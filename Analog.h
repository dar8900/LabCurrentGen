#ifndef ANALOG_h
#define ANALOG_h
#include <stdint.h>



typedef enum 
{
	AMPERE = 0,
	LUMEN,
	DISTANCE,
	TEMPERATURE,
	RESISTENCE,
	HUMIDITY_PERC,
	DECIBEL,
	VOLTAGE,
	RAW_VAL,
	MAX_ANALOG_UDM
}UDM_TYPE;


typedef struct 
{
	int analogInput;
	int32_t analogVal;
	float adcToVolT;
	float conversionV_Udm;
	float udmVal;
	uint8_t udm;
}ANALOG_VALUES_S;

extern const char *Udm[MAX_ANALOG_UDM];
extern ANALOG_VALUES_S AnalogChannels[];

void AnalogChannelsInit(void);
bool IsOneAnalogEnabled(void);
void SwitchOffAnalogCh(void);
void ReadAnalogChannels(void);

#endif