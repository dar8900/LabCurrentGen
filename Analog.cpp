#include "LabCurrentGen.h"
#include "Analog.h"

#define N_SAMPLE 	20

const char *Udm[MAX_ANALOG_UDM] = 
{
	"A",
	"ln",
	"m",
	"°C",
	"Ohm",
	"%",
	"db",
	"V",
	""
};


ANALOG_VALUES_S AnalogChannels[ANALOG_CHANNELS];


void AnalogChannelsInit()
{
	AnalogChannels[0].analogInput = ANALOG_1_PIN;
	AnalogChannels[1].analogInput = ANALOG_2_PIN;
	AnalogChannels[2].analogInput = ANALOG_3_PIN;
	AnalogChannels[3].analogInput = ANALOG_4_PIN;
	AnalogChannels[0].udm = RAW_VAL;
	AnalogChannels[1].udm = VOLTAGE;
	AnalogChannels[2].udm = RAW_VAL;
	AnalogChannels[3].udm = RAW_VAL;	
}

bool IsOneAnalogEnabled()
{
	bool isEnabled = false;
	for(int i = 0; i < ANALOG_CHANNELS; i++)
	{
		if(Flags.enableAnalogChannel[i])
		{
			isEnabled = true;
			break;
		}
	}
	return isEnabled;
}

void SwitchOffAnalogCh()
{
	for(int i = 0; i < ANALOG_CHANNELS; i++)
		Flags.enableAnalogChannel[i] = false;
}

void ReadAnalogChannels()
{
	int Sample = 0;
	if(IsOneAnalogEnabled())
	{
		for(int Channel = 0; Channel < ANALOG_CHANNELS; Channel++)
		{
			if(Flags.enableAnalogChannel[Channel])
			{
				for(Sample = 0; Sample < N_SAMPLE; Sample++) // 2ms a canale
				{
					AnalogChannels[Channel].analogVal += analogRead(AnalogChannels[Channel].analogInput);
				}
				AnalogChannels[Channel].analogVal /= N_SAMPLE;
				if(AnalogChannels[Channel].udm != RAW_VAL)
				{
					switch(AnalogChannels[Channel].udm)
					{
						case AMPERE:
							break;
						case LUMEN:
							break;
						case DISTANCE:
							break;
						case TEMPERATURE:
							break;
						case RESISTENCE:
							break;
						case HUMIDITY_PERC:
							break;
						case DECIBEL:
							break;
						case VOLTAGE:
							AnalogChannels[Channel].adcToVolT = (float)AnalogChannels[Channel].analogVal * ADC_TO_VOLT;
							AnalogChannels[Channel].udmVal = AnalogChannels[Channel].adcToVolT;
							break;
						default:
							break;
					}
				}
				else
					AnalogChannels[Channel].udmVal = (float)AnalogChannels[Channel].analogVal;
			}
			else
				AnalogChannels[Channel].analogVal = 0;
		}
	}
}