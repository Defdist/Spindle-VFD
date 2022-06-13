#ifndef _PID_H_
	#define _PID_H_

    //PID control coefficients
    #define SPEED_PID_PROPERTIONAL_COEF 1
    #define SPEED_PID_INTEGRAL_COEF 30
    #define SPEED_PID_DIFFERENTIAL_COEF 0

    //#define SPINDLE_MODE_OPEN_LOOP
    #define SPINDLE_MODE_CLOSED_LOOP

    #define OPEN_LOOP_STATIC_PSC_DUTY_CYCLE 255 //0: 0% PWM //255: 100% PWM

    #define PID_UPDATE_PERIOD_MICROSECONDS 1000

    #define MIN_ALLOWED_RPM 1500 //must be larger than ADC_COUNTS_TO_RPM__OFFSET (or spindle won't stop spinning)

	uint8_t pid_dutyCycle_get(void);
	void    pid_dutyCycle_set(uint8_t newDuty);

    void pid_scheduler(void);
    uint8_t pid_dutyCycle_calculate(void);

#endif
