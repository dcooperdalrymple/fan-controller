avr-gcc -Wall -g -Os -mmcu=attiny13a -v -o fan-controller.bin main.c
avr-size -C fan-controller.bin
avr-objcopy -j .text -j .data -O ihex fan-controller.bin fan-controller.hex
move fan-controller.bin bin/fan-controller.bin
move fan-controller.hex bin/fan-controller.hex
