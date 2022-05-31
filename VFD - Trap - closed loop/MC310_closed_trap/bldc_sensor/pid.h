#ifndef _PID_H_
	#define _PID_H_

    //PID control coefficients
    #define SPEED_PID_PROPERTIONAL_COEF 30
    #define SPEED_PID_INTEGRAL_COEF 30
    #define SPEED_PID_DIFFERENTIAL_COEF 0

    // All PID coef are multiplied by 2^Kmul
    // Example : kp = 1 => Kp = 1 * 2^K_scal = 1 * 2^4 = 16
    // To get the right result you have to divide the number by 2^K_scal (right shift by K_scal)
    #define K_SPEED_SCALAR 4 //Speed regulation scale factor

    // RPM measurement
    #define K_SPEED 53125 // 57BLF BLDC max RPM: 4500  
    // K_SPEED = (60 * 255)/(n * t_timer0 * speed_max(rpm))
    // where n = number of pole pairs
    // where t_timer0 = 16us
    
    //to calculate absolute speed:
    //   absolute_speed = alpha * measured_speed
    //   with alpha = 60 / (n * K_SPEED * t_timer0)

	uint8_t pid_dutyCycle_calculate(void);
	uint8_t pid_dutyCycle_get(void);

#endif
