@echo on
make clean
make all
avrdude -c usbasp -p m32u4 -U flash:w:Caterina.hex
pause.


