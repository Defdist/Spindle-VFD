//******************************************************************************
//!
//! @file $Id: psc_drv.h 1138 2008-04-17 16:35:32Z raubree $
//!
//! Copyright (c) 2008 Atmel.
//!
//! @brief Main module : Provide MacroInst. or functions to use the PSC 
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _PSC_DRV_H_
	#define _PSC_DRV_H_

	//_____ I N C L U D E S ____________________________________________________

	//! @defgroup PSC_module PSC Module
	//! PSC Module
	//! @{
	//_____ M A C R O S ________________________________________________________

	   //! @defgroup PSC_macros PSC Macros
	   //! Low level macros that permit the use of the PSC of the product.
	   //! @{

		  //! @defgroup PSC_set_module_A set module A of PSC
		  //! set all module A values
		  //! @{
	#define Psc_set_module_A(sa_val,ra_val,sb_val) \
			 POCR0SAH = highByte(sa_val); \
			 POCR0SAL = lowByte(sa_val);  \
			 POCR0RAH = highByte(ra_val); \
			 POCR0RAL = lowByte(ra_val);  \
			 POCR0SBH = highByte(sb_val); \
			 POCR0SBL = lowByte(sb_val); 
		  //! @}

		  //! @defgroup PSC_set_module_B set module B of PSC
		  //! set all module A values
		  //! @{
	#define Psc_set_module_B(sa_val,ra_val,sb_val) \
			 POCR1SAH = highByte(sa_val); \
			 POCR1SAL = lowByte(sa_val);  \
			 POCR1RAH = highByte(ra_val); \
			 POCR1RAL = lowByte(ra_val);  \
			 POCR1SBH = highByte(sb_val); \
			 POCR1SBL = lowByte(sb_val); 
		  //! @}

		  //! @defgroup PSC_set_module_C set module C of PSC
		  //! set all module A values
		  //! @{
	#define Psc_set_module_C(sa_val,ra_val,sb_val) \
			 POCR2SAH = highByte(sa_val); \
			 POCR2SAL = lowByte(sa_val);  \
			 POCR2RAH = highByte(ra_val); \
			 POCR2RAL = lowByte(ra_val);  \
			 POCR2SBH = highByte(sb_val); \
			 POCR2SBL = lowByte(sb_val); 
		  //! @}

	//set PSC POCR_RB register
	//This sets the max value the free-running PSC 12b counter can count up to
	//free-funning PSC 12b counter is clocked by PLL or CPU clock
	//once the free-running counter gets to this value, it either counts back down to zero, or resets to zero (depending on mode)
	#define Psc_set_register_RB(RB_VAL) \
			 POCR_RBH = highByte(RB_VAL); \
			 POCR_RBL = lowByte(RB_VAL);
    
		  //! @defgroup PSC_enable_all_outputs Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
	#define Psc_enable_all_outputs() \
	   POC = (1<<POEN2B)| \
			 (1<<POEN2A)| \
			   (1<<POEN1B)| \
			   (1<<POEN1A)| \
			 (1<<POEN0B)| \
			 (1<<POEN0A);
		   //! @{



		  //! @defgroup PSC_enable_all_outputs Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
	#define Psc_select_outputs(val2B,val2A,val1B,val1A,val0B,val0A) \
	   POC = (val2B<<POEN2B)| \
			 (val2A<<POEN2A)| \
			   (val1B<<POEN1B)| \
			   (val1A<<POEN1A)| \
			 (val0B<<POEN0B)| \
			 (val0A<<POEN0A);
		   //! @{


		  //! @defgroup PSC_enable_all_outputs Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
		  //PSC_PRESCALER:    input clock division factor //00:DIV1 //01:DIV4 //10:DIV32 //11:DIV256
		  //PSC_CLOCK_SOURCE: input clock source //0:CLK_IO //1:CLK_PLL
		  //PCCYC:            //0:PSC halts immediately when PRUN=0 //1:PSC completes cycle before halting
	#define Psc_run() \
	   PCTL = (PSC_PRESCALER<<PPRE0)| \
			  (PSC_CLOCK_SOURCE<<PCLKSEL)| \
 				(0<<PCCYC)| \
			  (1<<PRUN); /* RUN !! */
		  //! @}

		  //! @defgroup PSC_enable_all_outputs Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
	#define Psc_stop() \
	   PCTL = (PSC_PRESCALER<<PPRE0)| \
			  (PSC_CLOCK_SOURCE<<PCLKSEL)| \
 				(0<<PCCYC)| \
			  (0<<PRUN); /* STOP !! */
		  //! @}

		  //! @defgroup PSC_enable_all_outputs Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
	#define Psc_complete_and_stop() \
	   PCTL = (PSC_PRESCALER<<PPRE0)| \
			  (PSC_CLOCK_SOURCE<<PCLKSEL)| \
 				(1<<PCCYC)| \
			  (0<<PRUN); /* STOP !! */
		  //! @}

		  //! @defgroup PSC_config Enable all 6 PSC outputs
		  //! set all enable in POC register
		  //! @{
		  //PULOCK:                //0: updated PSC register values affect output //1: updated PSC registers stored - but ignored - until unlocked
		  //PSC_MODE:              //1: center-aligned mode /0: ramp mode
		  //PSC_OUTPUT_B_POLARITY: //0: outputs are active low //1: outputs are active high
		  //PSC_OUTPUT_A_POLARITY: //0: outputs are active low //1: outputs are active high
	#define Psc_config() \
	   PCNF = (0<<PULOCK)| \
			  (PSC_MODE<<PMODE)| \
			  (PSC_OUTPUT_B_POLARITY<<POPB)| \
			  (PSC_OUTPUT_A_POLARITY<<POPA);
		  //! @}

		  //! @defgroup PSC_lock lock the update of duty registers
		  //! unauthorize the update of PSC registers
		  //! @{
		  //
	#define Psc_lock() \
	   PCNF = (1<<PULOCK)| \
			  (PSC_MODE<<PMODE)| \
			  (PSC_OUTPUT_B_POLARITY<<POPB)| \
			  (PSC_OUTPUT_A_POLARITY<<POPA); 
		  //! @}

		  //! @defgroup PSC_unlock unlock the update of duty registers
		  //! authorize the update of PSC registers
		  //! @{
	#define Psc_unlock() \
	   PCNF = (0<<PULOCK)| \
			  (PSC_MODE<<PMODE)| \
			  (PSC_OUTPUT_B_POLARITY<<POPB)| \
			  (PSC_OUTPUT_A_POLARITY<<POPA); 
		  //! @}

		  //! @defgroup PSC_config_input_0 configure the PMIC0 register
		  //! authorize the update of PSC registers
		  //! @{
		  //POVEN0: /*0: Overlap Protection enabled //1: Deactivate A&B phase Overlap Protection*/
		  //PISEL0: /*0: PSCIN0 is module 0 input //1: Comparator 0 output is module 0 input*/
		  //PELEV0: /*0: low level on PISEL0 pin generates interrupt //1: high level generates interrupt*/
		  //PFLTE0: /*0: noise canceller disabled //1: noise canceller enabled (input delayed four cycles)*/
		  //PAOC0:  /*0: fault input acts directly on PSC module 0 outputs //1: fault input clocked*/
		  //PRFM00: /*0: PSC module 0 input mode:
							//000:ignore (no action)
							//0x1:Deactivate 0A
							//01x:Deactivate 0B 
							//10x:Deactivate all PSC outputs (0/1/2)
							//11x:Halt PSC and wait for software
	#define Psc_config_input_0(v1,v2,v3,v4,v5,v6)\
	   PMIC0 = ((v1)<<POVEN0)| \
			   ((v2)<<PISEL0)| \
			   ((v3)<<PELEV0)| \
			   ((v4)<<PFLTE0)| \
			   ((v5)<<PAOC0)|  \
			   ((v6)<<PRFM00);

		  //! @}

		  //! @defgroup PSC_config_input_1 configure the PMIC1 register
		  //! authorize the update of PSC registers
		  //! @{
	#define Psc_config_input_1(v1,v2,v3,v4,v5,v6)\
	   PMIC1 = ((v1)<<POVEN1)| \
			   ((v2)<<PISEL1)| \
			   ((v3)<<PELEV1)| \
			   ((v4)<<PFLTE1)| \
			   ((v5)<<PAOC1)| \
			   ((v6)<<PRFM10);
		  //! @}

		  //! @defgroup PSC_config_input_2 configure the PMIC2 register
		  //! authorize the update of PSC registers
		  //! @{
	#define Psc_config_input_2(v1,v2,v3,v4,v5,v6)\
	   PMIC2 = ((v1)<<POVEN2)| \
			   ((v2)<<PISEL2)| \
			   ((v3)<<PELEV2)| \
			   ((v4)<<PFLTE2)| \
			   ((v5)<<PAOC2)| \
			   ((v6)<<PRFM20);
		  //! @}



	//_____ D E F I N I T I O N S ______________________________________________
	#define PSC_MODE_ONE_RAMP 0
	#define PSC_MODE_CENTERED 1

	#define PSC_OUTPUT_LOW  0
	#define PSC_OUTPUT_HIGH 1

	#define PSC_CLOCK_SOURCE_EQ_CLKIO   0
	#define PSC_CLOCK_SOURCE_EQ_PLL     1

	#define PSC_NODIV_CLOCK             0
	#define PSC_DIV_CLOCK_BY_4          1
	#define PSC_DIV_CLOCK_BY_32         2
	#define PSC_DIV_CLOCK_BY_256        3

	/* PMIC register definitions */
	#define PSC_OVERLAP_DISABLE         0
	#define PSC_OVERLAP_ENABLE          1

	#define PSC_USE_PIN                 0
	#define PSC_USE_COMPARATOR          1

	#define PSC_USE_LOW_LEVEL           0
	#define PSC_USE_HIGH_LEVEL          1

	#define PSC_INPUT_FILTER_DISABLE    0
	#define PSC_INPUT_FILTER_ENABLE     1

	#define PSC_ASYNCHRONOUS_OUTPUT_CONTROL 0
	#define PSC_SYNCHRONOUS_OUTPUT_CONTROL  1

	#define PSC_INPUT_NO_ACTION         0
	#define PSC_DISACTIVATE_OUTPUT_A    1
	#define PSC_DISACTIVATE_OUTPUT_B    2
	#define PSC_DISACTIVATE_OUTPUT_AB   3
	#define PSC_DISACTIVATE_ALL_OUTPUTS 4
	#define PSC_INPUT_HALT              6

#endif  // _PSC_DRV_H_

