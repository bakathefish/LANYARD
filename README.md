<img width="1410" height="2000" alt="E-Ink Lanyard" src="https://github.com/user-attachments/assets/d56f08d7-72f8-4384-be8c-f64266a1b6e4" />


# E-INK LANYARD
**A changeable lanyard that you can update from your phone.**
## What it does
This is a lanyard with a 3.7" e-paper screen that connects to your phone and allows you to change what it's displaying in real time over the internet. The photo you upload from your phone gets turned into a black and white image with shades of black and then displayed on the screen. Because it's e-ink, even after you cut the power the image still stays there so you can wear it all day long without having to charge it.
## Why I built it
Almost every month in my school we have a new event and for those we have to print out and create new lanyards for the attendees, and I'm also starting my own Hack Club in my school now. Overall the lanyards we normally used were also made of flimsy paper and by the third day they were pretty much unreadable. So to solve this I realised I could just make digital screened lanyards, and at first I wanted to use a normal LED or OLED display, however I realised those would eat too much power and so I ended up using e-paper displays since they maintain their image even after the power is cut and since they have a hard PCB backing they have a much longer life.
## How it works
The brain of the entire lanyard is the ESP32 module paired with a 3.7 inch e-paper panel. This panel is stretchable and flimsy so we use the PCB to support it to add life and rigidity to it. when turned on the lanyard makes its own WiFi network that you can join from your device to change the displayed image. The conversion to black and white actually happens on your phone, inside the webpage itself. It takes your photo and runs Floyd-Steinberg dithering on it, which turns the greys into a pattern of tiny black and white dots so the image still looks right on a screen that can only do black or white. Then it sends those finished bytes over to the ESP, and the ESP just draws them straight onto the panel, so the little board never has to do any heavy image work itself. A small DC-DC booster circuit is also included to generate the higher voltages the raw panel needs to actually create the images, because a raw e-paper panel needs a lot more than the 3.3V the rest of the board runs on.
## What's on the board
The main parts are the ESP32-S3-MINI-1 module for the WiFi and the brains, the 3.7 inch Waveshare panel which is 480 by 280 and does 4 levels of grey, and a small LiPo battery so the whole thing runs off your neck with nothing plugged in. The rest of the board is the power side. There is a 3.3V regulator that feeds the ESP, and a small boost converter built around an inductor, a Schottky diode and the MOSFET that makes the higher voltage the e-paper panel needs to refresh. It is a 2 layer board and every part is hand solderable, I assembled mine by hand with a normal iron and hot air.
## Hardware
### SCHEMATIC
<img width="1047" height="740" alt="schematic" src="https://github.com/user-attachments/assets/e97b7b35-8f3c-4db9-9367-8622047220e4" />

### PCB LAYER 1




<img width="507" height="859" alt="image" src="https://github.com/user-attachments/assets/7b3e5b45-593e-45ec-a6f2-014c3e891f4e" />




### PCB LAYER 2



<img width="347" height="574" alt="image" src="https://github.com/user-attachments/assets/5426bbc5-2705-4a7e-a531-d5c68c4522af" />






### PCB 3D FRONT

<img width="811" height="820" alt="image-1" src="https://github.com/user-attachments/assets/2b82514d-2c95-4cef-b44a-12f171a4875d" />

### PCB 3D BACK

<img width="811" height="880" alt="image" src="https://github.com/user-attachments/assets/d301cfe2-1bf0-47a2-858a-de0170286e5c" />

## Firmware
The code is in [firmware/lanyard.ino](firmware/lanyard.ino). It runs on the ESP32, makes the WiFi hotspot, serves the upload page, takes the image your phone sends and draws it onto the e-paper, then drops the screen into hibernate so it sits there using basically no power until you send it a new one. The image comes in as one bit per pixel, so the whole 480 by 280 screen is only about 16 kilobytes, which is tiny and sends over WiFi almost instantly. You flash it once with an external USB to serial adapter using the pads on the board, and after that every image update happens over WiFi so you never have to plug it in again.
## How to use it
1. Power it on with the battery plugged in.
2. On your phone, join the WiFi network the lanyard makes.
3. Open http://192.168.4.1 in your browser.
4. Pick a photo. It shows you a black and white preview of how it will actually look on the screen.
5. Hit send, and a few seconds later the photo is on your lanyard.

Since it is e-paper the image stays even if the battery dies or you turn it off, so it is really only pulling power in those few seconds while it redraws.
## Bill of materials

| Qty | Description | Manufacturer | MPN | Supplier | Part No. | Unit (USD) | Total (USD) |
|-----|-------------|--------------|-----|----------|----------|------------|-------------|
| 1 | [ESP32-S3-MINI-1-N4R2 module](https://www.lcsc.com/product-detail/C3013941.html) | Espressif | ESP32-S3-MINI-1-N4R2 | LCSC | C3013941 | $5.15 | $5.15 |
| 1 | [Capacitor 100nF](https://www.lcsc.com/product-detail/C14663.html) | YAGEO | CC0603KRX7R9BB104 | LCSC | C14663 | $0.0094 | $0.0094 |
| 3 | [Capacitor 100nF](https://www.lcsc.com/product-detail/C149620.html) | YAGEO | AC0603KRX7R9BB104 | LCSC | C149620 | $0.0156 | $0.0468 |
| 1 | [Current-sense resistor 0.47Ω](https://www.lcsc.com/product-detail/C186564.html) | KOA | SR731JTTDR470F | LCSC | C186564 | $0.1195 | $0.1195 |
| 1 | [Capacitor 4.7uF](https://www.lcsc.com/product-detail/C19666.html) | Samsung Electro-Mechanics | CL10A475KO8NNNC | LCSC | C19666 | $0.0185 | $0.0185 |
| 2 | [Capacitor 10uF](https://www.lcsc.com/product-detail/C19702.html) | Samsung Electro-Mechanics | CL10A106KP8NNNC | LCSC | C19702 | $0.0174 | $0.0348 |
| 1 | [3.3V LDO regulator](https://www.lcsc.com/product-detail/C5446.html) | TOREX | XC6206P332MR-G | LCSC | C5446 | $0.1124 | $0.1124 |
| 1 | [N-channel MOSFET](https://www.lcsc.com/product-detail/C710060.html) | VBsemi Elec | SI1304BDL-VB | LCSC | C710060 | $0.0246 | $0.0246 |
| 1 | [Power inductor 68uH](https://www.lcsc.com/product-detail/C72424.html) | Shun Xiang Nuo | SM3521-680MT | LCSC | C72424 | $0.0402 | $0.0402 |
| 3 | [Schottky diode MBR0530](https://www.lcsc.com/product-detail/C77336.html) | JSCJ | MBR0530 | LCSC | C77336 | $0.0347 | $0.1041 |
| 9 | [Capacitor 1uF](https://www.lcsc.com/product-detail/C913562.html) | muRata | GRM188B31H105KAALD | LCSC | C913562 | $0.0619 | $0.5571 |
| 3 | [Resistor 10kΩ](https://www.lcsc.com/product-detail/C98220.html) | YAGEO | RC0603FR-0710KL | LCSC | C98220 | $0.0036 | $0.0108 |
| 1 | [2-layer PCB (min order 5 pcs)](https://jlcpcb.com) | - | - | JLCPCB | - | $2.00 | $2.00 |
| 1 | [Waveshare 3.7" e-paper raw panel 480x280](https://www.waveshare.com/3.7inch-e-paper.htm) | Waveshare | - | - | - | $18.99 | $18.99 |
| 1 | Small 3.7V LiPo battery | - | - | - | - | $3.00 | $3.00 |
| | | | | | | **Total** | **$30.22** |

The same list is also in [bom.csv](bom.csv) if you want it as a file.

## Assembly
1. **Solder all of the parts onto the PCB one by one, do the smaller parts first then move to the larger ones**
2. **Connect the battery to the battery holes, solder it directly onto the board and double tape it**
3. **Connect the e-paper screen to the other side of the PCB and double tape it on**
4. **After it is powered, use the holes marked to flash the ESP, you need an external flasher to do the initial flash (flash lanyard.ino)**
5. **After that is done the lanyard should be on and there should be a WiFi connection, when you connect to it it should let you add an image and then flash it onto the screen wirelessly at http://192.168.4.1**
