# Smart Useless Box with ESP8266 and Gesture Sensor

## Forked from balassy and made it work with PlatformIO

Added LightSleep for the Wemos after 15s. (Power Consumption)

A useless box made smarter with an ESP8266 microcontroller on a Wemos D1 Mini board and an APDS-9960 proximity sensor to give more funny responses.

![Photo](./media/Useless-Box.jpg)

## YAUB (Yet Another Useless Box?)

Useless machines are not new, there are many versions available. You can create a simple one using a lever switch, however that will react always the same way. Using a programmable microcontroller you can create **funny, unexpected responses**, and by adding a proximity sensor you can surprise the user with **actions before she would even turn on the switch**!

This is a programmable useless box, so you have the option to implement **additional reactions** when you want to to further improve this funny little toy. What's more the used controller board has WiFi connectivity, so you can **connect it to other online services** (e.g. IFTTT) or **smart assistants** (Alexa, Cortana etc.).

## Smart Useless Box in Action

Click the image below to see this box in action:

[![Smart Useless Box in Action](./media/video-preview.png)](http://www.youtube.com/watch?v=x0kGetj1nt8 "Smart Useless Box in Action")

## Hardware

The following hardware components are required to build this project:

- 1 × [Wemos D1 Mini board](hhttps://www.bastelgarage.ch/wemos-d1-mini-esp8266-nodemcu-lua-board?search=wemos%20d1%20mini%20esp8266%20nodemcu%20lua%20board)
- 1 × [APDS-9960 RGB, gesture and proximity sensor](https://www.bastelgarage.ch/apds-9960-rgb-gesten-distanz-sensor-modul-i2c?search=apds-9960%20rgb%20%2F%20gesten%20%2F%20distanz%20sensor%20modul%20i2c)
- 2 × [SG90 servo motors](https://www.bastelgarage.ch/tower-pro-micro-servo-9g-sg90?search=tower%20pro%20micro%20servo%209g%20%2F%20sg90)
- 1 × [Switch](ttps://www.bastelgarage.ch/kippschalter-on-on-mts-102?search=kippschalter%20on-on%20mts-102) this one worked for me. It's not that easy to Switch but the servo made it in 100% of all cases.  
- 1x [Prototype Shield](https://www.bastelgarage.ch/wemos-d1-mini-prototype-shield?search=wemos%20d1%20mini%20prototype%20shield)
- 1 × 1kΩ resistance
- Male pin headers:
  - 1 × 1x2 for the switch
  - 2 × 1x3 for the servo motors
  - 1 × 1x5 for the sensor
- Pin headers - to connect the shield to the Wemos D1 Mini.
- Dupont cables or wires with connectors.
- BluTack - to mount the wires and the controller board.
- M3 screws - to mount the lids.

## Wiring

The wiring is designed to create a custom shield for the Wemos D1 Mini ESP8266 microcontroller-based board, instead of soldering the cables directly to the board. In this way you can easily assemble the parts or even reuse them in the future.

### Schematics

![Schematic](./wiring/Useless-Box-Shield-v1-Schematic.png)

### PCB

![PCB](./wiring/Useless-Box-Shield-v1-PCB.png)

The PCB was designed with [Fritzing](https://fritzing.org), and you can [download the source file](./wiring/Useless-Box-Shield-v1.fzz) to further customize it to your needs.

You can also [download the Gerber files](./wiring/Useless-Box-Shield-v1-PCB-Gerber.zip) which you can use to order the PCB from your preferred PCB manufacturer. (Note: I've created my prototype manually then documented it in Fritzing, so I have not tested this PCB yet.)

## Software

The source code in this repo is created with [Visual Studio Code](https://code.visualstudio.com) using the [Arduino plugin from Microsoft](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino), but it should work with the [Arduino IDE](https://www.arduino.cc/en/main/software) as well.

The code in this repository is preconfigured with the pin layout shown in the wiring diagram above, but if you decide to connect the parts to different pins, you have to update the values in the `config.h` file.

After finalizing the pin configuration (or using the default one) just upload the code to the Wemos D1 Mini board.

The responses of the box are implemented in the `useless-box.ino` file, and the `run()` function is responsible for selecting and executing the reaction to a flip of the switch or to a signal from the sensor. Feel free to add new logic or remove any existing reaction you don't like in this function.

## The Box

I designed a custom box for this project which can be 3D printed or even further customized. You can download the model from [Thingiverse](https://www.thingiverse.com/thing:3856965) or [MyMiniFactory](https://www.myminifactory.com/object/3d-print-100944).

Happy Printing! :)

## About the author

This project is maintained by [György Balássy](https://linkedin.com/in/balassy).
