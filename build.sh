#!/bin/bash
# Compile ATtiny13 PWM Fan Controller

avr-gcc -Wall -g -Os -mmcu=attiny13 -v -o fan-controller.bin main.c
echo ""
avr-size -C fan-controller.bin
echo ""
avr-objcopy -j .text -j .data -O ihex fan-controller.bin fan-controller.hex
mv fan-controller.bin ./bin/fan-controller.bin
mv fan-controller.hex ./bin/fan-controller.hex
