#include "LabCurrentGen.h"
#include "Time.h"

TIME_DATE_S GlobalTime;

RTC_DS1307 rtc;

uint32_t TimeOn;

Chrono TimeOnTimer(Chrono::SECONDS);

const uint8_t DayInMonth[12] = 
{
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31,	
};

static DateTime now;


void TimeSetup()
{
	if (!rtc.begin())
	{
		GlobalTime.TimeStr = "--:--";
		GlobalTime.DateStr = "--/--/--";
		GlobalTime.TimeStr = "--:--";
		GlobalTime.DateStr = "--/--/--";
		GlobalTime.Hour = DFLT_HOUR;
		GlobalTime.Minute = DFLT_MINUTE;
		GlobalTime.Second = 0;
		GlobalTime.Day = DFLT_DAY;
		GlobalTime.Month = DFLT_MONTH;
		GlobalTime.Year = DFLT_YEAR + 2000;				
		GlobalTime.IsRunning = false;
	}
	else if (!rtc.isrunning())
	{
		GlobalTime.TimeStr = "--:--";
		GlobalTime.DateStr = "--/--/--";
		GlobalTime.Hour = DFLT_HOUR;
		GlobalTime.Minute = DFLT_MINUTE;
		GlobalTime.Second = 0;
		GlobalTime.Day = DFLT_DAY;
		GlobalTime.Month = DFLT_MONTH;
		GlobalTime.Year = DFLT_YEAR + 2000;		
		SetTime(DFLT_HOUR, DFLT_MINUTE);
		GetTime();
	}
	else
	{
		GlobalTime.IsRunning = true;
		CtrlTimeOn(true);
		GetTime();
	}
}

void GetTime()
{
	now = rtc.now();
	GlobalTime.Hour = now.hour();
	GlobalTime.Minute = now.month();
	GlobalTime.Second = now.second();
	GlobalTime.Day = now.day();
	GlobalTime.Month = now.month();
	GlobalTime.Year = now.year();

	GlobalTime.TimeStr = (GlobalTime.Hour > 9 ? String(GlobalTime.Hour) : ("0" + String(GlobalTime.Hour)));
	GlobalTime.TimeStr += ":" + (GlobalTime.Minute > 9 ? String(GlobalTime.Minute) : ("0" + String(GlobalTime.Minute)));

	GlobalTime.DateStr = (GlobalTime.Day > 9 ? String(GlobalTime.Day) : ("0" + String(GlobalTime.Day)));
	GlobalTime.DateStr += "/" + (GlobalTime.Month > 9 ? String(GlobalTime.Month) : ("0" + String(GlobalTime.Month)));
	GlobalTime.DateStr += "/" + String(GlobalTime.Year % 100);
}

void SetTime(uint8_t hour, uint8_t minute)
{
	rtc.adjust(DateTime(GlobalTime.Year, GlobalTime.Month, GlobalTime.Day, hour, minute, 0));
}

void SetDate(uint8_t day, uint8_t month, uint8_t year)
{
	uint16_t Year = year + 2000;
	rtc.adjust(DateTime(Year, month, day, GlobalTime.Hour, GlobalTime.Minute, 0));
}

void CtrlTimeOn(bool Reset)
{
	if(Reset)
	{
		TimeOnTimer.restart();
		TimeOn = 0;
	}
	else
	{
		if(TimeOnTimer.hasPassed(1, true))
			TimeOn++;
	}
}