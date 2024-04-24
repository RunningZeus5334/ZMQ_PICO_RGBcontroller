# ZMQ RBG Controller with RPI pico W

In this repository, I have developed a code in QT Creator, which uses the ZeroMQ library to make a publish-subscribe service. This service enables users to remotely manipulate the RGB LED on the Raspberry Pi Pico microcontroller.

## Content table
- [How to start guide](#How-to-start-guide)
- (coming soon) [Tutorial video](#Tutorial-video)
- [API manual](#API-manual)
- [Update/Patches](#Update/Patches) 
- [Future updates ](#Future-updates)


###  How to start guide
1. install QT creator(it's free)
2. install the 6.6.0 MinGW as compiler
3. pull the code from github and open the .pro file in Client side folder
4. press play and it should work 

### Tutorial video
(coming soon)

### API manual
![client side](https://github.com/RunningZeus5334/ZMQ_PICO_RGBcontroller/blob/main/resources/Schermafbeelding%202024-04-24%20223630.png)\
this is a quick flow diagram of how communication goes between client and server.
We can choose between 3 pico's if they all are connected.\
Pico 1: ``RGB_Controller?>Pico1``\
Pico 2: ``RGB_Controller?>Pico2``\
Pico 3: ``RGB_Controller?>Pico3``

We can also choose between a few leds\
Led 1: ``RGB_Controller?>Pico1>Led1``\
Led 2: ``RGB_Controller?>Pico1>Led2``\
Led 3: ``RGB_Controller?>Pico1>Led3``

And after that we can push the color code we want to change to. this ranges between 0..255 for RGB.\
example: ``RGB_Controller?>Pico1>Led1>255,15,105``

After the Led is changen we can recieve a response that the led has changed or that the pico is not responding.\
Subscribe to: ``RGB_Controller!>Pico1``

Example recieve: ``RGB_Controller!>Pico2>changedto:255,15,105``\
or for example: ``RGB_Controller!>Pico3>could_not_respond``
![server side](https://github.com/RunningZeus5334/ZMQ_PICO_RGBcontroller/blob/main/resources/Schermafbeelding%202024-04-24%20223647.png)
This is what the server does in the background. and how communication goes for the server. 

### Update/Patches 
- V0.1 Alpha release. Basic service that responds to a color.

### Future updates 
Here are some planned updates for my current service and repository: 

- PWM controlled RGB
- more than 1 led on the pico
- multiple pico's
- controlling something else
- More stable code
- Portable code
- Cleaner repository
- UI for conection and controlling RGB's
- Tutorial video on how to run on LAN for smart home services.
- Running ZMQ service on pico if possible
