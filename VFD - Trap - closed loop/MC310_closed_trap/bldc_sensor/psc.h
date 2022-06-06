#ifndef _PSC_H_
	#define _PSC_H_

	#define PSC_PRESCALER PSC_NODIV_CLOCK
    //#define PSC_PRESCALER PSC_DIV_CLOCK_BY_4
    //#define PSC_PRESCALER PSC_DIV_CLOCK_BY_32
    
    //#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL
    #define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_CLKIO

    #define PSC_MODE PSC_MODE_CENTERED

    #define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH
	#define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW

    #define A_SA_VAL 0 //!< POCR0SA = 0 for no pulse at init
    #define A_RA_VAL 1 //!< POCR0RA = 1 to synchronize the ADC at the center of the waveform
    #define A_SB_VAL 0 //!< POCR0SB = 0 for no pulse at init

    #define B_SA_VAL 0 //!< POCR1SA = 0 for no pulse at init
    #define B_RA_VAL 1
    #define B_SB_VAL 0 //!< POCR1SB = 0 for no pulse at init

    #define C_SA_VAL 0 //!< POCR2SA = 0 for no pulse at init
    #define C_RA_VAL 1
    #define C_SB_VAL 0 //!< POCR2SB = 0 for no pulse at init

    #define RB_VAL 254 //POCR_RB //PWM freq = f_PLL/RB_VAL //PSC timer counts to this value

    #define DEADTIME 2 //!< Dead Time for the inverter

    ////////////////////////////////////////////////////////////////////////////

    void psc_init (void);

    void psc_commutateOutputWaveforms(uint8_t duty);

    void psc_disconnectAllMOSFETs(void);

    void psc_connectAllMOSFETs(void);

    // Over Current Detection
    //void mc_disableOvercurrentDuringStartup(void); //JTS2doLater
    //void mc_inrush_task(void); /* manage the inrush current */

#endif
