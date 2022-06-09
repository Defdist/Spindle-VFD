#ifndef _MOTOR_H_
	#define _MOTOR_H_

    #define RUNNING 1
    #define STOPPED 0

    //Define motor direction
    #define MOTOR_CCW 1
    #define MOTOR_CW 2

    void motor_init(void);
    void motor_stop(void);
    void motor_run(void);

    uint8_t motor_state_get(void);

    uint8_t motor_direction_get(void);
    void    motor_direction_set(uint8_t direction);

#endif
