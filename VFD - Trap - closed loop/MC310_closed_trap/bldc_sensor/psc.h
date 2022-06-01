#ifndef _PSC_H_
	#define _PSC_H_

	#define PSC_PRESCALER PSC_NODIV_CLOCK
    //#define PSC_PRESCALER PSC_DIV_CLOCK_BY_4
    //#define PSC_PRESCALER PSC_DIV_CLOCK_BY_32
    
    #define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL
    //#define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_CLKIO

    #define PSC_MODE PSC_MODE_CENTERED

    #define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH

    //! @brief  Define all current decay types
    #define SLOW_DECAY 0
    #define FAST_DECAY 1
    #define SLOW_DECAY_SYNCHRONOUS 2

    //! @brief  Select here the current decay type for the application
    //#define CURRENT_DECAY SLOW_DECAY
    #define CURRENT_DECAY FAST_DECAY
    //#define CURRENT_DECAY SLOW_DECAY_SYNCHRONOUS

    #if (CURRENT_DECAY == FAST_DECAY)
        #define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW
    #else // SLOW_DECAY or SLOW_DECAY_SYNCHRONOUS
        #define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_HIGH
    #endif

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

    void psc_setDutyCycle(uint8_t level);

    // Over Current Detection
    //void mc_disableOvercurrentDuringStartup(void); //JTS2doLater
    //void mc_inrush_task(void); /* manage the inrush current */

#endif
