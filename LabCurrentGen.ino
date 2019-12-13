// Generatore da banco di corrente costante
#include "LabCurrentGen.h"
#include "Display.h"

SYSTEM_FLAGS Flags;

uint8_t DisplayPage = MAIN_MENU;

void setup()
{
	
}



void loop()
{
	switch(DisplayPage)
	{
		case MAIN_MENU:
			break;
		case CURRENT_CTRL:
			break;
		case DIGITAL_IO:
			break;
		case ANALOG:
			break;
		case MEASURES:
			break;
		case LOG:
			break;
		case LOG_GRAPHIC:
			break;
		case LOG_LIST:
			break;
		case STATISTICS:
			break;
		case SETUP:
			break;
		case RESET:
			break;
		default:
			break;
	}
}