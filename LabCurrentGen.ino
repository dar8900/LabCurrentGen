// Generatore da banco di corrente costante
#include "LabCurrentGen.h"
#include "Display.h"
#include "Keyboard.h"
#include "CurrentControl.h"
#include "Time.h"
#include "Measure.h"

SYSTEM_FLAGS Flags;

uint8_t DisplayPage = MAIN_MENU;

void setup()
{
	DisplayInit();
	KeyboardInit();
	CurrentControlInit();
	TimeInit();
	TempSensInit();
}



void loop()
{
	switch(DisplayPage)
	{
		case MAIN_MENU:
			DrawMainMenu();
			break;
		case CURRENT_CTRL:
			DrawCurrentCtrl();
			break;
		case DIGITAL_IO:
			break;
		case ANALOG:
			break;
		case MEASURES:
			break;
		case LOG:
			break;
		case STATISTICS:
			break;
		case SETUP:
			break;
		case SETUP_PARAM:
			break;
		case RESET:
			break;
		default:
			break;
	}
}