#include "LabCurrentGen.h"
#include "Keyboard.h"

#undef USE_ROTARY	

#ifdef USE_ROTARY
#define CW_DIR		1
#define CCW_DIR 	2
#endif

#define BACK_RELEASE_TIME 	500

#ifdef USE_ROTARY
static bool CWState = false, CCWState = false, OldCWState = false, OldCCWState = false;
static uint8_t ContaCW, ContaCCW;
#endif

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


#ifdef USE_ROTARY
uint8_t RotaryDir()
{
	uint8_t Dir = 0;
	CWState = digitalRead(ROTARY_A_PIN);
	CCWState = digitalRead(ROTARY_B_PIN);
	if(OldCWState != CWState && OldCCWState == CCWState)
	{
		if(ContaCW % 2 == 0)
		{
			Dir = CW_DIR;
			OldCWState = CWState;
			DBG("Rotary -> Rotazione CW");
		}
		ContaCW++;
	}
	else if(OldCWState == CWState && OldCCWState != CCWState)
	{
		if(ContaCCW % 2 == 0)
		{
			Dir = CCW_DIR;
			OldCCWState = CCWState;
			DBG("Rotary -> Rotazione CCW");
		}
		ContaCCW++;
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


#else

int CheckRotary()
{
	uint32_t RotButtTime = 0;
	Rotary.pin_A = digitalRead(ROTARY_A_PIN);
	Rotary.pin_B = digitalRead(ROTARY_B_PIN);
	Rotary.rot_ok = digitalRead(ROTARY_BUTT_PIN);
	if(Rotary.pin_A == LOW)
	{
		DBG("Rotary -> bottone UP premuto");
		return DECREMENT;
	}
	if(Rotary.pin_B == HIGH)
	{
		DBG("Rotary -> bottone DOWN premuto");
		return INCREMENT;	
	}
    if(Rotary.rot_ok == HIGH)
    {
		DBG("Rotary -> bottone premuto");
		RotButtTime = millis();
		while(digitalRead(ROTARY_BUTT_PIN) == HIGH)
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

#endif
