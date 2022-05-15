//Inputs/Outputs
int buzzer = 5;
/* PWM in pin - D8
 * High A - D9
 * LOW A - D4
 * HIGH B - D10
 * LOW B - D3
 * HIGH C - D11
 * LOW C - D2
 * Comparator - D6
*/
#define PWM_max_value      255
#define PWM_min_value      35
#define PWM_value    35


int PWM_IN_MAX = 2000;
int PWM_IN_MIN = 1000;
int PWM_IN_MIN_ADRESS = 2;
int PWM_IN_MAX_ADRESS = 7;
int MIN_PWM_TO_STORE = 0;
int MAX_PWM_TO_STORE = 0;
int pwm_set_counter = 0;
int beeping_PWM_VALUE = 100;

byte sequence_step = 0, motor_speed;
unsigned int i;
//We create variables for the time width value of the PWM input signal
unsigned long counter_1, current_count;
byte last_PWM_state;
//To store the 1000us to 2000us value we create variables
int PWM_INPUT;      //In my case PWM_IN pin is D8 of the Arduino
bool MOTOR_SPINNING = false;
bool ESC_MODE_ON = false;
int motor_off_counter = 0;
bool PWM_RANGE_SET = false;
unsigned long previousMillis = 0; 
unsigned long currentMillis = 0;
bool full_stop = false;
