#include "LabCurrentGen.h"
#include "Display.h"
#include <U8g2lib.h>
#include <SPI.h>
#include "Time.h"
#include "Measure.h"

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, CS_DISPLAY_PIN, RESET_DISPLAY_PIN);


static const char *MainMenuTitles[MAX_MAIN_MENU_ITEMS] = 
{
	"Controllo corrente",
	"Digital IN/OUT",
	"Entrate analogiche",
	"Misure",
	"Menu dei log",
	"Statistiche",
	"Setup",
	"Menu dei reset"
};

static const char *DigitalTitles[MAX_DIGITAL_ITEMS] = 
{
	"Dig. INPUT",
	"Dig. OUTPUT",
};

static const char *AnalogTitles[MAX_ANALOG_ITEMS] = 
{
	"Entrata an. 1",
	"Entrata an. 2",
	"Entrata an. 3",
	"Entrata an. 4",
};


static const char *LogTitles[MAX_LOG_ITEMS] = 
{
	"Grafico log",
	"Lista log",
};

static const char *StatisticsTitles[MAX_STATISTICS_ITEMS] = 
{
	"Corrente max.",
	"Corrente min.",
	"Corrente med.",
	"Potenza max.",
	"Potenza min.",
	"Potenza med.",
	"Entrata an. 1",
	"Entrata an. 2",
	"Entrata an. 3",
	"Entrata an. 4",
	"Tempo acceso",
	"Temperatura max.",
	"Temperatura min.",
	"Temperatura med.",
};

static const char *SetupTitles[MAX_SETUP_ITEMS] = 
{
	"Imposta ora",
	"Imposta data",
};

static const char *ResetTitles[MAX_RESET_ITEMS] = 
{
	"Reset max/min/avg",
	"Reset tempo acceso",
};

void DisplayInit()
{
	u8g2.begin();
}



