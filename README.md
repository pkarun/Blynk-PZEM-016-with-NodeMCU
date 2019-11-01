# Blynk PZEM-016 with NodeMCU (Single Device)
Blynk ESP8266 (NodeMCU) Program for PZEM 016 Power Meter. 

<h2>Requirements</h2>
1) <a href="http://s.click.aliexpress.com/e/pV6CDdr2">PZEM-016</a></br>
2) <a href="http://s.click.aliexpress.com/e/nlefJ4PI">NodeMCU</a></br>
3) <a href="http://s.click.aliexpress.com/e/5D9mJ8JW">MAX485 Module RS-485 TTL to RS485 MAX485CSA Converter Module </a></br>
4) <a href="http://s.click.aliexpress.com/e/e9vv4Wwy">USB to RS485 485 Converter Adapter</a> (optional)</br>
5) <a href="https://play.google.com/store/apps/details?id=cc.blynk">Blynk App</a></br>

<h2> Installation </h2>
Open settings.h and change Bynk Auth code, Wifi settings, server settings and few other parameters as per your project requirement.


<h2> Hardware Connection </h2>

<h3>PZEM-016 to NodeMCU</h3>

GND to GND</br>
5v to Vin</br>

<h3>PZEM-016 to RS-485 TTL Converter to RS485</h3>

A to A</br>
B to B</br>

<h3>RS-485 TTL to RS485 Converter to NodeMCU</h3>

VCC to 3V</br>
GND to GND</br>
DI  to D6/GPIO12</br>
DE  to D1/GPIO5</br>
RE  to D2/GPIO4</br>
RO  to D5/GPIO14</br>


<h2> Software Setup </h2>

1) Download and install the Blynk Mobile App for iOS or Android.

2) Scan the QR code at the bottom of this page to clone the screenshot below, or create a new project yourself and manually arrange and setup the widgets.

3) Email yourself the Auth code.

4) Download this repo and copy the files in to your sketches directory. Open the sketch in Arduino IDE.

5) Go to the settings.h tab. This is where all the customisable settings are. You should be able to change almost everything from there before compiling.

<h2> Screenshots </h2>

<img src="/images/products/peacefair-pzem-016-with-split-ct.jpg" alt="PZEM-016" title="PZEM-016" width="350" height=""></br>

<img src="/images/products/max485-rs-485-to-ttl-converter-module.jpg" alt="MAX485 Module RS-485 TTL to RS485 MAX485CSA Converter Module " title="MAX485 Module RS-485 TTL to RS485 MAX485CSA Converter Module " width="350" height=""></br>

<img src="/images/products/usb-to-rs485.jpg" alt="USB to RS485 485 Converter Adapter" title="USB to RS485 485 Converter Adapter" width="350" height=""></br>


<h2> Scan QR Code on Blynk App </h2>

<img src="/images/blynk-scan-qr-code.png" alt="Blynk Project QR code" title="Blynk Project QR code"></br>
