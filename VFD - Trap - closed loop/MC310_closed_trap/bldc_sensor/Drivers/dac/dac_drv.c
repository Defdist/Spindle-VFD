
#include "config_dac.h"

#ifdef _USE_DAC_LIB_ //!< this define is set on config.h file
       #include "dac_drv.h"

       //! Configures the DAC according to the DAC Define Configuration values
       void init_dac(void)
       {
           Dac_enable();

            #if (DAC_INPUT_RIGHT_ADJUST == 1)
                Dac_right_adjust_input();
            #elif (DAC_INPUT_RIGHT_ADJUST == 0)
                Dac_left_adjust_input();
            #else
                #error (DAC_RIGHT_ADJUST_RESULT should be 0 or 1... See config.h file)
            #endif

            #if (DAC_OUTPUT_DRIVER == 1)
                Dac_enable_output();
            #elif (DAC_OUTPUT_DRIVER == 0)
                Dac_disable_output();
            #else
                #error (DAC_OUTPUT_DRIVER should be 0 or 1... See config.h file)
            #endif
       }

#endif // USE_DAC