@echo on
make clean
make all
avrdude -c usbtiny -p m32u4 -U flash:w:Caterina.hex
pause.


