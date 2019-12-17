#include "LabCurrentGen.h"
#include "Keyboard.h"

typedef struct
{
    int last_pin_A;
    int pin_A;
    int pin_B;
    int rot_ok;
    int go_back;
}ROTARY_INPUT;

static ROTARY_INPUT Rotary;

void KeyboardInit()
{
    pinMode(BACK_BUTT_PIN, INPUT);
    pinMode(ROTARY_A_PIN, INPUT);
    pinMode(ROTARY_B_PIN, INPUT);
    pinMode(ROTARY_BUTT_PIN, INPUT);
    Rotary.last_pin_A = digitalRead(ROTARY_A_PIN);
}

int CheckRotary()
{
    Rotary.pin_A = digitalRead(ROTARY_A_PIN);
    Rotary.pin_B = digitalRead(ROTARY_B_PIN);
    Rotary.rot_ok = digitalRead(ROTARY_BUTT_PIN);
    Rotary.go_back = digitalRead(BACK_BUTT_PIN);
    if(Rotary.pin_A != Rotary.last_pin_A)
    {
        if(Rotary.pin_B != Rotary.pin_A)
        {
            Rotary.last_pin_A = Rotary.pin_A;
            delay(20);
            return INCREMENT;
        }
        else
        {
            Rotary.last_pin_A = Rotary.pin_A;
            delay(20);
            return DECREMENT;
        }
    }
    if(Rotary.rot_ok == HIGH)
    {
        delay(20);
        return OK;
    }
    if(Rotary.go_back == HIGH)
    {
        delay(20);
        return BACK;
    }
    return NO_PRESS;
}
