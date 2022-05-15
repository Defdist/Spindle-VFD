//!
//! @file $RCSfile: ascii.c,v $
//!
//! Copyright (c) 2006 Atmel.
//!
//! @brief This file provides ASCII functions for the µshell task.
//!
//! @version $Revision: 1.4 $
//!

//_____  I N C L U D E S ___________________________________________________

#ifdef __ICCAVR__ // IAR C Compiler
#include "config.h"
#endif

#ifdef __GNUC__  // GNU C Compiler
#include "config_for_gcc.h"
#endif

#include "ascii.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________



//! @brief This function returns the binary value of an ascii digit.
//!
//!
//! @param none
//!
//! @return none
//!
//!/
U8 ascii_to_bin (U8 c)
{
  if (c>='a') return(c-('a'-0x0A));
  if (c>='A') return(c-('A'-0x0A));
  return(c-'0');
}

//! @brief This function returns the ascii value of a quartet
//!
//!
//! @param none
//!
//! @return none
//!
//!/
U8 bin_to_ascii (U8 c)
{
  if (c>=0x0A) return (c+('A'-0x0A));
  return (c+'0');
}
