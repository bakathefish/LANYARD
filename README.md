# LANYARD
**A changeable lanyard that you can update from your phone.**
## What it does
This is a lanyard with a 3.7" e-paper screen that connects to your phone and allows you to change what it's displaying in real time over the internet. The photo you upload from your phone gets turned into a black and white image with shades of black and then displayed on the screen. Because it's e-ink, even after you cut the power the image still stays there so you can wear it all day long without having to charge it.
## Why I built it
Almost every month in my school we have a new event and for those we have to print out and create new lanyards for the attendees, and I'm also starting my own Hack Club in my school now. Overall the lanyards we normally used were also made of flimsy paper and by the third day they were pretty much unreadable. So to solve this I realised I could just make digital screened lanyards, and at first I wanted to use a normal LED or OLED display, however I realised those would eat too much power and so I ended up using e-paper displays since they maintain their image even after the power is cut and since they have a hard PCB backing they have a much longer life.
## How it works
The brain of the entire lanyard is the ESP32 module driving a Waveshare 3.7 inch raw e-paper panel. This panel is stretchable so we use the PCB to support it to add life to the product. On power up the lanyard makes its own WiFi network that you can join from your device and upload an image. That image is then converted into a form the screen can support and sent and flashed onto the screen. A small DC-DC booster circuit is also included to generate the higher voltages the raw panel needs to actually create the images.
## Hardware
### SCHEMATIC
<img width="1181" height="835" alt="image" src="https://github.com/user-attachments/assets/32cbffa8-f0a0-48bc-8323-517a09e101d7" />

### PCB FRONT

<img width="811" height="820" alt="image-1" src="https://github.com/user-attachments/assets/2b82514d-2c95-4cef-b44a-12f171a4875d" />

### PCB BACK

<img width="811" height="880" alt="image" src="https://github.com/user-attachments/assets/d301cfe2-1bf0-47a2-858a-de0170286e5c" />

## Bill of materials

| Qty | Description | Manufacturer | MPN | Supplier | Part No. | Unit (USD) | Total (USD) |
|-----|-------------|--------------|-----|----------|----------|------------|-------------|
| 1 | [ESP32-S3-MINI-1-N4R2 module](https://www.lcsc.com/product-detail/C3013941.html) | Espressif | ESP32-S3-MINI-1-N4R2 | LCSC | C3013941 | $5.15 | $5.15 |
| 1 | [Capacitor 100nF](https://www.lcsc.com/product-detail/C14663.html) | YAGEO | CC0603KRX7R9BB104 | LCSC | C14663 | $0.0094 | $0.0094 |
| 3 | [Capacitor 100nF](https://www.lcsc.com/product-detail/C149620.html) | YAGEO | AC0603KRX7R9BB104 | LCSC | C149620 | $0.0156 | $0.0468 |
| 1 | [Current-sense resistor 0.47Ω (RESE)](https://www.lcsc.com/product-detail/C186564.html) | KOA | SR731JTTDR470F | LCSC | C186564 | $0.1195 | $0.1195 |
| 1 | [Capacitor 4.7uF](https://www.lcsc.com/product-detail/C19666.html) | Samsung Electro-Mechanics | CL10A475KO8NNNC | LCSC | C19666 | $0.0185 | $0.0185 |
| 2 | [Capacitor 10uF](https://www.lcsc.com/product-detail/C19702.html) | Samsung Electro-Mechanics | CL10A106KP8NNNC | LCSC | C19702 | $0.0174 | $0.0348 |
| 1 | [3.3V LDO regulator](https://www.lcsc.com/product-detail/C5446.html) | TOREX | XC6206P332MR-G | LCSC | C5446 | $0.1124 | $0.1124 |
| 1 | [N-channel MOSFET](https://www.lcsc.com/product-detail/C710060.html) | VBsemi Elec | SI1304BDL-VB | LCSC | C710060 | — | $0 |
| 1 | [Power inductor 68uH](https://www.lcsc.com/product-detail/C72424.html) | Shun Xiang Nuo | SM3521-680MT | LCSC | C72424 | $0.0402 | $0.0402 |
| 3 | [Schottky diode MBR0530](https://www.lcsc.com/product-detail/C77336.html) | JSCJ | MBR0530 | LCSC | C77336 | $0.0347 | $0.1041 |
| 9 | [Capacitor 1uF](https://www.lcsc.com/product-detail/C913562.html) | muRata | GRM188B31H105KAALD | LCSC | C913562 | $0.0619 | $0.5571 |
| 3 | [Resistor 10kΩ](https://www.lcsc.com/product-detail/C98220.html) | YAGEO | RC0603FR-0710KL | LCSC | C98220 | $0.0036 | $0.0108 |
| 1 | [2-layer PCB](https://cart.jlcpcb.com/quote?spm=jlcpcb.Public.2006) | — | — | JLCPCB | — | — | — |
| 1 | [Waveshare 3.7" e-paper panel 480x280](https://www.waveshare.com/wiki/3.7inch_e-Paper_HAT) | Waveshare | — | — | — | — | — |
| 1 | Small 3.7V LiPo battery | — | — | — | — | — | — |

## Assembly
1. **Solder all of the parts onto the PCB one by one, do the smaller parts first then move to the larger ones**
2. **Connect the battery to the battery holes, solder it directly onto the board and double tape it**
3. **Connect the e-paper screen to the other side of the PCB and double tape it on**
4. **After it is powered, use the holes marked to flash the ESP, you need an external flasher to do the initial flash (flash lanyard.ino)**
5. **After that is done the lanyard should be on and there should be a WiFi connection, when you connect to it it should let you add an image and then flash it onto the screen wirelessly at http://192.168.4.1**
