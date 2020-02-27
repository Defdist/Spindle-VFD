/*!
* \mainpage
* \section section1 Description
*   This application drives a BLDC motor with trapezoidal waveforms\n
*   The motor features Hall sensors \n
*   It runs on an ATAVRMC310 board with an ATmega32M1 part\n
*   The main source files are :
*
*         -  main.c             main loop
*         -  mc_control.c       PI regulation
*         -  mc_drv.c           hardware level of motor control
*
*         -  mc_interface.c     interface routines to motor control
*
*         -  ushell_task.c      command interpreter from an ascii chain
*         -  ascii.c            ascii to binary conversion
*
*
* \section section2 Preamble
* All parameters are given for the motor included in the kit with no load.\n
* They must be ajusted according to the application (motor, load ...)
* \n
*
* \section section3 Main Peripheral Use
*   - Timer 0 is used for speed measurement/svpwm
*   - Timer 1 is used to generate main tick
*   - PSC is used to generate PWM
*   - ADC is used for current and potentiometer measurement
*
* \section section4 User Manual
*   - At power on, the motor starts running
*   - The reference speed is ajusted with the potentiometer connected to the ATmega32M1 Isrc Input
*   - One can control the motor through Uart Interface :
*
* \subsection subsection1 Communication setting through RS232 (if PC IHM is used)
*   - Connect the MC310 RS232 DB9 to the PC
*   - Set J12 jumper on TxD
*   - Set J13 jumper on RxD
* 
* \subsection subsection2 Communication setting through USB bridge (if PC IHM is used)
*   - Connect the MC310 USB connector to the PC
*   - Set J12 jumper on TxDUSB
*   - Set J13 jumper on RxDUSB
*
* \subsection subsection3 List of Material
*   - ATAVRMC310 (ATmega32M1 clock is 16MHz from PLL)
*   - ATAVRMC300 (Power Board)
*
* \subsection subsection4 Hardware Configuration
*   - Set the ATAVRMC300 jumpers as described in the AVR194 App Note
*   - Set the ATAVRMC310 jumpers as described in the AVR194 App Note
*
* \subsection subsection5 HyperTerminal Configuration
*   - Speed : 38400 bauds
*   - Bits : 8
*   - Stop : 1
*   - Handshake : None
*   - Parity : None
*
* \subsection subsection6 List of Commands
* After reset the ATAVRMC310 board prints the welcome message and a prompt\n
* The user commands are :
*   - ru   : run / start the motor
*   - st   : stop / stop the motor
*   - help : help / return the list of commands
*   - fw   : forward
*   - bw   : backward
*   - ss v : set speed (v is the value)
*   - gi   : get identification / return the board id, the soft id and the soft rev
*   - g0   : get status 0 : return the status byte, the speed and the current
*   - g1   : get status 1 : return the rotation counter
* \n \n
* Note : All values are in hexadecimal form\n
*           These commands are compatible with ATMEL Motor Control Center
*
* \section section5 Overcurrent protection
* This firmware sets an overcurrent protection. The motor current is measured
* thanks to a shunt resistor located on the MC300 board.
* The amplifier 1 amplifies the shunt voltage.
* The output of the amplifier 1 is used as ADC input to get the motor current.
* The output of the amplifier 1 is also used as comparator 1 positive input.
* The negative output of the comparator 1 is connected to the DAC output
* which provides a treshold voltage for the overcurrent detection. The output 
* of the comparator 1 is used as PSC fault input. When an overcurrent occurs,
* the PSC is stopped.
*/