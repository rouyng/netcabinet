#Networking Cabinet
Arduino sketch and design reference for my networking cabinet with integrated fan and LED lighting.

##Overview
An Arduino-powered controller that regulates temperature using a 12V fan controller by a PID algorithim fed with data from a TMP36 temperature sensor.
A pushbutton switch detects when the cabinet door is open/closed. When door is open, fan is turned off and LED light strip turns on. When door is closed, LED strip is turned off and PID control of the fan is enabled.

##Hardware
Ardunio UNO with pushbutton switch, TMP36 temperature sensor and Sparkfun Ardumoto shield.

