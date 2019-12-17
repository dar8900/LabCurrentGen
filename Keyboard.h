#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef enum 
{
	DECREMENT = 0,
	INCREMENT,
	OK,
	BACK,
	NO_PRESS
};


void KeyboardInit(void);

int CheckRotary(void);

#endif