uint16_t consecutiveCountsAboveLimit_1minute[3] = {0}; //[PhaseA, PhaseB, Phase C]
uint16_t consecutiveCountsAboveLimit_1second[3] = {0};
uint16_t consecutiveCountsAboveLimit_1sample[3] = {0};

#define MAX_PHASE_CURRENT_1MINUTE_AMPS 15
#define MAX_PHASE_CURRENT_1SECOND_AMPS 20
#define MAX_PHASE_CURRENT_1SAMPLE_AMPS 30

#define LOOP_RATE_MILLISECONDS 10

void setup(void)
{
	//configure PB2(ADC5) to measure analog input (goalRPM)
	//configure PC4(ADC8), PC5(ADC9), PB5(ADC6) to measure analog input (phase A/B/C current)
	//configure PC2(T0) to count edges (blue hall sensor)(to determine RPM (or rather, RPsecond))
	//configure PB4 as digital output (A4910 RESETn).  Resets faults when pulled low.  Disables A4910 when held low longer than tRSD = 10us
	//configure PC3 as digital output (grbl: slow down! (overload))
	//configure PC7 as digital input with pullup (A4910:DIAG).  A4910 pulls line low when fault occurs
}

void loop(void)
{
	//per-phase over-current analysis
	for(char ii = 'A'; ii <= 'C'; ii++)
	{
		//adc_measurePhaseCurrents(); //measure all three phases at the same time.  3x oversampled (to reduce noise) //result stored in adc_getPhaseCurrent(n)

		(adc_getPhaseCurrent(ii) < MAX_PHASE_CURRENT_1MINUTE_AMPS) ? (consecutiveCountsAboveLimit_1minute[ii] = 0) : consecutiveCountsAboveLimit_1minute[ii]++;
		(adc_getPhaseCurrent(ii) < MAX_PHASE_CURRENT_1SECOND_AMPS) ? (consecutiveCountsAboveLimit_1second[ii] = 0) : consecutiveCountsAboveLimit_1second[ii]++;
		(adc_getPhaseCurrent(ii) < MAX_PHASE_CURRENT_1SAMPLE_AMPS) ? (consecutiveCountsAboveLimit_1sample[ii] = 0) : consecutiveCountsAboveLimit_1sample[ii]++;

		if(1) {;}
	}
}