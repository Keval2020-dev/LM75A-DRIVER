# LM75A-DRIVER
Interfacing STM NUCLEO-L073RZ  with LM75A Temperature sensor 

## Hardware & Software
* STM NUCLEO-L073RZ 
* LM75A MODULE 
* STM32CubeMx IDE 

## Pin Connection
LM75A Sensor interfaced on *I2C* bus over Nucleo Board.  
<pre>
BME280  ->  Nucleo Board(Arduino Header)  
VIN     ->  5 Volt
GND     ->  GND
SCL     ->  PB9(D15) 
SDA     ->  PB8(D14)
iNT     ->  PA6(D12)
</pre>   
Note: While Doing Connection keep the Solder Bridges of Nucleo Board in mind. 

## Resources 
Application code can be found under *Core/src/main.c*.   
For Adding Serial Printf function , I followed Shawn Hymel's [Tutorial](https://shawnhymel.com/1873/how-to-use-printf-on-stm32/).  
M2M_Soultion's Library from which i derived this project's Library [here](https://github.com/m2m-solutions/M2M_LM75A).
