#ifndef _DAC_H_
	#define _DAC_H_

	/* DAC configuration */
    #define DAC_AUTOTRIG_ENABLE_VALUE        DAC_AUTOTRIG_DISABLE
    #define DAC_TRIGGER_SELECTION            DAC_TRIG_WITH_COMP0
    #define DAC_LEFT_ADJUST_VALUE            DAC_LEFT_ADJUST
    #define DAC_OUTPUT_ENABLE_VALUE          DAC_OUTPUT_DISABLE
    #define DAC_ENABLE_VALUE                 DAC_ENABLE

	//////////////////////////////////////////////////////////////////////////////

    void dac_init(void);

#endif
