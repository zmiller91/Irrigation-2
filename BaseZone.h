// BaseZone.h

#ifndef _BASEZONE_h
#define _BASEZONE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class BaseZone
{
protected:
	int NUM_BITS = 24;
	int m_bitmask[24];
	void putToRegister();
	void ledOneByOne(int);
	int NUM_REGISTERS;
	String m_name;

	// Each zone contains 3 daisy chained 8-bit shift registers
	// and 15 LED status lights.  The LEDs can be mapped to bits 9-23 
	// in the chained register. Bits 0-8 in the register  are available 
	// for use. These first 24 entries in the zone represent it's register. 
	// To use, set the bit value of each of these register entries 
	// to either turn on or off an action in the zone.

	int REG_01 = 0;
	int REG_02 = 1;
	int REG_03 = 2;
	int REG_04 = 3;
	int REG_05 = 4;
	int REG_06 = 5;
	int REG_07 = 6;
	int REG_08 = 7;
	int REG_09 = 8;

	int LED_01 = 9;
	int LED_02 = 10;
	int LED_03 = 11;
	int LED_04 = 12;
	int LED_05 = 13;
	int LED_06 = 14;
	int LED_07 = 15;
	int LED_08 = 16;
	int LED_09 = 17;
	int LED_10 = 18;
	int LED_11 = 10;
	int LED_12 = 20;
	int LED_13 = 21;
	int LED_14 = 22;
	int LED_15 = 23;

	// Variables below here are not required for basic integration.  These
	// are now application variables and are used solely for the application
	// of this irrigation system

	// Map moisture sensor leds to register
	int MOISTURE_LED_LOW = LED_01;
	int MOISTURE_LED_LMED = LED_02;
	int MOISTURE_LED_GOOD = LED_03;
	int MOISTURE_LED_HMED = LED_04;
	int MOISTURE_LED_HIGH = LED_05;

	// Map temp sensor leds to register
	int TEMP_LED_LOW = LED_06;
	int TEMP_LED_LMED = LED_07;
	int TEMP_LED_GOOD = LED_08;
	int TEMP_LED_HMED = LED_09;
	int TEMP_LED_HIGH = LED_10;

	// Map pH sensor leds to register
	int PH_LED_LOW = LED_11;
	int PH_LED_LMED = LED_12;
	int PH_LED_GOOD = LED_13;
	int PH_LED_HMED = LED_14;
	int PH_LED_HIGH = LED_15;

	// Map zone functions to register
	int MOISTURE_SENSOR_PWR = REG_01;
	int PUMP_PWR = REG_02;
	int PERI_PUMP = REG_03;
	int MIXER_PWR = REG_04;
	int PHDOWN_PWR = REG_05;
	int PHUP_PWR = REG_06;
	int SOLENOID_PWR = REG_07;
	int LIGHT_PWR = REG_08;
	int FAN_PWR = REG_09;

	// Map zone sensors to register
	int MOISTURE_SENSOR;
	int PHOTORESISTOR;
	int TEMP_SENSOR;
	int HUMIDITY_SENSOR;
	int DATA_PIN;
	int LATCH_PIN;
	int CLOCK_PIN;

	/*
	* Strings are insanely expensive when limited to 36k of free
	* memory.  In order to use as few free memory as possible, we
	* need to map common actions and components to IDs so that we
	* can map the serial output to an action or component. Below
	* are the maps for common actions and components.
	*/

	// TODO: We should rethink this conf. It probably needs to go in a super
	// duper base class that everything inherits.  That way we aren't
	// duplicating work in Component.cpp



public:
	BaseZone();
	BaseZone(String name, int data, int latch, int clock, int moisture, int photo, int temp, int humidity);
	void test();
	void allOn();
	void allOff();
	void ledBlink(int);
};

#endif

