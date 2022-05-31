#ifndef _COMPARATOR_H_
	#define _COMPARATOR_H_

	/* Comparator 0 configuration */
    #define COMP0_ENABLE_BIT_VALUE COMP_ENABLE
    #define COMP0_INTERRUPT_ENABLE COMP_ENABLE_INTERRUPT
    #define COMP0_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
    #define COMP_CLOCK_SOURCE COMP_CLOCK_IO
    #define COMP0_NEG_INPUT_SELECT COMP_USE_BANDGAP

    /* Comparator 1 configuration */
    #define COMP1_ENABLE_BIT_VALUE COMP_ENABLE
    #define COMP1_INTERRUPT_ENABLE COMP_DISABLE_INTERRUPT
    #define COMP1_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
    #define COMP1_CAPTURE_ENABLE COMP_CAPTURE_DISABLE
    #define COMP1_NEG_INPUT_SELECT COMP_USE_DAC_OUTPUT

    /* Comparator 2 configuration */
    #define COMP2_ENABLE_BIT_VALUE COMP_ENABLE
    #define COMP2_INTERRUPT_ENABLE COMP_ENABLE_INTERRUPT
    #define COMP2_INTERRUPT_SELECT COMP_INTERRUPT_ON_OUTPUT_TOGGLE
    #define COMP2_NEG_INPUT_SELECT COMP_USE_BANDGAP

    /* Amplifier 1 configuration */
    #define AMP1_ENABLE_VALUE                AMP_ENABLE
    #define AMP1_INPUT_SHUNT_VALUE           AMP_SHUNT_DISABLE
    #define AMP1_GAIN                        AMP_GAIN_5
    #define AMP1_CMP1_CONNECTION_VALUE       AMP_CMP_CONNECTED
    #define AMP1_CLOCK_SOURCE                AMP_CLOCK_EQ_PSC0



    /* IMAX(counts) is calculated as follows:
    Rshunt           = 0.005 Ohm    // series resistance on each phase
    gain_opamp       = 16.5  V/V    // hardware gain using opamps inside A4910
    imax(amps)       = _____ A      // amps through any single phase
    Vref             = 2.56  V      // 32M1's internal reference
    ADC_counts       = 2^8   b      // ADC is left adjusted; only 8 MSBs read
    zero_current_b   = 0     counts // opamp component offset not used 
    IMAX(counts) = imax(amps) * Rshunt * gain_opamp * adc_counts / Vref + zero_current_b
    IMAX(counts) = imax(amps) * 0.005  * 16.5       * 256        / 2.56 + 0
    IMAX(counts) = imax(amps) * 8.25
    Conclusions:
    8.25 counts per amp through each phase 
    IMAX must be less than 254! */

    //#define IMAX 124 //imax(amps) = 15 amps in phase
    #define IMAX 165 //imax(amps) = 20 amps in phase
    //#define IMAX 206 //imax(amps) = 25 amps in phase
    //#define IMAX 248 //imax(amps) = 30 amps in phase

	/////////////////////////////////////////////////////////////////////////////////////

	void comparator_init(void);

#endif
