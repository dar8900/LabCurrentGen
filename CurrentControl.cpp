#include "LabCurrentGen.h"
#include "CurrentControl.h"
#include "Measure.h"

static uint16_t CurrentPwm;

static void WritePwmSignal(uint16_t DutyCycle)
{
	if(DutyCycle > 255)
		DutyCycle = 255;
	analogWrite(CURRENT_REG_PIN, DutyCycle);
}

void CurrentControlInit()
{
	pinMode(CURRENT_REG_PIN, OUTPUT);
	WritePwmSignal(0);
}

void CtrlCurrentExit()
{
	int CurrentSetted = 0, CurrentMis = 0;
	if(Flags.enableCurrent)
	{
		CurrentMis = (int)(roundf(Measures.Current.Actual * 10));
		CurrentSetted = (int)(roundf(CurrentSet * 10));
		if(CurrentMis < CurrentSetted)
		{
			if(CurrentPwm < MAX_CURRENT_PWM)
				CurrentPwm++;
		}
		else if(CurrentMis > CurrentSetted)
		{
			if(CurrentPwm > MIN_CURRENT_PWM)
				CurrentPwm--;			
		}
	}
	else
		CurrentPwm = 0;
	WritePwmSignal(CurrentPwm);
}