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
- MEAN WELL GST25A12-P1J Desktop AC Adapters, 120VAC to 12VDC 2A

## TODO
- shell script to log data to Synology NAS over serial connection
- PID loop tuning based on data
- Photo documentation
