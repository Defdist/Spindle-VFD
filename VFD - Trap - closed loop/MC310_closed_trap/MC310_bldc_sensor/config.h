#ifndef _CONFIG_H_
    #define _CONFIG_H_

    #define SOFT_ID 1 /* 0:unknown, 1:bldc sensor, 2:bldc sinus, 3:bldc sensorless */
    #define REV_ID 1

    /*-------------- UART LIB CONFIGURATION ---------------*/

    #define BAUDRATE      38400
    #define FOSC          16000 //kHz

    /* DAC configuration */
    #define DAC_AUTOTRIG_ENABLE_VALUE        DAC_AUTOTRIG_DISABLE
    #define DAC_TRIGGER_SELECTION            DAC_TRIG_WITH_COMP0
    #define DAC_LEFT_ADJUST_VALUE            DAC_LEFT_ADJUST
    #define DAC_OUTPUT_ENABLE_VALUE          DAC_OUTPUT_DISABLE
    #define DAC_ENABLE_VALUE                 DAC_ENABLE


    /* Amplifier 1 configuration */
    #define AMP1_ENABLE_VALUE                AMP_ENABLE
    #define AMP1_INPUT_SHUNT_VALUE           AMP_SHUNT_DISABLE
    #define AMP1_GAIN                        AMP_GAIN_5
    #define AMP1_CMP1_CONNECTION_VALUE       AMP_CMP_CONNECTED
    #define AMP1_CLOCK_SOURCE                AMP_CLOCK_EQ_PSC0


    /* ADC configuration */
    #define ADC_REF_SOURCE                   ADC_REF_EQ_INT_VREF
    #define ADC_ADLAR_VALUE                  ADC_RIGHT_ADJUST_RESULT
    #define ADC_CHANNEL                      ADC_INPUT_ADC0
    #define ADC_ENABLE_BIT_VALUE             ADC_ENABLE
    #define ADC_AUTO_TRIG_ENABLE_VALUE       ADC_AUTO_TRIG_DISABLE
    #define ADC_INTERRUPT_ENABLE_VALUE       ADC_INTERRUPT_ENABLE
    #define ADC_PRESCALER_SELECT_VALUE       ADC_DIV_CLOCK_BY_4
    #define ADC_HIGH_SPEED_MODE_VALUE        ADC_HIGH_SPEED_MODE
    #define ADC_CURRENT_SOURCE_ENABLE_VALUE  ADC_CURRENT_SRC_ENABLE
    #define ADC_AREF_PIN_ENABLE_VALUE        ADC_AREF_PIN_DISABLE
    #define ADC_AUTO_TRIG_SOURCE             ADC_FREE_RUNNING


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


    // PSC configuration
    #define PSC_PRESCALER PSC_NODIV_CLOCK
    #define PSC_CLOCK_SOURCE PSC_CLOCK_SOURCE_EQ_PLL

    #define PSC_MODE PSC_MODE_CENTERED

    #define PSC_OUTPUT_A_POLARITY PSC_OUTPUT_HIGH

    //! @brief  Define all current decay types
    #define SLOW_DECAY 0
    #define FAST_DECAY 1
    #define SLOW_DECAY_SYNCHRONOUS 2
    #define FAST_DECAY_SYNCHRONOUS 3 // ATmega64M1 only

    //! @brief  Select here the current decay type for the application
    //#define CURRENT_DECAY SLOW_DECAY
    #define CURRENT_DECAY FAST_DECAY
    //#define CURRENT_DECAY SLOW_DECAY_SYNCHRONOUS
    //#define CURRENT_DECAY FAST_DECAY_SYNCHRONOUS // ATmega64M1 only

    #if (CURRENT_DECAY == FAST_DECAY)
        #define PSC_OUTPUT_B_POLARITY PSC_OUTPUT_LOW
    #else /* SLOW_DECAY or SLOW_DECAY_SYNCHRONOUS or FAST_DECAY_SYNCHRONOUS */
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

    #define RB_VAL 255 //!< POCR_RB = 255 => PWM freq = PLL freq / 255

    #define DEADTIME 2 //!< Dead Time for the inverter

    #define Low(data_w)                ((uint8_t)data_w)
    #define High(data_w)               ((uint8_t)(data_w>>8))

    /* useful defines when PC3 is required to display events */
    #define Init_PC3()   (DDRC |= (1<<DDC3))
    #define Toggle_PC3() (PINC |= (1<<PINC3))
    #define Set_PC3()    (PORTC |= (1<<PORTC3))
    #define Clear_PC3()  (PORTC &= ~(1<<PORTC3))

    /* JTS: Previously used to indicate an overcurrent condition
    #define Init_PC7()   (DDRC |= (1<<DDC7))
    #define Toggle_PC7() (PINC |= (1<<PINC7))
    #define Set_PC7()    (PORTC |= (1<<PORTC7))
    #define Clear_PC7()  (PORTC &= ~(1<<PORTC7))
    */

    enum {CCW = TRUE, CW = FALSE}; //Define motor direction

    #define N_SAMPLE  8 //Number of samples to calculate motor speed (if enabled)
    //#define AVERAGE_SPEED_MEASUREMENT //enable averaging

    //PID control coefficients
    #define SPEED_PID_PROPERTIONAL_COEF 30
    #define SPEED_PID_INTEGRAL_COEF 30
    #define SPEED_PID_DIFFERENTIAL_COEF 0

    // All PID coef are multiplied by 2^Kmul
    // Example : kp = 1 => Kp = 1 * 2^K_scal = 1 * 2^4 = 16
    // To get the right result you have to divide the number by 2^K_scal (right shift by K_scal)
    #define K_SPEED_SCALAR 4 //Speed regulation scale factor

    // Speed measurement
    // K_SPEED = (60 * 255)/(n * t_timer0 * speed_max(rpm))
    // where n = number of pole pairs
    // where t_timer0 = 16us
    #define K_SPEED 53125 // max speed : 4500 (57BLF)  
    //#define K_SPEED 34152 // max speed : 7000 (MC100 motor)
    //#define K_SPEED 11250 // max speed : 17000 (MMT 35-1LS motor)
    // if you want to calculate the absolute speed
    //   absolute_speed = alpha * measured_speed
    //   with alpha = 60 / (n * K_SPEED * t_timer0)

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

#endif // _CONFIG_H_
