====== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ======

//******************************************************************************
//! @file $RCSfile: can_drv.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions (drivers) of:
//!             - CAN (Controller Array Network)
//!             - for AT90PWMxx4 & ATtinyxx7.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

... ... ...


//******************************************************************************
//! @file $RCSfile: can_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - CAN (Controller Array Network)
//!             - for AT90PWMxx4 & ATtinyxx7.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _CAN_DRV_H_
#define _CAN_DRV_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ M A C R O S ____________________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

( *** function prototypes ***)
... ... ...

====== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ==== DRV ======


====== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ======

//******************************************************************************
//! @file $RCSfile: uart_lib.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the library of functions of:
//!             - UART of LINUART macro
//!             - for AT90PWMxx4 & ATtinyxx7.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

... ... ...


//******************************************************************************
//! @file $RCSfile: uart_lib.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - UART of LINUART macro
//!             - for AT90PWMxx4 & ATtinyxx7.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _UART_LIB_H_
#define _UART_LIB_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ M A C R O S ____________________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

( *** function prototypes ***)
... ... ...


====== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ==== LIB ======

====== MAIN === MAIN === MAIN === MAIN === MAIN === MAIN === MAIN === MAIN =====

//******************************************************************************
//! @file $RCSfile: main_can_spy_echo_test.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief CAN spy displaying CAN activity on UART's
//!             - for AT90PWMxx4 & ATtinyxx7.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413549/WinAVR-20070525.
//!
//! @version $Revision: 1.00 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____ I N C L U D E S ________________________________________________________

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn main
//!
//! Core of "main_can_spy_echo_example.c".
//!
//! - CAN communications are listen, captured and a resume is sent on UART_0 and
//!   UART_1 (The UART number is at the end & at the beginning of each generated
//!   printing; i.e. 0 or 1).
//! - An CAN Echo also is sent: ID(sent)=ID(received)+1
//!                             DLC = 8
//!                             RTR = 0
//!                             Data[6:7]=CANSTMH:CANSTML
//! Note: If some key is pushed while RESET, only Spy mode is enabled.
//! Note: Exit in UART ECHO MODE if CAN ID == 0 as CAN error simulation
//!
//! @warning UART's at 38400 bauds
//!          CAN in auto-bitrate
//!
//! @param none.
//!
//! @return Integer 0
//!
//------------------------------------------------------------------------------

====== MAIN === MAIN === MAIN === MAIN === MAIN === MAIN === MAIN === MAIN =====

=== FUNCTION === FUNCTION === FUNCTION === FUNCTION === FUNCTION === FUNCTION ==

//------------------------------------------------------------------------------
//  @fn can_auto_baudrate
//!
//! This function programs itself the CANBTx registers if there is some
//! communication (activity) on the CAN bus.
//!
//! @warning complex function not yet implemented
//!
//! @param  Evaluation needed
//!         ==0: start the evaluation from faster baudrate
//!         ==1: (re)start an evaluation with CANBTx registers contents
//!
//! @return Baudrate Status
//!         ==0: research of bit timing configuration failed
//!         ==1: baudrate performed
//------------------------------------------------------------------------------
U8 can_auto_baudrate (U8 mode)
{
    U8  u8_temp0;                               //! Temporary variable
    ...
    
    //! --- place code here
    u8_temp0 = 0;
    
    ... ...
}    

