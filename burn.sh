#!/bin/bash
# Burn PWM Fan Controller firmware to ATtiny13a using Arduino ISP
# Change serial port path as needed
cd bin
avrdude -Cavrdude.conf -v -pattiny13 -carduino -P/dev/ttyACM0 -b19200 -Uflash:w:fan-controller.hex:i
cd ../
