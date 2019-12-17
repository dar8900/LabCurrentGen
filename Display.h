#ifndef DISPLAY_H
#define DISPLAY_H


#define DISPLAY_WIDTH	    128
#define DISPLAY_HIGH	     64

#define STR_WIDTH(Str)      u8g2.getStrWidth(Str)
#define STR_HIGH         	u8g2.getAscent()

#define LEFT_ALIGN 	        0
#define RIGHT_ALIGN(Str) 	(DISPLAY_WIDTH - u8g2.getStrWidth(Str))
#define CENTER_ALIGN(Str) 	((DISPLAY_WIDTH - u8g2.getStrWidth(Str)) / 2)

#define TOP_POS				(1 + u8g2.getAscent())
#define CENTER_POS			((DISPLAY_HIGH/2) + (u8g2.getAscent() / 2))
#define BOTTOM_POS			(DISPLAY_HIGH  - u8g2.getAscent())

#define TITLE_Y_POS 		 7
#define MENU_LIST_Y_POS 	18
#define MAX_MENU_VIEW_ITEM	 5


typedef enum 
{
	CURRENT_CTRL_ITEM = 0,
	DIGITAL_IO_ITEM,
	ANALOG_ITEM,
	MEASURE_ITEM,
	LOG_ITEM,
	STATISTICS_ITEM,
	SETUP_ITEM,
	RESET_ITEM,
	MAX_MAIN_MENU_ITEMS
}MAIN_MENU_ITEMS;

typedef enum
{
	DIGITAL_INPUT_ITEM = 0,
	DIGITAL_OUTPUT_ITEM,
	MAX_DIGITAL_ITEMS
}DIGITAL_ITEMS;

typedef enum
{
	ANALOG_1_ITEM = 0,
	ANALOG_2_ITEM,
	ANALOG_3_ITEM,
	ANALOG_4_ITEM,
	MAX_ANALOG_ITEMS
}ANALOG_ITEMS;

typedef enum
{
	LOG_LIST_ITEM = 0,
	MAX_LOG_ITEMS
}LOG_ITEMS;

typedef enum
{
	MAX_CURRENT_ITEM = 0,
	MIN_CURRENT_ITEM,
	AVG_CURRENT_ITEM,
	MAX_POWER_ITEM,
	MIN_POWER_ITEM,
	AVG_POWER_ITEM,
	ANALOG_1_OUT_EN_ITEM,
	ANALOG_2_OUT_EN_ITEM,
	ANALOG_3_OUT_EN_ITEM,
	ANALOG_4_OUT_EN_ITEM,
	TIME_ON_ITEM,
	MAX_TEMPERATURE_ITEM,
	MIN_TEMPERATURE_ITEM,
 	AVG_TEMPERATURE_ITEM,
	MAX_STATISTICS_ITEMS
}STATISTICS_ITEMS;

typedef enum
{
	SET_TIME_ITEM = 0,
	SET_DATE_ITEM,
	AVG_CALC_TIME,
	MAX_SETUP_ITEMS
}SETUP_ITEMS;

typedef enum
{
	RESET_MAX_MIN_AVG_ITEM = 0,
	RESET_TIME_ON_ITEM,
	MAX_RESET_ITEMS
}RESET_ITEMS;

void DisplayInit(void);
void DrawPopUp(const String Str1 = "", const String Str2 = "", const String Str3 = "");
void DrawMainMenu(void);
void DrawCurrentCtrl(void);
void DrawAnalogPages(void);

#endif