//!
//! @file $RCSfile: ascii.h,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This file provides ASCII functions for the �shell task.
//!
//! @version $Revision: 1.5 $
//!
 
#ifndef _ASCII_H_
#define _ASCII_H_

//_____  I N C L U D E S ___________________________________________________

//#include "config.h"
#include "uart_lib.h"
#include <stdio.h>



U8 ascii_to_bin (U8 c);
U8 bin_to_ascii (U8 c);


#endif
