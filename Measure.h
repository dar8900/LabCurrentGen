#ifndef MEASURE_H
#define MEASURE_H

typedef struct 
{
	float Actual;
	float Max;
	float Min;
	float Avg;
}SINGLE_MEASURE_S;

typedef struct 
{
	SINGLE_MEASURE_S Current;
	SINGLE_MEASURE_S Power;
	SINGLE_MEASURE_S Temperature;
}MEASURES_S;

extern MEASURES_S Measures;
extern float CurrentSet;

void CalcMeasures(void);
void TempSensInit(void);


#endif