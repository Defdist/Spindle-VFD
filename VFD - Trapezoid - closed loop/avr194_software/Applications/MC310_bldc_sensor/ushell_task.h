//******************************************************************************
//!
//! @file $Id: ushell_task.h 1344 2008-05-07 14:50:31Z raubree $
//!
//! Copyright (c) 2007 Atmel.
//!
//! @brief This file contains the ushell_task.c function declarations
//!
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _USHELL_TASK_H_
#define _USHELL_TASK_H_

//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "compiler.h"
//_____ M A C R O S ________________________________________________________


// Commands shell
#define CMD_NONE           0x00
#define CMD_HELP           0x01
#define CMD_RUN            0x02
#define CMD_STOP           0x03
#define CMD_FORWARD        0x04
#define CMD_BACKWARD       0x05
#define CMD_SET_SPEED      0x06
#define CMD_GET_ID         0x07
#define CMD_GET_STATUS0    0x08
#define CMD_GET_STATUS1    0x09


// Special char values
#define CR                 0x0D
#define LF                 0x0A
#define CTRL_Q             0x11
#define CTRL_C             0x03
#define BKSPACE_CHAR       0x08
#define ABORT_CHAR         CTRL_C
#define QUIT_APPEND        CTRL_Q

// String values for commands
#define STR_RUN            "ru"
#define STR_STOP           "st"
#define STR_HELP           "help"
#define STR_FORWARD        "fw"
#define STR_BACKWARD       "bw"
#define STR_SET_SPEED      "ss"
#define STR_GET_ID         "gi"
#define STR_GET_STATUS0    "g0"
#define STR_GET_STATUS1    "g1"

// String messages
#define MSG_PROMPT         "\r>"
#define MSG_WELCOME        "\rATMEL Motor Control Interface"
#define MSG_ER_CMD_NOT_FOUND  "Unknown Command"
#define MSG_HELP    "\r\
ru : run\r\
st : stop\r\
fw : forward\r\
bw : backward\r\
ss : set speed\r\
gi : get id\
"

//_____ D E C L A R A T I O N S ____________________________________________
extern volatile Bool ushell_active;


void   build_cmd(void);
void   parse_cmd(void);
#ifdef __GNUC__
U8 mystrncmp(U8 *str1,U8 const *str2,U8 i);
#else
U8 mystrncmp(U8 *str1,U8 code *str2,U8 i);
#endif
#ifdef __GNUC__
void print_msg(U8 const *str);
#else
void print_msg(U8 code *str);
#endif
void   ushell_task_init(void);
void   ushell_task(void);

#endif /* _USHELL_TASK_H_ */

