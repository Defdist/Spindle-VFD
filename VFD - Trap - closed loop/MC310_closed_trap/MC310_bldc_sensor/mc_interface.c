#include "grBLDC.h"

Bool motorDirection = CW;
Bool motorStatus = STOPPED;

uint8_t motorSpeed_desired = 0;
uint8_t motorSpeed_measured = 0;

uint32_t mci_measured_current = 0; //!<Motor Input parameter to get the motor current
uint8_t mc_potentiometer_value = 0;//!<Motor Input to set the motor speed

extern Bool overcurrent;

////////////////////////////////////////////////////////////////////////////////////////

void mci_motor_run(void)
{
  if (!(PCTL & (1<<PRUN))) { PSC_Init(); } //starts PSC stage, if not already started
  
  overcurrent = FALSE;
  motorStatus = RUNNING;
  psc_setDutyCycle( pid_dutyCycle_calculate() );
  mc_commutateFETs( hall_getPosition() ); //also occurs in ISR each time Hall state changes
  mc_disableOvercurrentDuringStartup(); //JTS2doLater: Configure overcurrent
}

////////////////////////////////////////////////////////////////////////////////////////

uint8_t mci_motorState_get(void) { return motorStatus; }

////////////////////////////////////////////////////////////////////////////////////////

void mci_motor_stop(void) { motorStatus = STOPPED; }

////////////////////////////////////////////////////////////////////////////////////////

void mci_motor_desiredSpeed_set(uint8_t speed) { motorSpeed_desired = speed; }
uint8_t mci_motor_desiredSpeed_get(void) { return motorSpeed_desired; }

////////////////////////////////////////////////////////////////////////////////////////

//JTS2doNow: Direction never set in code.  Fine for now.
//JTS2doNow: If direction_now != direction_previous, need to stop motor first, then spin other way.
void mci_motorDirection_set(uint8_t direction) { (direction == CCW) ? (motorDirection = CCW) : motorDirection = CW; }
uint8_t mci_motorDirection_get(void) { return motorDirection; }

////////////////////////////////////////////////////////////////////////////////////////

void mci_motor_measuredSpeed_set(uint8_t measured_speed) { motorSpeed_measured = measured_speed; }
uint8_t mci_motor_measuredSpeed_get(void) { return motorSpeed_measured; }

////////////////////////////////////////////////////////////////////////////////////////

//JTS2doNow: We shouldn't be integrating inside these functions... do it wherever they're called
uint16_t mci_motor_measuredCurrent_get(void) { return (mci_measured_current >> 6); } //mci_measured_current/64

void mci_motor_measuredCurrent_integrate(uint16_t current) { mci_measured_current = ( (63 * mci_measured_current) + (64 * current) )>>6; }

////////////////////////////////////////////////////////////////////////////////////////

uint8_t mc_goalRPM_get(void) { return mc_potentiometer_value; }
void mc_goalRPM_set(uint8_t potentiometer) { mc_potentiometer_value = potentiometer; }

////////////////////////////////////////////////////////////////////////////////////////

void mc_motor_init()
{
  mc_motor_init_HW();
  sei(); //enable interrupts

  mci_motor_stop();
  mci_motorDirection_set(CW);
  mci_motor_desiredSpeed_set(0);
  mci_motor_measuredSpeed_set(0);
}