#ifndef TIME_H
#define TIME_H
#include <Arduino.h>

#define DFLT_HOUR	      0
#define DFLT_MINUTE       0
#define DFLT_DAY          0
#define DFLT_MONTH        1
#define DFLT_YEAR        20


typedef struct
{
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
	uint8_t Day;
	uint8_t Month;
	uint16_t Year;
	String TimeStr;
	String DateStr;
	bool IsRunning;
}TIME_DATE_S;

extern const uint8_t DayInMonth[];
extern TIME_DATE_S GlobalTime;
extern uint32_t TimeOn;

void TimeInit(void);
void GetTime(void);
void SetTime(uint8_t hour, uint8_t minute);
void SetDate(uint8_t day, uint8_t month, uint8_t year);
void CtrlTimeOn(bool Reset);

#endif