
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

#ifndef LM75_h
#define LM75_h

#include "main.h"


//Register address in LM75A

#define LM75A_DEFAULT_ADDRESS		0x48		// Address is configured with pins A0-A2
#define LM75A_REGISTER_TEMP			0			// Temperature register (read-only)
#define LM75A_REGISTER_CONFIG		1			// Configuration register
#define LM75A_REGISTER_THYST		2			// Hysterisis register
#define LM75A_REGISTER_TOS			3			// OS register
#define LM75A_REGISTER_PRODID		7			// Product ID register - Only valid for Texas Instruments

#define LM75_CONF_OS_COMP_INT		1			// OS operation mode selection
#define LM75_CONF_OS_POL			2			// OS polarity selection
#define LM75_CONF_OS_F_QUE			3			// OS fault queue programming

#define LM75A_INVALID_TEMPERATURE	-1000.0f	// Just an arbritary value outside of the sensor limits


typedef enum FaultQueueValue
{
	NUMBER_OF_FAULTS_1 = 0,
	NUMBER_OF_FAULTS_2 = 0b01000,
	NUMBER_OF_FAULTS_4 = 0b10000,
	NUMBER_OF_FAULTS_6 = 0b11000
}LM75A_FaultQueueValue;

typedef enum OsPolarity
{
	OS_POLARITY_ACTIVELOW = 0,
	OS_POLARITY_ACTIVEHIGH = 0b100
}LM75A_OsPolarity;

typedef enum DeviceMode
{
	DEVICE_MODE_COMPARATOR = 0,
	DEVICE_MODE_INTERRUPT = 0b10
}LM75A_DeviceMode;

//Declaration of functions


void LM75A_ShutDown();
void LM75A_Wakeup();
_Bool LM75A_Is_ShutDown();
float LM75A_getTemperature();
float LM75A_getTemperatureInFarenheit();
float LM75A_getHysterisisTemperature();
LM75A_FaultQueueValue LM75A_getFaultQueueValue();
float LM75A_getOSTripTemperature();
LM75A_OsPolarity LM75A_getOsPolarity();
LM75A_DeviceMode LM75A_getDeviceMode();
void LM75A_setHysterisisTemperature(int16_t temperature);
void LM75A_setOsTripTemperature(int16_t temperature);
void LM75A_setFaultQueueValue(const LM75A_FaultQueueValue value);
void LM75A_setOsPolarity(const LM75A_OsPolarity polarity);
void LM75A_setDeviceMode(const LM75A_DeviceMode deviceMode);
_Bool LM75A_Is_Connected();
int8_t LM75A_getConfig();
float LM75A_getProdId();


#endif
