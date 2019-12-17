#include "LabCurrentGen.h"
#include "Measure.h"

#define N_SAMPLE 	 50
#define ADC_TO_VOLT  0.0049
#define VOLTAGE 	 12.0

MEASURES_S Measures;

float CurrentAvgAcc = 0.0, PowerAvgAcc = 0.0, TemperatureAvgAcc = 0.0;
uint32_t AvgAcCnt = 0;

float CurrentSet;

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
	for(Sample = 0; Sample < N_SAMPLE; Sample++)
	{
		CurrentRead += analogRead(CURRENT_SENS_PIN);
	}
	CurrentRead /= N_SAMPLE;
	Measures.Current.Actual = (float)CurrentRead * ADC_TO_VOLT;
	Measures.Current.Actual = roundf(Measures.Current.Actual * 10) / 10;
	Measures.Power.Actual = Measures.Current.Actual * VOLTAGE;
	CalcTemperature();
	CalcMaxMin(&Measures.Current);
	CalcMaxMin(&Measures.Power);
	CalcAvg();
}



