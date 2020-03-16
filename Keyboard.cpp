#include "LabCurrentGen.h"
#include "Keyboard.h"

#define CW_DIR		1
#define CCW_DIR 	2

#define BACK_RELEASE_TIME 	500

static bool CWState = false, CCWState = false, OldCWState = false, OldCCWState = false;
static uint8_t ContaCW, ContaCCW;
static uint8_t ButtonPressed = NO_PRESS; 

typedef struct
{
    int pin_A;
    int pin_B;
    int rot_ok;
    int go_back;
}ROTARY_INPUT;

static ROTARY_INPUT Rotary;

void KeyboardInit()
{
    pinMode(ROTARY_A_PIN, INPUT);
    pinMode(ROTARY_B_PIN, INPUT);
    pinMode(ROTARY_BUTT_PIN, INPUT);
}



uint8_t RotaryDir()
{
	uint8_t Dir = 0;
	CWState = digitalRead(ROTARY_A_PIN);
	CCWState = digitalRead(ROTARY_B_PIN);
	if(OldCWState != CWState && OldCCWState == CCWState && ContaCW % 2)
	{
		Dir = CW_DIR;
		OldCWState = CWState;
		ContaCW++;
		DBG("Rotary -> Rotazione CW");
	}
	else if(OldCWState == CWState && OldCCWState != CCWState && ContaCCW % 2)
	{
		Dir = CCW_DIR;
		OldCCWState = CCWState;
		ContaCCW++;
		DBG("Rotary -> Rotazione CCW");
	}
	return Dir;
}


int CheckRotary()
{
	uint8_t Direction = RotaryDir();
	uint32_t RotButtTime = 0;
	if(Direction)
	{
		if(Direction == CW_DIR)
		{
			DBG("Rotary -> Incremento");
			delay(50);
			return INCREMENT;
		}
		else if(Direction == CCW_DIR)
		{
			DBG("Rotary -> decremento");
			delay(50);
			return DECREMENT;
		}
	}
	Rotary.rot_ok = digitalRead(ROTARY_BUTT_PIN);
    if(Rotary.rot_ok == LOW)
    {
		DBG("Rotary -> bottone premuto");
		RotButtTime = millis();
		while(digitalRead(ROTARY_BUTT_PIN) == LOW)
		{
			delay(50);
			if(millis() - RotButtTime >= BACK_RELEASE_TIME)
				break;
		}
		if(millis() - RotButtTime < BACK_RELEASE_TIME)
		{
			if(ButtonPressed == BACK)
			{
				ButtonPressed = NO_PRESS;
			}
			else
			{
				DBG("Rotary -> bottone premuto -> OK");
				return OK;
			}
		}
		else
		{
			if(ButtonPressed == NO_PRESS)
			{
				DBG("Rotary -> bottone premuto -> BACK");
				ButtonPressed = BACK;
				return BACK;
			}
		}
    }
    return NO_PRESS;
}
