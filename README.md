# Duckuino

### The truly open-source atmega32u4 ducky clone (V2.0)

```YOU are on the ALTIUM branch! V2.0 WIP```

## Info

Enter the duckuino, the WIP fully open-source USB rubberducky clone based on the atmega32u4

## BOM

### Parts list for building your duckuino
Duckuino BOM

```
Part 		Value         		Device            		Package                                                                                                            
3V3  		TPTP11R       		TPTP11R           		TP11R
C1   		10uF          		C-USC0603         		C0603                                                                                                         
C2   		10uF          		C-USC0603         		C0603                                                                                                            
C3   		1uF           		C-EUC0603         		C0603                                                                                                          
C4   		0.1uF/100nF   		C-EUC0603         		C0603
C5   		22pF          		C-EUC0603         		C0603                                                                                                           
C6   		22pF          		C-EUC0603         		C0603                                                                                                            
Q1   		16MHz         		XTAL-4-3225       		NX3225                                                                                                    
R1   		10KR          		RR0603            		R0603
R2   		22R           		RR0603           		 R0603
R3   		22R           		RR0603           		 R0603
SD1  		TF-HOLDER     		TF-HOLDER         		TF-PULL         
U$1  		ATMEGA32U4-AU 		ATMEGA32U4-AU     		TQFP44                                                                                                
U1   		MIC5219 3.3V  		V_REG_MIC52193.3V 		SOT23-5
X1   		USB-A         		USB-A                                                                                                                         
```

## PINMAP
PINMAP of the ATMEGA32u4

```
Warning! This WILL change due to pin arranjements on the pcb layout
D0/RX    --- TestPad
D1/TX    --- TestPad
D2/SDA   --- Testpad
D3       --- N/C
D4/A6    --- CD/DAT3(!CS!)  (sdcard reader)
D5       --- N/C
D6       --- GPIO LED1
D7       --- GPIO LED2
D8/A8    --- DIPSwitch1
D9/A9    --- DIPSwitch2
D10/A10  --- DIPSwitch3
D11      --- DIPSwitch4
D12      --- N/C
D13      --- N/C
D14/MISO --- DAT0(DO) (sdcard reader)
D15/SCK  --- CLK(SCLK) (sdcard reader)
D16/MOSI --- CMD(DI) (sdcard reader)
```



## Renders & Pictures

### V2.0 Altium Renders
Soon!


## Old Version Renders & Pictures

### V0.1 Photos
![Soldered1](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/soldered1.jpg)

![Soldered2](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/soldered2.jpg)

![Soldered3](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/soldered3.jpg)

### V0.1 Renders
![Render1](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/top.png)

![Render2](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/bot.png)


### V0.1 Eagle Renders
![Eagle1](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/eagle_sch.png)

![Eagle2](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/eagle_brd.png)

### V0.1 PCB pictures
![PCB1](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/V0.1_TOP.jpg) ![PCB2](https://raw.githubusercontent.com/afonsus1997/Duckuino/master/renders/V0.1_BOTTOM.jpg)