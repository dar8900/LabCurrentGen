#include "LabCurrentGen.h"
#include "Display.h"
#include <U8g2lib.h>
#include <SPI.h>
#include "Keyboard.h"
#include "Time.h"
#include "Measure.h"
#include "CurrentControl.h"

#define SET_TOP_BAR_FONT (u8g2.setFont(u8g2_font_4x6_mf))
#define SET_MENUS_FONT  (u8g2.setFont(u8g2_font_6x10_mf)) // alto 6 largo 10 monospace 
#define SET_TITLE_FONT 	(u8g2.setFont(u8g2_font_8x13B_mf))

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, CS_DISPLAY_PIN, RESET_DISPLAY_PIN);


static const char *MainMenuTitles[MAX_MAIN_MENU_ITEMS] = 
{
	"Controllo corrente",
	"Digital IN/OUT",
	"Entrate analogiche",
	"Misure",
	"Lista log",
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

static void DoTasks()
{
	CalcMeasures();
	CtrlCurrentExit();
	GetTime();
	CtrlTimeOn(false);
}

static void DrawTopInfo()
{
	String TimeStr = GlobalTime.TimeStr + " " + GlobalTime.DateStr;
	SET_TOP_BAR_FONT;
	u8g2.drawStr(LEFT_ALIGN, TOP_POS + STR_HIGH, TimeStr.c_str());
}

static void DrawMenuList(uint8_t TopItem, uint8_t ItemSel, uint8_t MaxItems, const char **MenuVoices)
{
	int NewTopItem = 0, StrHigh = 0;
	SET_TITLE_FONT;
	u8g2.drawStr(CENTER_ALIGN("Menu"), TITLE_Y_POS + STR_HIGH, "Menu");
	SET_MENUS_FONT;
	StrHigh = STR_HIGH;
	for(int i = 0; i < MAX_MENU_VIEW_ITEM; i++)
	{
		NewTopItem = TopItem + i;
		if(NewTopItem >= MaxItems)
			break;
		u8g2.drawStr(LEFT_ALIGN, (MENU_LIST_Y_POS + StrHigh) + (i * (StrHigh + 2)), MenuVoices[NewTopItem]);
		if(NewTopItem == ItemSel)
		{
			u8g2.setFontMode(0);
			u8g2.setDrawColor(2);
			u8g2.drawBox(LEFT_ALIGN, (MENU_LIST_Y_POS + StrHigh) + (i * 2)  - 1, 
						 STR_WIDTH(MenuVoices[NewTopItem]) + 1, StrHigh + 2);	
		}	
	}

}

void DrawMainMenu()
{
	bool ExitMainMenu = false;
	uint8_t TopItem = 0, ItemList = 0, ItemSel = 0, RotaryState = NO_PRESS;
	
	while(!ExitMainMenu)
	{
		DoTasks();
		u8g2.clearBuffer();
		DrawTopInfo();
		DrawMenuList(TopItem, ItemList, MAX_MAIN_MENU_ITEMS, MainMenuTitles);
		u8g2.sendBuffer();
		RotaryState = CheckRotary();
		switch(RotaryState)
		{
			case DECREMENT:
				if(ItemList > 0)
					ItemList--;
				else
					ItemList = MAX_MAIN_MENU_ITEMS - 1;
				break;
			case INCREMENT:
				if(ItemList < MAX_MAIN_MENU_ITEMS - 1)
					ItemList++;
				else
					ItemList = 0;			
				break;
			case OK:
				DisplayPage = ItemSel + 1;
				ExitMainMenu = true;
				break;
			case BACK:
			default:
				break;
		}
		if(ItemList > MAX_MENU_VIEW_ITEM - 1)
		{
			TopItem = ItemList - MAX_MENU_VIEW_ITEM - 1;
		}
		else
			TopItem = 0;
		if(ItemList < MAX_MAIN_MENU_ITEMS - 3)
		{
			if(ItemList < MAX_MENU_VIEW_ITEM - 2)
				ItemSel = ItemList;
			else
				ItemSel = TopItem  + 3;
		}
		else
			ItemSel = MAX_MAIN_MENU_ITEMS - 1 - ItemList;		
	}
}

static void CurrentCtrlScreen(uint8_t Current)
{
	String CurrValueMis = "", CurrValueSet = "";
	float CurrentSetFl = (float)Current / 10;
	CurrValueMis = String(Measures.Current.Actual, 1);
	CurrValueSet = String(CurrentSetFl, 1);
	SET_TITLE_FONT;
	u8g2.drawStr(CENTER_ALIGN("Reg. I"), TITLE_Y_POS + STR_HIGH, "Reg. I");
	u8g2.setFont(u8g2_font_9x15B_mf);
	u8g2.drawStr(LEFT_ALIGN, MENU_LIST_Y_POS + STR_HIGH, CurrValueSet.c_str());
	u8g2.drawStr(RIGHT_ALIGN(CurrValueMis.c_str()), MENU_LIST_Y_POS + STR_HIGH, CurrValueMis.c_str());
	u8g2.drawStr(CENTER_ALIGN("-->"), MENU_LIST_Y_POS + STR_HIGH, "-->");
}

void DrawCurrentCtrl()
{
	bool ExitCurrentCrtl = false, CurrenEnable = false;
	uint8_t Current = 0, RotaryState = NO_PRESS;
	while(!ExitCurrentCrtl)
	{
		DoTasks();
		u8g2.clearBuffer();
		DrawTopInfo();
		CurrentCtrlScreen(Current);
		u8g2.sendBuffer();		
		switch(RotaryState)
		{
			case DECREMENT:
				if(Current > 0 && !CurrenEnable)
					Current--;
				break;
			case INCREMENT:
				if(Current < 50 && !CurrenEnable)
					Current++;			
				break;
			case OK:
				CurrenEnable = !CurrenEnable;
				Flags.enableCurrent = CurrenEnable;
				if(CurrenEnable)
					CurrentSet = (float)Current / 10;
				break;
			case BACK:
				DisplayPage = MAIN_MENU;
				ExitCurrentCrtl = true;
				break;
			default:
				break;
		}
	}
}