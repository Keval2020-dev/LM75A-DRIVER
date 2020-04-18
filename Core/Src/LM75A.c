//---------------------------------------------------------------------------------------------
//
// Library for the LM75A temperature sensor by NXP and Texas Instruments.
//
// Copyright 2016-2017, M2M Solutions AB
// Written by Jonny Bergdahl, 2016-11-18
//
// Licensed under the MIT license.
//
////////////////////////////////////////////////////////////////////////////////////////////////
#include "LM75A.h"
#include "main.h"

////////////////////////////////////////////////////////////////////////////////////////////////

extern uint8_t Reg_Buf[10]; //defined in main file
extern uint8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length); //defined in main file
extern uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);  //defined in main file
////////////////////////////////////////////////////////////////////////////////////////////////
//

//to shutdown the LM75A module
void LM75A_ShutDown()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);


	Reg_Buf[0] = ((Reg_Buf[0] & 0b11111110)|0b1);
	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG,&Reg_Buf[0],1);

}


//to wakeup the LM75A module
void LM75A_Wakeup()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);


	Reg_Buf[0] = (Reg_Buf[0] & 0b11111110);
	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG,&Reg_Buf[0],1);

}

//to check if LM75A is shutdown or not?
_Bool LM75A_Is_ShutDown()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);

	return (Reg_Buf[0] & 0b1);


}


//to read the current temperature from the sensor
float LM75A_getTemperature()
{
	uint16_t result;
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_TEMP,Reg_Buf,2);

	result = (Reg_Buf[0] << 8) | Reg_Buf[1];

	if(!result)
		return LM75A_INVALID_TEMPERATURE;
	else
		return (float)result / 256.0f;
}


//to read the current temperature from the sensor and return value in farenheit
float LM75A_getTemperatureInFarenheit()
{
	return LM75A_getTemperature() * 1.8f + 32.0f;
}



//to read the set hystersis temperature in sensor
float LM75A_getHysterisisTemperature()
{
	int16_t result;

	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_THYST,Reg_Buf,2);

	result = (int16_t)((Reg_Buf[0] << 8) | Reg_Buf[1]);


    if(!result)
      return LM75A_INVALID_TEMPERATURE;
	else
	  return (float)result / 256.0f;
}







//to read the set OS trip temperature in sensor
float LM75A_getOSTripTemperature()
{
	int16_t result;

	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_TOS,Reg_Buf,2);

	result = (int16_t)((Reg_Buf[0] << 8) | Reg_Buf[1]);

	if(!result)
	  return LM75A_INVALID_TEMPERATURE;
	else
      return (float)result / 256.0f;


}

//to read the set OS polarity in sensor
LM75A_OsPolarity LM75A_getOsPolarity()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);
	return (LM75A_OsPolarity)(Reg_Buf[0] & 0b100);
}


//to read the current device mode in sensor
LM75A_DeviceMode LM75A_getDeviceMode()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);

	return (LM75A_DeviceMode)(Reg_Buf[0] & 0b010);
}


//to set hystersis temperature in sensor
void LM75A_setHysterisisTemperature(int16_t temperature)
{

	temperature *= 256;
	Reg_Buf[0] = (uint8_t)(temperature>>8);
	Reg_Buf[1] = (uint8_t)temperature;


    i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_THYST,Reg_Buf,2);
}


//to set os trip temperature in sensor
void LM75A_setOsTripTemperature(int16_t temperature)
{

	temperature *= 256;
	Reg_Buf[0] = (uint8_t)(temperature>>8);
	Reg_Buf[1] = (uint8_t)temperature;


	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_TOS,Reg_Buf,2);

}

//to set os polarity in sensor
void LM75A_setOsPolarity(LM75A_OsPolarity polarity)
{

	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);


	Reg_Buf[0] = ((Reg_Buf[0] & 0b11111011) | polarity);
	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG, &Reg_Buf[0],1);

}

//to set the device mode in sensor
void LM75A_setDeviceMode(LM75A_DeviceMode deviceMode)
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);

	Reg_Buf[0] = ((Reg_Buf[0] & 0b11111101) | deviceMode);
	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG, &Reg_Buf[0],1);

}

//to clear the faults
void LM75A_setFaultQueueValue(LM75A_FaultQueueValue value)
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);

	Reg_Buf[0] = ((Reg_Buf[0] & 0b11100111) | value);

	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG, &Reg_Buf[0],1);

}



 //check whether sensor is present on i2c bus or not
_Bool LM75A_Is_Connected()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);
	uint8_t oldValue = Reg_Buf[0];

	Reg_Buf[0] = 0x0f;
	i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG, &Reg_Buf[0],1);

	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);
		uint8_t newValue = Reg_Buf[0];

	Reg_Buf[0] = oldValue;
    i2c_reg_write(LM75A_DEFAULT_ADDRESS, LM75A_REGISTER_CONFIG, &Reg_Buf[0],1);

    return newValue == 0x0f;


}

//Read configuration register of sensor
int8_t LM75A_getConfig()
{
	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);
	return Reg_Buf[0];


}

//Read product id of sensor
float LM75A_getProdId()
{


	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_PRODID,Reg_Buf,1);
	return (float)((Reg_Buf[0]) >> 4) + (Reg_Buf[0] & 0x0F) /10.0f;

} 


//Read fault value from sensor
LM75A_FaultQueueValue LM75A_getFaultQueueValue()
{

	i2c_reg_read(LM75A_DEFAULT_ADDRESS,LM75A_REGISTER_CONFIG,Reg_Buf,1);

	return (LM75A_FaultQueueValue)(Reg_Buf[0] & 0b00011000);


}
