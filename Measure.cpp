#include "LabCurrentGen.h"
#include "Measure.h"

#define N_SAMPLE 	 50
#define VOLTAGE 	 12.0

MEASURES_S Measures;

float CurrentAvgAcc = 0.0, PowerAvgAcc = 0.0, TemperatureAvgAcc = 0.0;
uint32_t AvgAcCnt = 0;

float CurrentSet;
int AdcCurrentOffSet;

Chrono CalcAvgTotTimer(Chrono::SECONDS);
Chrono CalcAvgTimer;
Chrono TakeTempTimer;

DHT SensorDht11(DHT_PIN, DHTTYPE);

static void CalcMaxMin(SINGLE_MEASURE_S *Measure)
{
	float ActualForMinMeasure = roundf(Measure->Min * 1000) / 1000;
	if(Measure->Max < Measure->Actual)
		Measure->Max = Measure->Actual;
	if(Measure->Min > Measure->Actual && ActualForMinMeasure != 0.0f)
	{
		Measure->Min = Measure->Actual;
	}
	else
		Measure->Min = Measure->Max;
}
static void CalcAvg()
{
	if(CalcAvgTotTimer.hasPassed(MIN_TO_SEC(5), true)) // Ogni 5 min
	{
		CalcAvgTimer.stop();
		Measures.Current.Avg = (CurrentAvgAcc / AvgAcCnt);
		Measures.Power.Avg = (PowerAvgAcc / AvgAcCnt);
		Measures.Temperature.Avg = (TemperatureAvgAcc / AvgAcCnt);
		CurrentAvgAcc = 0.0;
		PowerAvgAcc = 0.0;
		TemperatureAvgAcc = 0.0;
		AvgAcCnt = 0;
		CalcAvgTimer.restart();
	}
	else
	{
		if(CalcAvgTimer.hasPassed(500, true)) // Ogni mezzo secondo
		{
			CurrentAvgAcc += Measures.Current.Actual;
			PowerAvgAcc += Measures.Power.Actual;
			TemperatureAvgAcc += Measures.Temperature.Actual;
			AvgAcCnt++;
		}
	}
}

static void CalcTemperature()
{
	if(TakeTempTimer.hasPassed(500, true))
	{
		Measures.Temperature.Actual = SensorDht11.readTemperature();
		if(isnan(Measures.Temperature.Actual))
			Measures.Temperature.Actual = 0.0;
		CalcMaxMin(&Measures.Temperature);
	}
}

void TempSensInit()
{
	SensorDht11.begin();
}

void CalcMeasures()
{
	int Sample = 0;
	uint32_t CurrentRead = 0;
	if(Flags.enableCurrent)
	{
		// Tempo 5ms 
		for(Sample = 0; Sample < N_SAMPLE; Sample++)
		{
			CurrentRead += analogRead(CURRENT_SENS_PIN);
		}
		CurrentRead /= N_SAMPLE;
		CurrentRead -= AdcCurrentOffSet;
		Measures.Current.Actual = (float)CurrentRead * ADC_TO_VOLT / ACS20_VOLT_TO_AMPS;
		Measures.Current.Actual = roundf(Measures.Current.Actual * 10) / 10;
		Measures.Power.Actual = Measures.Current.Actual * VOLTAGE;
	}
	else
	{
		for(Sample = 0; Sample < 10; Sample++)
		{
			CurrentRead += analogRead(CURRENT_SENS_PIN);
		}		
		AdcCurrentOffSet = CurrentRead / 10;
		Measures.Current.Actual = 0.0;
		Measures.Power.Actual = 0.0;		
	}

	CalcMaxMin(&Measures.Current);
	CalcMaxMin(&Measures.Power);
	CalcTemperature();
	CalcAvg();
}


void ResetMaxMinAvg()
{
	Measures.Current.Max = 0.0;
	Measures.Current.Min = 0.0;
	Measures.Current.Avg = 0.0;
	Measures.Power.Max = 0.0;
	Measures.Power.Min = 0.0;
	Measures.Power.Avg = 0.0;
	Measures.Temperature.Max = 0.0;
	Measures.Temperature.Min = 0.0;
	Measures.Temperature.Avg = 0.0;
}

