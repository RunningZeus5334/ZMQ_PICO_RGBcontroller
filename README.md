# ZMQ RBG Controller with RPI pico W

In this repository, I have developed a code in QT Creator, which uses the ZeroMQ library to make a publish-subscribe service. This service enables users to remotely manipulate the RGB LED on the Raspberry Pi Pico microcontroller.

## Content table
- [How to start guide](#how-to-start-guide)
- [How to build guide](#how-to-build-guide)
- [Tutorial video](#tutorial-video)
- [API manual](#api-manual)
- [Update/Patches](#updatepatches) 
- [Future updates ](#future-updates)


##  How to start guide
1. install QT creator(it's free)
2. install the 6.6.0 MinGW as compiler
3. pull the code from github and open the .pro file in Client side folder
4. press play and it should work 

## How to build guide
For building your own code that communicates with the service u need the ZMQ library.
Option 1: use the library included in this repo
1. copy the include and lib folder to the same place as your qt project folder is.
2. in the .pro file add these lines.
```
DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include
```
3. try to build it should normally work now


Option 2: compile the zmq library yourself

#### Download libzmq library
1. Go to the [libzmq](https://github.com/zeromq/libzmq) GitHub page.
2. Select the v4.3.4 tag.
3. Download the repository.
4. Unzip the lib.

#### Install CMake
1. Go to [CMake](https://cmake.org/).
2. Download the Windows x64 installer.
3. Run the CMake installer.

#### Install pkg-config [Windows]
1. Go to [http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/](http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/).
2. Download the file pkg-config_0.26-1_win32.zip
3. Extract the file bin/pkg-config.exe to C:\MinGW\bin
4. Download the file gettext-runtime_0.18.1.1-2_win32.zip
5. Extract the file bin/intl.dll to C:\MinGW\bin
6. Go to [http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28](http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28)
7. Download the file glib_2.28.8-1_win32.zip
8. Extract the file bin/libglib-2.0-0.dll to C:\MinGW\bin

Source: https://stackoverflow.com/questions/1710922/how-to-install-pkg-config-in-windows

#### Build instructions for libzmq with MinGW
1. Run the CMake GUI.
2. Set the path to the libzmq directory as source directory.
    * e.g. C:/Users/User1/Downloads/libzmq-4.3.4
3. Set the same path as the build directory and append /build.
    * e.g. C:/Users/User1/Downloads/libzmq-4.3.4/build
4. Press the configure button.
5. CMake will ask you permission to create the build directory. Click Yes.
6. Select the MinGW Makefiles as generator for this project.
7. Click Finish
8. If the configuration is finished then deselect ZMQ_BUILD_TESTS and click Generate.
9. Run a command prompt as administrator from the build directory.
10. Enter the command `mingw32-make -j4 install` and hit enter.
11. If the build is succesful you will see that the directory C:/Program Files (x86)/ZeroMQ is created.

## Tutorial video
(coming soon)

## API manual
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

## Update/Patches 
- V0.1.1 Added API manual and lots of documentation
- V0.1 Alpha release. Basic service that responds to a color.
  

## Future updates 
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
