#ifndef LABCURRENTGEN_H
#define LABCURRENTGEN_H

#include <Arduino.h>
#include <stdint.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <TimerThree.h>
#include <Chrono.h>
#include <DHT.h>

// Comunication
#define SCL_PIN				 0
#define SDA_PIN				 1 

// Display e digital pin
#define BACK_BUTT_PIN		 6
#define ROTARY_A_PIN		 7
#define ROTARY_B_PIN         8
#define ROTARY_BUTT_PIN      9
#define DIGITAL_IN			10
#define DIGITAL_OUT			11
#define DHT_PIN				12
#define RESET_DISPLAY_PIN   19
#define CS_DISPLAY_PIN		20
#define CURRENT_REG_PIN 	25

// Analog pin
#define ANALOG_1_PIN		A1
#define ANALOG_2_PIN		A2
#define ANALOG_3_PIN		A3
#define ANALOG_4_PIN		A4
#define CURRENT_SENS_PIN 	A5

#define DHTTYPE DHT11 

#define PIGRECO               3.141592653
#define TO_GRADES(Angle)     (Angle * (180.0 / PIGRECO))
#define TO_RADIANTS(Angle)   (Angle * (PIGRECO / 180.0))

#define MIN_TO_SEC(min)		 (min * 60)

typedef struct 
{
	bool enableLog;
	bool enableAnalog_1;
	bool enableanalog_2;
	bool enableanalog_3;
	bool enableanalog_4;
	bool enableCurrent;

}SYSTEM_FLAGS;

typedef enum 
{
	MAIN_MENU = 0,
	CURRENT_CTRL,
	DIGITAL_IO,
	ANALOG,
	MEASURES,
	LOG,
	STATISTICS,
	SETUP,
	RESET,
	SETUP_PARAM,
	MAX_DISPLAY_PAGES
}DISPLAY_PAGES;



extern SYSTEM_FLAGS Flags;
extern uint8_t DisplayPage;

#endif