// getting libraries
#include <WiFi.h>
#include <WebServer.h>
#include <GxEPD2_BW.h>
// defining pins
#define CS    10
#define DC    9
#define RST   8
#define BUSY  7
#define SCK   12
#define DIN   11 
// WIFI THINGY
const char* ssid = "your_wifi_SSID";
const char* password = "your_wifi_password";
// define screen size
#define IMG_W 480
#define IMG_H 280
#define IMG_BYTES(IMG_w*IMG_H/8)
// define the screen object thingy
GxEPD2_BW<GxEPD2_370_TC1, GxEPD2_370_TC1::HEIGHT> display(
  GxEPD2_370_TC1(CS, DC, RST, BUSY)
);
// make the iphone connection website on page 80
WebServer server(80)
// where the photo we upload goes(temp storage)
uint8_t imgbuf[IMG_BYTES];   // the photo, once it arrives
bool newImage = false;
//webpage itself
const char PAGE[] PROGMEM = R"HTML(
<!doctype html><html><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Badge</title>
<style>
 body{font-family:sans-serif;text-align:center;padding:16px;background:#111;color:#eee}
 button,label{margin:8px;padding:14px 20px;font-size:16px;border:0;border-radius:10px;
   background:#3b82f6;color:#fff}
 canvas{border:1px solid #555;margin-top:12px;max-width:100%;background:#fff}
</style></head><body>
<h1>Badge photo</h1>
<label>Pick a photo<input id="file" type="file" accept="image/*" hidden></label><br>
<canvas id="c" width="480" height="280"></canvas><br>
<button id="send" disabled>Send to badge</button>
<div id="status"></div>
<script>
const W=480,H=280;
const c=document.getElementById('c'),ctx=c.getContext('2d');
let bytes=null;
// when you pick a photo, draw it onto the canvas at 480x280
document.getElementById('file').onchange=e=>{
  const img=new Image();
  img.onload=()=>{
    ctx.fillStyle='#fff';ctx.fillRect(0,0,W,H);
    const s=Math.min(W/img.width,H/img.height);   // fit the whole photo in
    ctx.drawImage(img,(W-img.width*s)/2,(H-img.height*s)/2,img.width*s,img.height*s);
    dither();
  };
  img.src=URL.createObjectURL(e.target.files[0]);
};
// turn the canvas into black & white using Floyd-Steinberg dithering
function dither(){
  const d=ctx.getImageData(0,0,W,H),p=d.data;
  const g=new Float32Array(W*H);
  for(let i=0;i<W*H;i++) g[i]=0.299*p[i*4]+0.587*p[i*4+1]+0.114*p[i*4+2]; // grayscale
  for(let y=0;y<H;y++)for(let x=0;x<W;x++){
    const i=y*W+x,old=g[i],nv=old<128?0:255,err=old-nv;g[i]=nv;
    if(x+1<W)g[i+1]+=err*7/16;
    if(y+1<H){if(x>0)g[i+W-1]+=err*3/16;g[i+W]+=err*5/16;if(x+1<W)g[i+W+1]+=err*1/16;}
  }
  // pack into bytes: a dark pixel = a 1 bit
  bytes=new Uint8Array(W*H/8);
  for(let i=0;i<W*H;i++){if(g[i]<128)bytes[i>>3]|=(0x80>>(i&7));
    const v=g[i];p[i*4]=p[i*4+1]=p[i*4+2]=v;}
  ctx.putImageData(d,0,0);                       // show the preview
  document.getElementById('send').disabled=false;
}
// send the finished black & white image to the badge
document.getElementById('send').onclick=()=>{
  if(!bytes)return;
  document.getElementById('status').textContent='Sending...';
  fetch('/upload',{method:'POST',body:bytes})
    .then(r=>document.getElementById('status').textContent=r.ok?'Done!':'Failed.')
    .catch(()=>document.getElementById('status').textContent='Failed.');
};
</script></body></html>
)HTML";
// what to do when phone asks for code 
void handleRoot() { 
        server.send_p(200,
            "text/html")
}
// what to do when phone sends a photo
void handleUpload() {
  String body = server.arg("plain");       
  if (body.length() == IMG_BYTES) {         
    for (size_t i = 0; i < IMG_BYTES; i++) imgbuf[i] = (uint8_t)body[i];
    newImage = true;                       
    server.send(200, "text/plain", "ok");
  } else {
    server.send(400, "text/plain", "wrong size");
  }
}
// burn image onto screen and then sleep mode
void showImage(){
    display.init();
    display.setRotation(1);
    display.setFullWindow();
    display.FirstPage();
    do{
        display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, imgbuf, IMG_W, IMG_H, GxEPD_BLACK);
  } while (display.nextPage());
  display.hibernate();            
}
// getting it to run when it gets power
void setup() {
  SPI.begin(SCK, -1, DIN, CS);    // tell the chip which pins are the screen's SPI

  WiFi.softAP(ssid, password);    // JOB 1: make our own WiFi network

  server.on("/", handleRoot);              // JOB 2: when phone visits "/", send page
  server.on("/upload", HTTP_POST, handleUpload); // when phone sends a photo, handle it
  server.begin();                          // start listening
}

// getting the loop to run it again
void loop() {
  server.handleClient();        
  if (newImage) {                
    showImage();                  

  }
}
