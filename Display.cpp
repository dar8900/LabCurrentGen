#include "LabCurrentGen.h"
#include "Display.h"
#include <U8g2lib.h>
#include <SPI.h>

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);


void DisplayInit()
{
	u8g2.begin();
}

