## Installation

### Driver Installation

#### Windows

1. Download https://github/signed_drivers and unzip into any folder.
   Note that the Windows 10 generic CDC drivers work as well.
1. Plug in the NXprog.
1. Windows will detect the board. 

#### Linux

1. No driver installation is needed.


### NOVUS NXprog Core installation


1. The NOVUS NXprog Core requires Arduino IDE 1.6.7 or above (including 1.8.x).
1. In the Arduino IDE, click File->Preferences.
1. Click the button next to Additional Boards Manager URLs.
1. Add the reference to NOVUS platform definition https://github/package_novus.json.
1. Save preferences, then open the Boards Manager.
1. Install the NOVUS Arduino package.
1. Close Boards Manager, then click Tools->Board->(choose board).
1. Select the MCU with the now visible Tools->Microcontroller menu (if present).
1. Plug in the NXprog.
1. Click Tools->Port and choose the COM port. Note that the board indicated may not match the chosen board*
1. You can now upload your own sketch.


## Language reference
The NXprog version Arduino programming language is an extension of standard [Arduino Language](https://www.arduino.cc/reference/en/) can be divided in three main parts: 
* IO Functions
	* [Standard Analog](./AnalogIO.md)
	* [Expert IO](./ExpertAnalogIO.md)
* Values 
	* [Sensor Type](./SensorType.md)
* Structures
	* [Analog Configuration](./AnalogConfiguration.md)
