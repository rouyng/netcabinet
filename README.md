# Networking Cabinet

Arduino sketch and design reference for my networking cabinet with integrated fan and LED lighting.

## Overview

An Arduino-powered controller that regulates temperature using a 12V fan controller by a PID loop fed with data from a TMP36 temperature sensor. Uses [Brett Beauregard's PID library for Arduino.](https://github.com/br3ttb/Arduino-PID-Library/)

A pushbutton switch detects when the cabinet door is open/closed. When door is open, fan is turned off and LED light strip turns on. When door is closed, LED strip is turned off and PID control of the fan is enabled.

Everything is built into a modified IKEA Lixhult cabinet. The cabinet contains a surge protector, Synology NAS, Ubiquiti Edgerouter X, PoE injector and a cable modem. Planning to add a Unifi US-8-60W switch.


## Hardware
See /doc for images and fritzing file.

- Ardunio UNO
- Generic pushbutton switch
- TMP36 temperature sensor
- Sparkfun Ardumoto shield
- 90mm muffin fan, 12 VDC
- approx 1' length Hitlights L2012V-401-1030-U 4100K LED light strip. 12 VDC, 2.8 Watts/ft
- MEAN WELL GST25A12-P1J Desktop AC Adapter, 120VAC to 12VDC 2A

## Logging
The Python script found at `log/cabinetlog.py` is designed to log data from the USB serial connection of the Arduino and generate a CSV file. The data logged by the CSV file can be adjusted by changing which variables are printed to the serial connection within `fanctl.ino`.

Tested using Python 3.5.1 running on a Synology DS218+. It may be necessary to run `sudo stty -F /dev/ttyACM0 9600 tostop` (replacing `/dev/ttyACM0` with whatever serial port the Arduino is located  at) in order to prevent other processes from writing to the serial connection and resetting the Arduino.

## TODO
- PID loop tuning based on data
