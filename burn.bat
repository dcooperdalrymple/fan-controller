# Use Arduino ISP to burn fan controller firmware to ATtiny13a
# Make sure to change COM port as needed
cd bin
avrdude.exe -Cavrdude.conf -v -pattiny13 -carduino -PCOM17 -b19200 -Uflash:w:fan-controller.hex:i
cd ..\
