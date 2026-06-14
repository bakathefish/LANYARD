# LANYARD
**A changable lanyard that you can update from your phone
## What it does
this is a lanyard with a 3.7" e-paper screen that connect to your phone and allows you to change what its displaying in real time over the internet. The photo you upload from your phone gets turned into a black and whirte image with shades of black and then displayed on the screen. becasue its eink even after you cut the power the image still stays there so you can wear it all day long without having to charge it 
## Why i built it
almost every month in my school we have a new event and for those we have to print out and create new lanyards for the attendees and im also starting my own hackclub in my school now. overall the landyards we normally used were also made of flimsy paper and by the third day they were pretty much unreadble. so to solve this i realised i could just make digital screened lanyards and at first i wanted to use a normal led or oled display however i realised those would eat too much power and so i ended up using epaper displays since they maintain their image even after the power is cut and since they have a hard pcb backing they have a much longer life
## How it works 
The brain of the entire lanyard is the esp32 module driving a waveshare 3.7 inch raw epaper pannel this pannel is strechable so we use the pcb to support it to add life to the product. On power up the lanyard makes its own wifi network that you can join from your device and upload an image. that image is then converted into a form the screen can support and sent and flashed onto the screen. a small dc-dc booster circut is aslo incliuded to generate the higher voltages the raw pannels needs to actually create the imagges
##hardware
### SCHEMATIC
<img width="1181" height="835" alt="image" src="https://github.com/user-attachments/assets/32cbffa8-f0a0-48bc-8323-517a09e101d7" />

### PCB FRONT

<img width="811" height="820" alt="image-1" src="https://github.com/user-attachments/assets/2b82514d-2c95-4cef-b44a-12f171a4875d" />

### PCB BACK

<img width="811" height="880" alt="image" src="https://github.com/user-attachments/assets/d301cfe2-1bf0-47a2-858a-de0170286e5c" />


## Bill of materials

