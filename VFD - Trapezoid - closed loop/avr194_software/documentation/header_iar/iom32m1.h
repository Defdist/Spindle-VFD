/****************************************************************************
 **             - iom32M1.h -
 **
 **     This file declares the internal register addresses for ATmega32M1.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 2008. All rights reserved.
 **
 **     File version: $Revision: 1.3 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(3)
#error This file should only be compiled with iccavr or aavr with processor option -v3
#endif /* TID_GUARD(3) */

#ifdef __HAS_RAMPZ__
#error This file should not have RAMPZ enabled, use --cpu or --64k_flash
#endif /* __HAS_RAMPZ__ */

/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOM32M1_H) || defined(__IAR_SYSTEMS_ASM__)

#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_N(0xFA, CANMSG, MSG7, MSG6, MSG5, MSG4, MSG3, MSG2, MSG1, MSG0)
SFR_W_N(0xF8, CANSTMP, TIMSTM15, TIMSTM14, TIMSTM13, TIMSTM12, TIMSTM11, TIMSTM10, TIMSTM9, TIMSTM8,\
        TIMSTM7, TIMSTM6, TIMSTM5, TIMSTM4, TIMSTM3, TIMSTM2, TIMSTM1, TIMSTM0)
SFR_B_N(0xF7, CANIDM1, IDMSK28, IDMSK27, IDMSK26, IDMSK25, IDMSK24, IDMSK23, IDMSK22, IDMSK21)
SFR_B_N(0xF6, CANIDM2, IDMSK20, IDMSK19, IDMSK18, IDMSK17, IDMSK16, IDMSK15, IDMSK14, IDMSK13)
SFR_B_N(0xF5, CANIDM3, IDMSK12, IDMSK11, IDMSK10, IDMSK9, IDMSK8, IDMSK7, IDMSK6, IDMSK5)
SFR_B_N(0xF4, CANIDM4, IDMSK4, IDMSK3, IDMSK2, IDMSK1, IDMSK0, RTRMSK, Dummy1, IDEMSK)
SFR_B_N(0xF3, CANIDT1, IDT28, IDT27, IDT26, IDT25, IDT24, IDT23, IDT22, IDT21)
SFR_B_N(0xF2, CANIDT2, IDT20, IDT19, IDT18, IDT17, IDT16, IDT15, IDT14, IDT13)
SFR_B_N(0xF1, CANIDT3, IDT12, IDT11, IDT10, IDT9, IDT8, IDT7, IDT6, IDT5)
SFR_B_N(0xF0, CANIDT4, IDT4, IDT3, IDT2, IDT1, IDT0, RTRTAG, RB1TAG, RB0TAG)
SFR_B_N(0xEF, CANCDMOB, CONMOB1, CONMOB0, RPLV, IDE, DLC3, DLC2, DLC1, DLC0)
SFR_B_N(0xEE, CANSTMOB, DLCW, TXOK, RXOK, BERR, SERR, CERR, FERR, AERR)
SFR_B_N(0xED, CANPAGE, MOBNB3, MOBNB2, MOBNB1, MOBNB0, AINC, INDX2, INDX1, INDX0)
SFR_B_N(0xEC, CANHPMOB, HPMOB3, HPMOB2, HPMOB1, HPMOB0, CGP3, CGP2, CGP1, CGP0)
SFR_B_N(0xEB, CANREC, REC7, REC6, REC5, REC4, REC3, REC2, REC1, REC0)
SFR_B_N(0xEA, CANTEC, TEC7, TEC6, TEC5, TEC4, TEC3, TEC2, TEC1, TEC0)
SFR_W_N(0xE8, CANTTC, TIMTTC15, TIMTTC14, TIMTTC13, TIMTTC12, TIMTTC11, TIMTTC10, TIMTTC9, TIMTTC8,\
        TIMTTC7, TIMTTC6, TIMTTC5, TIMTTC4, TIMTTC3, TIMTTC2, TIMTTC1, TIMTTC0)
SFR_W_N(0xE6, CANTIM, CANTIM15, CANTIM14, CANTIM13, CANTIM12, CANTIM11, CANTIM10, CANTIM9, CANTIM8,\
        CANTIM7, CANTIM6, CANTIM5, CANTIM4, CANTIM3, CANTIM2, CANTIM1, CANTIM0)
SFR_B_N(0xE5, CANTCON, TPRSC7, TPRSC6, TPRSC5, TPRSC4, TPRSC3, TPRSC2, TRPSC1, TPRSC0)
SFR_B_N(0xE4, CANBT3, Dummy7, PHS22, PHS21, PHS20, PHS12, PHS11, PHS10, SMP)
SFR_B_N(0xE3, CANBT2, Dummy7, SJW1, SJW0, Dummy4, PRS2, PRS1, PRS0, Dummy0)
SFR_B_N(0xE2, CANBT1, Dummy7, BRP5, BRP4, BRP3, BRP2, BRP1, BRP0, Dummy)
SFR_B_N(0xE1, CANSIT1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0xE0, CANSIT2, Dummy7, Dummy6, SIT5, SIT4, SIT3, SIT2, SIT1, SIT0)
SFR_B_N(0xDF, CANIE1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0xDE, CANIE2, Dummy7, Dummy6, IEMOB5, IEMOB4, IEMOB3, IEMOB2, IEMOB1, IEMOB0)
SFR_B_N(0xDD, CANEN1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0xDC, CANEN2, Dummy7, Dummy6, ENMOB5, ENMOB4, ENMOB3, ENMOB2, ENMOB1, ENMOB0)
SFR_B_N(0xDB, CANGIE, ENIT, ENBOFF, ENRX, ENTX, ENERR, ENBX, ENERG, ENOVRT)
SFR_B_N(0xDA, CANGIT, CANIT, BOFFIT, OVRTIM, BXOK, SERG, CERG, FERG, AERG)
SFR_B_N(0xD9, CANGSTA, Dummy7, OVRG, Dummy5, TXBSY, RXBSY, ENFG, BOFF, ERRP)
SFR_B_N(0xD8, CANGCON, ABRQ, OVRQ, TTC, SYNTTC, LISTEN, TEST, ENASTB, SWRES)
SFR_B_N(0xD2, LINDAT, LDATA7, LDATA6, LDATA5, LDATA4, LDATA3, LDATA2, LDATA1, LDATA0)
SFR_B_N(0xD1, LINSEL, Dummy7, Dummy6, Dummy5, Dummy4, LAINC, LINDX2, LINDX1, LINDX0)
SFR_B_N_EXTRA(0xD0, LINIDR, LP1, LP0, LID5, LID4, LID3, LID2, LID1, LID0, \
              struct{ unsigned char :2; unsigned char LINIDR_LDL1:1; unsigned char LINIDR_LDL0:1; unsigned char :4;};)
SFR_B_N(0xCF, LINDLR, LTXDL3, LTXDL2, LTXDL1, LTXDL0, LRXDL3, LRXDL2, LRXDL1, LRXDL0)
SFR_W_N(0xCD, LINBRR, Dummy15, Dummy14, Dummy13, Dummy12, LDIV11, LDIV10, LDIV9, LDIV8,\
        LDIV7, LDIV6, LDIV5, LDIV4, LDIV3, LDIV2, LDIV1, LDIV0)
SFR_B_N(0xCC, LINBTR, LDISR, Dummy6, LBT5, LBT4, LBT3, LBT2, LBT1, LBT0)
SFR_B_N(0xCB, LINERR, LABORT, LTOERR, LOVERR, LFERR, LSERR, LPERR, LCERR, LBERR)
SFR_B_N(0xCA, LINENIR, Dummy7, Dummy6, Dummy5, Dummy4, LENERR, LENIDOK, LENTXOK, LENRXOK)
SFR_B_N(0xC9, LINSIR, LIDST2, LIDST1, LIDST0, LBUSY, LERR, LIDOK, LTXOK, LRXOK)
SFR_B_N(0xC8, LINCR, LSWRES, LIN13, LCONF1, LCONF0, LENA, LCMD2, LCMD1, LCMD0)
SFR_B_N(0xBC, PIFR, Dummy7, Dummy6, Dummy5, Dummy4, PEV2, PEV1, PEV0, PEOP)
SFR_B_N(0xBB, PIM, Dummy7, Dummy6, Dummy5, Dummy4, PEVE2, PEVE1, PEVE0, PEOPE)
SFR_B_N(0xBA, PMIC2, POVEN2, PISEL2, PELEV2, PFLTE2, PAOC2, PRFM22, PRFM21, PRFM20)
SFR_B_N(0xB9, PMIC1, POVEN1, PISEL1, PELEV1, PFLTE1, PAOC1, PRFM12, PRFM11, PRFM10)
SFR_B_N(0xB8, PMIC0, POVEN0, PISEL0, PELEV0, PFLTE0, PAOC0, PRFM02, PRFM01, PRFM00)
SFR_B_N(0xB7, PCTL, PPRE1, PPRE0, PCLKSEL, Dummy4, Dummy3, Dummy2, PCCYC, PRUN)
SFR_B_N(0xB6, POC, Dummy7, Dummy6, POEN2B, POEN2A, POEN1B, POEN1A, POEN0B, POEN0A)
SFR_B_N(0xB5, PCNF, Dummy7, Dummy6, PULOCK, PMODE, POPB, POPA, Dummy1, Dummy0)
SFR_B_N(0xB4, PSYNC, Dummy7, Dummy6, PSYNC21, PSYNC20, PSYNC11, PSYNC10, PSYNC01, PSYNC00)
SFR_W_N(0xB2, POCR_RB, Dummy15, Dummy14, Dummy13, Dummy12, POCR_RB11, POCR_RB10, POCR_RB9, POCR_RB8,\
        POCR_RB7, POCR_RB6, POCR_RB5, POCR_RB4, POCR_RB3, POCR_RB2, POCR_RB1, POCR_RB0)
SFR_W_N(0xB0, POCR2SB, Dummy15, Dummy14, Dummy13, Dummy12, POCR2SB11, POCR2SB10, POCR2SB9, POCR2SB8,\
        POCR2SB7, POCR2SB6, POCR2SB5, POCR2SB4, POCR2SB3, POCR2SB2, POCR2SB1, POCR2SB0)
SFR_W_N(0xAE, POCR2RA, Dummy15, Dummy14, Dummy13, Dummy12, POCR2RA11, POCR2RA10, POCR2RA9, POCR2RA8,\
        POCR2RA7, POCR2RA6, POCR2RA5, POCR2RA4, POCR2RA3, POCR2RA2, POCR2RA1, POCR2RA0)
SFR_W_N(0xAC, POCR2SA, Dummy15, Dummy14, Dummy13, Dummy12, POCR2SA11, POCR2SA10, POCR2SA9, POCR2SA8,\
        POCR2SA7, POCR2SA6, POCR2SA5, POCR2SA4, POCR2SA3, POCR2SA2, POCR2SA1, POCR2SA0)
SFR_W_N(0xAA, POCR1SB, Dummy15, Dummy14, Dummy13, Dummy12, POCR1SB11, POCR1SB10, POCR1SB9, POCR1SB8,\
        POCR1SB7, POCR1SB6, POCR1SB5, POCR1SB4, POCR1SB3, POCR1SB2, POCR1SB1, POCR1SB0)
SFR_W_N(0xA8, POCR1RA, Dummy15, Dummy14, Dummy13, Dummy12, POCR1RA11, POCR1RA10, POCR1RA9, POCR1RA8,\
        POCR1RA7, POCR1RA6, POCR1RA5, POCR1RA4, POCR1RA3, POCR1RA2, POCR1RA1, POCR1RA0)
SFR_W_N(0xA6, POCR1SA, Dummy15, Dummy14, Dummy13, Dummy12, POCR1SA11, POCR1SA10, POCR1SA9, POCR1SA8,\
        POCR1SA7, POCR1SA6, POCR1SA5, POCR1SA4, POCR1SA3, POCR1SA2, POCR1SA1, POCR1SA0)
SFR_W_N(0xA4, POCR0SB, Dummy15, Dummy14, Dummy13, Dummy12, POCR0SB11, POCR0SB10, POCR0SB9, POCR0SB8,\
        POCR0SB7, POCR0SB6, POCR0SB5, POCR0SB4, POCR0SB3, POCR0SB2, POCR0SB1, POCR0SB0)
SFR_W_N(0xA2, POCR0RA, Dummy15, Dummy14, Dummy13, Dummy12, POCR0RA11, POCR0RA10, POCR0RA9, POCR0RA8,\
        POCR0RA7, POCR0RA6, POCR0RA5, POCR0RA4, POCR0RA3, POCR0RA2, POCR0RA1, POCR0RA0)
SFR_W_N(0xA0, POCR0SA, Dummy15, Dummy14, Dummy13, Dummy12, POCR0SA11, POCR0SA10, POCR0SA9, POCR0SA8,\
        POCR0SA7, POCR0SA6, POCR0SA5, POCR0SA4, POCR0SA3, POCR0SA2, POCR0SA1, POCR0SA0)
SFR_B_N(0x97, AC3CON, AC3EN, AC3IE, AC3IS1, AC3IS0, Dummy3, AC3M2, AC3M1, AC3M0)
SFR_B_N(0x96, AC2CON, AC2EN, AC2IE, AC2IS1, AC2IS0, Dummy3, AC2M2, AC2M1, AC2M0)
SFR_B_N(0x95, AC1CON, AC1EN, AC1IE, AC1IS1, AC1IS0, AC1ICE, AC1M2, AC1M1, AC1M0)
SFR_B_N(0x94, AC0CON, AC0EN, AC0IE, AC0IS1, AC0IS0, ACCKSEL, AC0M2, AC0M1, AC0M0)
SFR_W_R(0x91, DAC)
SFR_B_N(0x90, DACON, DAATE, DATS2, DATS1, DATS0, Dummy3, DALA, DAOE, DAEN)
SFR_W_N(0x8A, OCR1B, OCR1B15, OCR1B14, OCR1B13, OCR1B12, OCR1B11, OCR1B10, OCR1B9, OCR1B8,\
        OCR1B7, OCR1B6, OCR1B5, OCR1B4, OCR1B3, OCR1B2, OCR1B1, OCR1B0)
SFR_W_N(0x88, OCR1A, OCR1A15, OCR1A14, OCR1A13, OCR1A12, OCR1A11, OCR1A10, OCR1A9, OCR1A8,\
        OCR1A7, OCR1A6, OCR1A5, OCR1A4, OCR1A3, OCR1A2, OCR1A1, OCR1A0)
SFR_W_N(0x86, ICR1, ICR115, ICR114, ICR113, ICR112, ICR111, ICR110, ICR19, ICR18,\
        ICR17, ICR16, ICR15, ICR14, ICR13, ICR12, ICR11, ICR10)
SFR_W_N(0x84, TCNT1, TCNT115, TCNT114, TCNT113, TCNT112, TCNT111, TCNT110, TCNT19, TCNT18,\
        TCNT17, TCNT16, TCNT15, TCNT14, TCNT13, TCNT12, TCNT11, TCNT10)
SFR_B_N(0x82, TCCR1C, FOC1A, FOC1B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x81, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
SFR_B_N(0x80, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, Dummy3, Dummy2, WGM11, WGM10)
SFR_B_N(0x7F, DIDR1, Dummy7, AMP2PD, ACMP0D, AMP0PD, AMP0ND, ADC10D, ADC9D, ADC8D)
SFR_B_N(0x7E, DIDR0, ADC7D, ADC6D, ADC5D, ADC4D, ADC3D, ADC2D, ADC1D, ADC0D)
SFR_B_N(0x7C, ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)
SFR_B_N(0x7B, ADCSRB, ADHSM, ISRCEN, AREFEN, Dummy4, ADTS3, ADTS2, ADTS1, ADTS0)
SFR_B_N(0x7A, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
SFR_W_R(0x78, ADC)
SFR_B_N(0x77, AMP2CSR, AMP2EN, AMP2IS, AMP2G1, AMP2G0, AMPCMP2, AMP2TS2, AMP2TS1, AMP2TS0)
SFR_B_N(0x76, AMP1CSR, AMP1EN, AMP1IS, AMP1G1, AMP1G0, AMPCMP1, AMP1TS2, AMP1TS1, AMP1TS0)
SFR_B_N(0x75, AMP0CSR, AMP0EN, AMP0IS, AMP0G1, AMP0G0, AMPCMP0, AMP0TS2, AMP0TS1, AMP0TS0)
SFR_B_N(0x6F, TIMSK1, Dummy7, Dummy6, ICIE1, Dummy4, Dummy3, OCIE1B, OCIE1A, TOIE1)
SFR_B_N(0x6E, TIMSK0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE0B, OCIE0A, TOIE0)
SFR_B_N(0x6D, PCMSK3, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PCINT26, PCINT25, PCINT24)
SFR_B_N(0x6C, PCMSK2, PCINT23, PCINT22, PCINT21, PCINT20, PCINT19, PCINT18, PCINT17, PCINT16)
SFR_B_N(0x6B, PCMSK1, PCINT15, PCINT14, PCINT13, PCINT12, PCINT11, PCINT10, PCINT9, PCINT8)
SFR_B_N(0x6A, PCMSK0, PCINT7, PCINT6, PCINT5, PCINT4, PCINT3, PCINT2, PCINT1, PCINT0)
SFR_B_N(0x69, EICRA, ISC31, ISC30, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)
SFR_B_N(0x68, PCICR, Dummy7, Dummy6, Dummy5, Dummy4, PCIE3, PCIE2, PCIE1, PCIE0)
SFR_B_N(0x66, OSCCAL, Dummy7, CAL6, CAL5, CAL4, CAL3, CAL2, CAL1, CAL0)
SFR_B_N(0x64, PRR, Dummy7, PRCAN, PRPSC, PRTIM1, PRTIM0, PRSPI, PRLIN, PRADC)
SFR_B_N(0x61, CLKPR, CLKPCE, Dummy6, Dummy5, Dummy4, CLKPS3, CLKPS2, CLKPS1, CLKPS0)
SFR_B_N(0x60, WDTCSR, WDIF, WDIE, WDP3, WDCE, WDE, WDP2, WDP1, WDP0)
SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
SFR_W_N(0x3D, SP, SP15, SP14, SP13, SP12, SP11, SP10, SP9, SP8,\
        SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
SFR_B_N(0x37, SPMCSR, SPMIE, RWWSB, Dummy5, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)
SFR_B_N(0x35, MCUCR, SPIPS, Dummy6, Dummy5, PUD, Dummy3, Dummy2, IVSEL, IVCE)
SFR_B_N(0x34, MCUSR, Dummy7, Dummy6, Dummy5, Dummy4, WDRF, BORF, EXTRF, PORF)
SFR_B_N(0x33, SMCR, Dummy7, Dummy6, Dummy5, Dummy4, SM2, SM1, SM0, SE)
SFR_B_R(0x32, MSMCR)
SFR_B_R(0x31, MONDR)
SFR_B_N(0x30, ACSR, AC3IF, AC2IF, AC1IF, AC0IF, AC3O, AC2O, AC1O, AC0O)
SFR_B_N(0x2E, SPDR, SPD7, SPD6, SPD5, SPD4, SPD3, SPD2, SPD1, SPD0)
SFR_B_N(0x2D, SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
SFR_B_N(0x2C, SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
SFR_B_N(0x29, PLLCSR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PLLF, PLLE, PLOCK)
SFR_B_N(0x28, OCR0B, OCR0B7, OCR0B6, OCR0B5, OCR0B4, OCR0B3, OCR0B2, OCR0B1, OCR0B0)
SFR_B_N(0x27, OCR0A, OCR0A7, OCR0A6, OCR0A5, OCR0A4, OCR0A3, OCR0A2, OCR0A1, OCR0A0)
SFR_B_N(0x26, TCNT0, TCNT07, TCNT06, TCNT05, TCNT04, TCNT03, TCNT02, TCNT01, TCNT00)
SFR_B_N(0x25, TCCR0B, FOC0A, FOC0B, Dummy5, Dummy4, WGM02, CS02, CS01, CS00)
SFR_B_N(0x24, TCCR0A, COM0A1, COM0A0, COM0B1, COM0B0, Dummy3, Dummy2, WGM01, WGM00)
SFR_B_N(0x23, GTCCR, TSM, ICPSEL1, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, PSRSYNC)
SFR_W_N(0x21, EEAR, Dummy15, Dummy14, Dummy13, Dummy12, Dummy11, Dummy10, EEAR9, EEAR8,\
        EEAR7, EEAR6, EEAR5, EEAR4, EEAR3, EEAR2, EEAR1, EEAR0)
SFR_B_N(0x20, EEDR, EEDR7, EEDR6, EEDR5, EEDR4, EEDR3, EEDR2, EEDR1, EEDR0)
SFR_B_N(0x1F, EECR, Dummy7, Dummy6, Dummy5, Dummy4, EERIE, EEMWE, EEWE, EERE)
SFR_B_N(0x1E, GPIOR0, GPIOR07, GPIOR06, GPIOR05, GPIOR04, GPIOR03, GPIOR02, GPIOR01, GPIOR00)
SFR_B_N(0x1D, EIMSK, Dummy7, Dummy6, Dummy5, Dummy4, INT3, INT2, INT1, INT0)
SFR_B_N(0x1C, EIFR, Dummy7, Dummy6, Dummy5, Dummy4, INTF3, INTF2, INTF1, INTF0)
SFR_B_N(0x1B, PCIFR, Dummy7, Dummy6, Dummy5, Dummy4, PCIF3, PCIF2, PCIF1, PCIF0)
SFR_B_N(0x1A, GPIOR2, GPIOR27, GPIOR26, GPIOR25, GPIOR24, GPIOR23, GPIOR22, GPIOR21, GPIOR20)
SFR_B_N(0x19, GPIOR1, GPIOR17, GPIOR16, GPIOR15, GPIOR14, GPIOR13, GPIOR12, GPIOR11, GPIOR10)
SFR_B_N(0x16, TIFR1, Dummy7, Dummy6, ICF1, Dummy4, Dummy3, OCF1B, OCF1A, TOV1)
SFR_B_N(0x15, TIFR0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF0B, OCF0A, TOV0)
SFR_B_N(0x0E, PORTE, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PORTE2, PORTE1, PORTE0)
SFR_B_N(0x0D, DDRE, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, DDE2, DDE1, DDE0)
SFR_B_N(0x0C, PINE, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PINE2, PINE1, PINE0)
SFR_B_N(0x0B, PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0)
SFR_B_N(0x0A, DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)
SFR_B_N(0x09, PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)
SFR_B_N(0x08, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
SFR_B_N(0x07, DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
SFR_B_N(0x05, PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0)
SFR_B_N(0x04, DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)
SFR_B_N(0x03, PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)


#ifndef __IOM32M1_H
#define __IOM32M1_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */
#define    RESET_vect           (0x00)  /* External Pin, Power-on Reset, Brown-out Reset, 
                                           Watchdog Reset and JTAG AVR Reset*/
#define    ANA_COMP0_vect       (0x04)  /* Analog Comparator 0 */
#define    ANA_COMP1_vect       (0x08)  /* Analog Comparator 1 */
#define    ANA_COMP2_vect       (0x0C)  /* Analog Comparator 2 */
#define    ANA_COMP3_vect       (0x10)  /* Analog Comparator 3 */
#define    PSC_FAULT_vect       (0x14)  /* PSC Fault */
#define    PSC_EC_vect          (0x18)  /* PSC End of Cycle */
#define    INT0_vect            (0x1C)  /* External Interrupt Request 0 */
#define    INT1_vect            (0x20)  /* External Interrupt Request 1 */
#define    INT2_vect            (0x24)  /* External Interrupt Request 2 */
#define    INT3_vect            (0x28)  /* External Interrupt Request 3 */
#define    TIMER1_CAPT_vect     (0x2C)  /* Timer/Counter1 Capture Event */
#define    TIMER1_COMPA_vect    (0x30)  /* Timer/Counter1 Compare Match A */
#define    TIMER1_COMPB_vect    (0x34)  /* Timer/Counter1 Compare Match B */
#define    TIMER1_OVF_vect      (0x38)  /* Timer1/Counter1 Overflow */
#define    TIMER0_COMPA_vect    (0x3C)  /* Timer/Counter0 Compare Match A */
#define    TIMER0_COMPB_vect    (0x40)  /* Timer/Counter0 Compare Match B */
#define    TIMER0_OVF_vect      (0x44)  /* Timer/Counter0 Overflow */
#define    CAN_INT_vect         (0x48)  /* CAN MOB, Burst, General Errors */
#define    CAN_TOVF_vect        (0x4C)  /* CAN Timer Overflow */
#define    LIN_TC_vect          (0x50)  /* LIN Transfer Complete */
#define    LIN_ERR_vect         (0x54)  /* LIN Error */
#define    PCINT0_vect          (0x58)  /* Pin Change Interrupt Request 0 */
#define    PCINT1_vect          (0x5C)  /* Pin Change Interrupt Request 1 */
#define    PCINT2_vect          (0x60)  /* Pin Change Interrupt Request 2 */
#define    PCINT3_vect          (0x64)  /* Pin Change Interrupt Request 3 */
#define    SPI_STC_vect         (0x68)  /* SPI Serial Transfer Complete */
#define    ADC_vect             (0x6C)  /* ADC Conversion Complete */
#define    WDT_vect             (0x70)  /* Watchdog Time-Out Interrupt */
#define    EE_RDY_vect          (0x74)  /* EEPROM Ready */
#define    SPM_RDY_vect         (0x78)  /* Store Program Memory Read */

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#endif /* __IAR_SYSTEMS_ASM__ */

#ifdef ENABLE_BIT_DEFINITIONS


/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/


  /* CANMSG */
#define MSG7 7
#define MSG6 6
#define MSG5 5
#define MSG4 4
#define MSG3 3
#define MSG2 2
#define MSG1 1
#define MSG0 0

  /* CANSTMPH */
#define TIMSTM15 7
#define TIMSTM14 6
#define TIMSTM13 5
#define TIMSTM12 4
#define TIMSTM11 3
#define TIMSTM10 2
#define TIMSTM9 1
#define TIMSTM8 0

  /* CANSTMPL */
#define TIMSTM7 7
#define TIMSTM6 6
#define TIMSTM5 5
#define TIMSTM4 4
#define TIMSTM3 3
#define TIMSTM2 2
#define TIMSTM1 1
#define TIMSTM0 0

  /* CANIDM1 */
#define IDMSK28 7
#define IDMSK27 6
#define IDMSK26 5
#define IDMSK25 4
#define IDMSK24 3
#define IDMSK23 2
#define IDMSK22 1
#define IDMSK21 0

  /* CANIDM2 */
#define IDMSK20 7
#define IDMSK19 6
#define IDMSK18 5
#define IDMSK17 4
#define IDMSK16 3
#define IDMSK15 2
#define IDMSK14 1
#define IDMSK13 0

  /* CANIDM3 */
#define IDMSK12 7
#define IDMSK11 6
#define IDMSK10 5
#define IDMSK9 4
#define IDMSK8 3
#define IDMSK7 2
#define IDMSK6 1
#define IDMSK5 0

  /* CANIDM4 */
#define IDMSK4 7
#define IDMSK3 6
#define IDMSK2 5
#define IDMSK1 4
#define IDMSK0 3
#define RTRMSK 2
#define IDEMSK 0

  /* CANIDT1 */
#define IDT28 7
#define IDT27 6
#define IDT26 5
#define IDT25 4
#define IDT24 3
#define IDT23 2
#define IDT22 1
#define IDT21 0

  /* CANIDT2 */
#define IDT20 7
#define IDT19 6
#define IDT18 5
#define IDT17 4
#define IDT16 3
#define IDT15 2
#define IDT14 1
#define IDT13 0

  /* CANIDT3 */
#define IDT12 7
#define IDT11 6
#define IDT10 5
#define IDT9 4
#define IDT8 3
#define IDT7 2
#define IDT6 1
#define IDT5 0

  /* CANIDT4 */
#define IDT4 7
#define IDT3 6
#define IDT2 5
#define IDT1 4
#define IDT0 3
#define RTRTAG 2
#define RB1TAG 1
#define RB0TAG 0

  /* CANCDMOB */
#define CONMOB1 7
#define CONMOB0 6
#define RPLV 5
#define IDE 4
#define DLC3 3
#define DLC2 2
#define DLC1 1
#define DLC0 0

  /* CANSTMOB */
#define DLCW 7
#define TXOK 6
#define RXOK 5
#define BERR 4
#define SERR 3
#define CERR 2
#define FERR 1
#define AERR 0

  /* CANPAGE */
#define MOBNB3 7
#define MOBNB2 6
#define MOBNB1 5
#define MOBNB0 4
#define AINC 3
#define INDX2 2
#define INDX1 1
#define INDX0 0

  /* CANHPMOB */
#define HPMOB3 7
#define HPMOB2 6
#define HPMOB1 5
#define HPMOB0 4
#define CGP3 3
#define CGP2 2
#define CGP1 1
#define CGP0 0

  /* CANREC */
#define REC7 7
#define REC6 6
#define REC5 5
#define REC4 4
#define REC3 3
#define REC2 2
#define REC1 1
#define REC0 0

  /* CANTEC */
#define TEC7 7
#define TEC6 6
#define TEC5 5
#define TEC4 4
#define TEC3 3
#define TEC2 2
#define TEC1 1
#define TEC0 0

  /* CANTTCH */
#define TIMTTC15 7
#define TIMTTC14 6
#define TIMTTC13 5
#define TIMTTC12 4
#define TIMTTC11 3
#define TIMTTC10 2
#define TIMTTC9 1
#define TIMTTC8 0

  /* CANTTCL */
#define TIMTTC7 7
#define TIMTTC6 6
#define TIMTTC5 5
#define TIMTTC4 4
#define TIMTTC3 3
#define TIMTTC2 2
#define TIMTTC1 1
#define TIMTTC0 0

  /* CANTIMH */
#define CANTIM15 7
#define CANTIM14 6
#define CANTIM13 5
#define CANTIM12 4
#define CANTIM11 3
#define CANTIM10 2
#define CANTIM9 1
#define CANTIM8 0

  /* CANTIML */
#define CANTIM7 7
#define CANTIM6 6
#define CANTIM5 5
#define CANTIM4 4
#define CANTIM3 3
#define CANTIM2 2
#define CANTIM1 1
#define CANTIM0 0

  /* CANTCON */
#define TPRSC7 7
#define TPRSC6 6
#define TPRSC5 5
#define TPRSC4 4
#define TPRSC3 3
#define TPRSC2 2
#define TRPSC1 1
#define TPRSC0 0

  /* CANBT3 */
#define PHS22 6
#define PHS21 5
#define PHS20 4
#define PHS12 3
#define PHS11 2
#define PHS10 1
#define SMP 0

  /* CANBT2 */
#define SJW1 6
#define SJW0 5
#define PRS2 3
#define PRS1 2
#define PRS0 1

  /* CANBT1 */
#define BRP5 6
#define BRP4 5
#define BRP3 4
#define BRP2 3
#define BRP1 2
#define BRP0 1

  /* CANSIT1 */

  /* CANSIT2 */
#define SIT5 5
#define SIT4 4
#define SIT3 3
#define SIT2 2
#define SIT1 1
#define SIT0 0

  /* CANIE1 */

  /* CANIE2 */
#define IEMOB5 5
#define IEMOB4 4
#define IEMOB3 3
#define IEMOB2 2
#define IEMOB1 1
#define IEMOB0 0

  /* CANEN1 */

  /* CANEN2 */
#define ENMOB5 5
#define ENMOB4 4
#define ENMOB3 3
#define ENMOB2 2
#define ENMOB1 1
#define ENMOB0 0

  /* CANGIE */
#define ENIT 7
#define ENBOFF 6
#define ENRX 5
#define ENTX 4
#define ENERR 3
#define ENBX 2
#define ENERG 1
#define ENOVRT 0

  /* CANGIT */
#define CANIT 7
#define BOFFIT 6
#define OVRTIM 5
#define BXOK 4
#define SERG 3
#define CERG 2
#define FERG 1
#define AERG 0

  /* CANGSTA */
#define OVRG 6
#define TXBSY 4
#define RXBSY 3
#define ENFG 2
#define BOFF 1
#define ERRP 0

  /* CANGCON */
#define ABRQ 7
#define OVRQ 6
#define TTC 5
#define SYNTTC 4
#define LISTEN 3
#define TEST 2
#define ENASTB 1
#define SWRES 0

  /* LINDAT */
#define LDATA7 7
#define LDATA6 6
#define LDATA5 5
#define LDATA4 4
#define LDATA3 3
#define LDATA2 2
#define LDATA1 1
#define LDATA0 0

  /* LINSEL */
#define LAINC 3
#define LINDX2 2
#define LINDX1 1
#define LINDX0 0

  /* LINIDR */
#define LP1 7
#define LP0 6
#define LID5 5
#define LDL1 LID5
#define LID4 4
#define LDL0 LID4
#define LID3 3
#define LID2 2
#define LID1 1
#define LID0 0

  /* LINDLR */
#define LTXDL3 7
#define LTXDL2 6
#define LTXDL1 5
#define LTXDL0 4
#define LRXDL3 3
#define LRXDL2 2
#define LRXDL1 1
#define LRXDL0 0

  /* LINBRRH */
#define LDIV11 3
#define LDIV10 2
#define LDIV9 1
#define LDIV8 0

  /* LINBRRL */
#define LDIV7 7
#define LDIV6 6
#define LDIV5 5
#define LDIV4 4
#define LDIV3 3
#define LDIV2 2
#define LDIV1 1
#define LDIV0 0

  /* LINBTR */
#define LDISR 7
#define LBT5 5
#define LBT4 4
#define LBT3 3
#define LBT2 2
#define LBT1 1
#define LBT0 0

  /* LINERR */
#define LABORT 7
#define LTOERR 6
#define LOVERR 5
#define LFERR 4
#define LSERR 3
#define LPERR 2
#define LCERR 1
#define LBERR 0

  /* LINENIR */
#define LENERR 3
#define LENIDOK 2
#define LENTXOK 1
#define LENRXOK 0

  /* LINSIR */
#define LIDST2 7
#define LIDST1 6
#define LIDST0 5
#define LBUSY 4
#define LERR 3
#define LIDOK 2
#define LTXOK 1
#define LRXOK 0

  /* LINCR */
#define LSWRES 7
#define LIN13 6
#define LCONF1 5
#define LCONF0 4
#define LENA 3
#define LCMD2 2
#define LCMD1 1
#define LCMD0 0

  /* PIFR */
#define PEV2 3
#define PEV1 2
#define PEV0 1
#define PEOP 0

  /* PIM */
#define PEVE2 3
#define PEVE1 2
#define PEVE0 1
#define PEOPE 0

  /* PMIC2 */
#define POVEN2 7
#define PISEL2 6
#define PELEV2 5
#define PFLTE2 4
#define PAOC2 3
#define PRFM22 2
#define PRFM21 1
#define PRFM20 0

  /* PMIC1 */
#define POVEN1 7
#define PISEL1 6
#define PELEV1 5
#define PFLTE1 4
#define PAOC1 3
#define PRFM12 2
#define PRFM11 1
#define PRFM10 0

  /* PMIC0 */
#define POVEN0 7
#define PISEL0 6
#define PELEV0 5
#define PFLTE0 4
#define PAOC0 3
#define PRFM02 2
#define PRFM01 1
#define PRFM00 0

  /* PCTL */
#define PPRE1 7
#define PPRE0 6
#define PCLKSEL 5
#define PCCYC 1
#define PRUN 0

  /* POC */
#define POEN2B 5
#define POEN2A 4
#define POEN1B 3
#define POEN1A 2
#define POEN0B 1
#define POEN0A 0

  /* PCNF */
#define PULOCK 5
#define PMODE 4
#define POPB 3
#define POPA 2

  /* PSYNC */
#define PSYNC21 5
#define PSYNC20 4
#define PSYNC11 3
#define PSYNC10 2
#define PSYNC01 1
#define PSYNC00 0

  /* POCR_RBH */
#define POCR_RB11 3
#define POCR_RB10 2
#define POCR_RB9 1
#define POCR_RB8 0

  /* POCR_RBL */
#define POCR_RB7 7
#define POCR_RB6 6
#define POCR_RB5 5
#define POCR_RB4 4
#define POCR_RB3 3
#define POCR_RB2 2
#define POCR_RB1 1
#define POCR_RB0 0

  /* POCR2SBH */
#define POCR2SB11 3
#define POCR2SB10 2
#define POCR2SB9 1
#define POCR2SB8 0

  /* POCR2SBL */
#define POCR2SB7 7
#define POCR2SB6 6
#define POCR2SB5 5
#define POCR2SB4 4
#define POCR2SB3 3
#define POCR2SB2 2
#define POCR2SB1 1
#define POCR2SB0 0

  /* POCR2RAH */
#define POCR2RA11 3
#define POCR2RA10 2
#define POCR2RA9 1
#define POCR2RA8 0

  /* POCR2RAL */
#define POCR2RA7 7
#define POCR2RA6 6
#define POCR2RA5 5
#define POCR2RA4 4
#define POCR2RA3 3
#define POCR2RA2 2
#define POCR2RA1 1
#define POCR2RA0 0

  /* POCR2SAH */
#define POCR2SA11 3
#define POCR2SA10 2
#define POCR2SA9 1
#define POCR2SA8 0

  /* POCR2SAL */
#define POCR2SA7 7
#define POCR2SA6 6
#define POCR2SA5 5
#define POCR2SA4 4
#define POCR2SA3 3
#define POCR2SA2 2
#define POCR2SA1 1
#define POCR2SA0 0

  /* POCR1SBH */
#define POCR1SB11 3
#define POCR1SB10 2
#define POCR1SB9 1
#define POCR1SB8 0

  /* POCR1SBL */
#define POCR1SB7 7
#define POCR1SB6 6
#define POCR1SB5 5
#define POCR1SB4 4
#define POCR1SB3 3
#define POCR1SB2 2
#define POCR1SB1 1
#define POCR1SB0 0

  /* POCR1RAH */
#define POCR1RA11 3
#define POCR1RA10 2
#define POCR1RA9 1
#define POCR1RA8 0

  /* POCR1RAL */
#define POCR1RA7 7
#define POCR1RA6 6
#define POCR1RA5 5
#define POCR1RA4 4
#define POCR1RA3 3
#define POCR1RA2 2
#define POCR1RA1 1
#define POCR1RA0 0

  /* POCR1SAH */
#define POCR1SA11 3
#define POCR1SA10 2
#define POCR1SA9 1
#define POCR1SA8 0

  /* POCR1SAL */
#define POCR1SA7 7
#define POCR1SA6 6
#define POCR1SA5 5
#define POCR1SA4 4
#define POCR1SA3 3
#define POCR1SA2 2
#define POCR1SA1 1
#define POCR1SA0 0

  /* POCR0SBH */
#define POCR0SB11 3
#define POCR0SB10 2
#define POCR0SB9 1
#define POCR0SB8 0

  /* POCR0SBL */
#define POCR0SB7 7
#define POCR0SB6 6
#define POCR0SB5 5
#define POCR0SB4 4
#define POCR0SB3 3
#define POCR0SB2 2
#define POCR0SB1 1
#define POCR0SB0 0

  /* POCR0RAH */
#define POCR0RA11 3
#define POCR0RA10 2
#define POCR0RA9 1
#define POCR0RA8 0

  /* POCR0RAL */
#define POCR0RA7 7
#define POCR0RA6 6
#define POCR0RA5 5
#define POCR0RA4 4
#define POCR0RA3 3
#define POCR0RA2 2
#define POCR0RA1 1
#define POCR0RA0 0

  /* POCR0SAH */
#define POCR0SA11 3
#define POCR0SA10 2
#define POCR0SA9 1
#define POCR0SA8 0

  /* POCR0SAL */
#define POCR0SA7 7
#define POCR0SA6 6
#define POCR0SA5 5
#define POCR0SA4 4
#define POCR0SA3 3
#define POCR0SA2 2
#define POCR0SA1 1
#define POCR0SA0 0

  /* AC3CON */
#define AC3EN 7
#define AC3IE 6
#define AC3IS1 5
#define AC3IS0 4
#define AC3M2 2
#define AC3M1 1
#define AC3M0 0

  /* AC2CON */
#define AC2EN 7
#define AC2IE 6
#define AC2IS1 5
#define AC2IS0 4
#define AC2M2 2
#define AC2M1 1
#define AC2M0 0

  /* AC1CON */
#define AC1EN 7
#define AC1IE 6
#define AC1IS1 5
#define AC1IS0 4
#define AC1ICE 3
#define AC1M2 2
#define AC1M1 1
#define AC1M0 0

  /* AC0CON */
#define AC0EN 7
#define AC0IE 6
#define AC0IS1 5
#define AC0IS0 4
#define ACCKSEL 3
#define AC0M2 2
#define AC0M1 1
#define AC0M0 0

  /* DACON */
#define DAATE 7
#define DATS2 6
#define DATS1 5
#define DATS0 4
#define DALA 2
#define DAOE 1
#define DAEN 0

  /* OCR1BH */
#define OCR1B15 7
#define OCR1B14 6
#define OCR1B13 5
#define OCR1B12 4
#define OCR1B11 3
#define OCR1B10 2
#define OCR1B9 1
#define OCR1B8 0

  /* OCR1BL */
#define OCR1B7 7
#define OCR1B6 6
#define OCR1B5 5
#define OCR1B4 4
#define OCR1B3 3
#define OCR1B2 2
#define OCR1B1 1
#define OCR1B0 0

  /* OCR1AH */
#define OCR1A15 7
#define OCR1A14 6
#define OCR1A13 5
#define OCR1A12 4
#define OCR1A11 3
#define OCR1A10 2
#define OCR1A9 1
#define OCR1A8 0

  /* OCR1AL */
#define OCR1A7 7
#define OCR1A6 6
#define OCR1A5 5
#define OCR1A4 4
#define OCR1A3 3
#define OCR1A2 2
#define OCR1A1 1
#define OCR1A0 0

  /* ICR1H */
#define ICR115 7
#define ICR114 6
#define ICR113 5
#define ICR112 4
#define ICR111 3
#define ICR110 2
#define ICR19 1
#define ICR18 0

  /* ICR1L */
#define ICR17 7
#define ICR16 6
#define ICR15 5
#define ICR14 4
#define ICR13 3
#define ICR12 2
#define ICR11 1
#define ICR10 0

  /* TCNT1H */
#define TCNT115 7
#define TCNT114 6
#define TCNT113 5
#define TCNT112 4
#define TCNT111 3
#define TCNT110 2
#define TCNT19 1
#define TCNT18 0

  /* TCNT1L */
#define TCNT17 7
#define TCNT16 6
#define TCNT15 5
#define TCNT14 4
#define TCNT13 3
#define TCNT12 2
#define TCNT11 1
#define TCNT10 0

  /* TCCR1C */
#define FOC1A 7
#define FOC1B 6

  /* TCCR1B */
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

  /* TCCR1A */
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define WGM11 1
#define WGM10 0

  /* DIDR1 */
#define AMP2PD 6
#define ACMP0D 5
#define AMP0PD 4
#define AMP0ND 3
#define ADC10D 2
#define ADC9D 1
#define ADC8D 0

  /* DIDR0 */
#define ADC7D 7
#define ADC6D 6
#define ADC5D 5
#define ADC4D 4
#define ADC3D 3
#define ADC2D 2
#define ADC1D 1
#define ADC0D 0

  /* ADMUX */
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4 4
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

  /* ADCSRB */
#define ADHSM 7
#define ISRCEN 6
#define AREFEN 5
#define ADTS3 3
#define ADTS2 2
#define ADTS1 1
#define ADTS0 0

  /* ADCSRA */
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0


  /* AMP2CSR */
#define AMP2EN 7
#define AMP2IS 6
#define AMP2G1 5
#define AMP2G0 4
#define AMPCMP2 3
#define AMP2TS2 2
#define AMP2TS1 1
#define AMP2TS0 0

  /* AMP1CSR */
#define AMP1EN 7
#define AMP1IS 6
#define AMP1G1 5
#define AMP1G0 4
#define AMPCMP1 3
#define AMP1TS2 2
#define AMP1TS1 1
#define AMP1TS0 0

  /* AMP0CSR */
#define AMP0EN 7
#define AMP0IS 6
#define AMP0G1 5
#define AMP0G0 4
#define AMPCMP0 3
#define AMP0TS2 2
#define AMP0TS1 1
#define AMP0TS0 0

  /* TIMSK1 */
#define ICIE1 5
#define OCIE1B 2
#define OCIE1A 1
#define TOIE1 0

  /* TIMSK0 */
#define OCIE0B 2
#define OCIE0A 1
#define TOIE0 0

  /* PCMSK3 */
#define PCINT26 2
#define PCINT25 1
#define PCINT24 0

  /* PCMSK2 */
#define PCINT23 7
#define PCINT22 6
#define PCINT21 5
#define PCINT20 4
#define PCINT19 3
#define PCINT18 2
#define PCINT17 1
#define PCINT16 0

  /* PCMSK1 */
#define PCINT15 7
#define PCINT14 6
#define PCINT13 5
#define PCINT12 4
#define PCINT11 3
#define PCINT10 2
#define PCINT9 1
#define PCINT8 0

  /* PCMSK0 */
#define PCINT7 7
#define PCINT6 6
#define PCINT5 5
#define PCINT4 4
#define PCINT3 3
#define PCINT2 2
#define PCINT1 1
#define PCINT0 0

  /* EICRA */
#define ISC31 7
#define ISC30 6
#define ISC21 5
#define ISC20 4
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0

  /* PCICR */
#define PCIE3 3
#define PCIE2 2
#define PCIE1 1
#define PCIE0 0

  /* OSCCAL */
#define CAL6 6
#define CAL5 5
#define CAL4 4
#define CAL3 3
#define CAL2 2
#define CAL1 1
#define CAL0 0

  /* PRR */
#define PRCAN 6
#define PRPSC 5
#define PRTIM1 4
#define PRTIM0 3
#define PRSPI 2
#define PRLIN 1
#define PRADC 0

  /* CLKPR */
#define CLKPCE 7
#define CLKPS3 3
#define CLKPS2 2
#define CLKPS1 1
#define CLKPS0 0

  /* WDTCSR */
#define WDIF 7
#define WDIE 6
#define WDP3 5
#define WDCE 4
#define WDE 3
#define WDP2 2
#define WDP1 1
#define WDP0 0

  /* SPH */
#define SP15 7
#define SP14 6
#define SP13 5
#define SP12 4
#define SP11 3
#define SP10 2
#define SP9 1
#define SP8 0

  /* SPL */
#define SP7 7
#define SP6 6
#define SP5 5
#define SP4 4
#define SP3 3
#define SP2 2
#define SP1 1
#define SP0 0

  /* SPMCSR */
#define SPMIE 7
#define RWWSB 6
#define RWWSRE 4
#define BLBSET 3
#define PGWRT 2
#define PGERS 1
#define SPMEN 0

  /* MCUCR */
#define SPIPS 7
#define PUD 4
#define IVSEL 1
#define IVCE 0

  /* MCUSR */
#define WDRF 3
#define BORF 2
#define EXTRF 1
#define PORF 0

  /* SMCR */
#define SM2 3
#define SM1 2
#define SM0 1
#define SE 0

  /* ACSR */
#define AC3IF 7
#define AC2IF 6
#define AC1IF 5
#define AC0IF 4
#define AC3O 3
#define AC2O 2
#define AC1O 1
#define AC0O 0

  /* SPDR */
#define SPD7 7
#define SPD6 6
#define SPD5 5
#define SPD4 4
#define SPD3 3
#define SPD2 2
#define SPD1 1
#define SPD0 0

  /* SPSR */
#define SPIF 7
#define WCOL 6
#define SPI2X 0

  /* SPCR */
#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

  /* PLLCSR */
#define PLLF 2
#define PLLE 1
#define PLOCK 0

  /* OCR0B */
#define OCR0B7 7
#define OCR0B6 6
#define OCR0B5 5
#define OCR0B4 4
#define OCR0B3 3
#define OCR0B2 2
#define OCR0B1 1
#define OCR0B0 0

  /* OCR0A */
#define OCR0A7 7
#define OCR0A6 6
#define OCR0A5 5
#define OCR0A4 4
#define OCR0A3 3
#define OCR0A2 2
#define OCR0A1 1
#define OCR0A0 0

  /* TCNT0 */
#define TCNT07 7
#define TCNT06 6
#define TCNT05 5
#define TCNT04 4
#define TCNT03 3
#define TCNT02 2
#define TCNT01 1
#define TCNT00 0

  /* TCCR0B */
#define FOC0A 7
#define FOC0B 6
#define WGM02 3
#define CS02 2
#define CS01 1
#define CS00 0

  /* TCCR0A */
#define COM0A1 7
#define COM0A0 6
#define COM0B1 5
#define COM0B0 4
#define WGM01 1
#define WGM00 0

  /* GTCCR */
#define TSM 7
#define ICPSEL1 6
#define PSRSYNC 0

  /* EEARH */
#define EEAR9 1
#define EEAR8 0

  /* EEARL */
#define EEAR7 7
#define EEAR6 6
#define EEAR5 5
#define EEAR4 4
#define EEAR3 3
#define EEAR2 2
#define EEAR1 1
#define EEAR0 0

  /* EEDR */
#define EEDR7 7
#define EEDR6 6
#define EEDR5 5
#define EEDR4 4
#define EEDR3 3
#define EEDR2 2
#define EEDR1 1
#define EEDR0 0

  /* EECR */
#define EERIE 3
#define EEMWE 2
#define EEWE 1
#define EERE 0

  /* GPIOR0 */
#define GPIOR07 7
#define GPIOR06 6
#define GPIOR05 5
#define GPIOR04 4
#define GPIOR03 3
#define GPIOR02 2
#define GPIOR01 1
#define GPIOR00 0

  /* EIMSK */
#define INT3 3
#define INT2 2
#define INT1 1
#define INT0 0

  /* EIFR */
#define INTF3 3
#define INTF2 2
#define INTF1 1
#define INTF0 0

  /* PCIFR */
#define PCIF3 3
#define PCIF2 2
#define PCIF1 1
#define PCIF0 0

  /* GPIOR2 */
#define GPIOR27 7
#define GPIOR26 6
#define GPIOR25 5
#define GPIOR24 4
#define GPIOR23 3
#define GPIOR22 2
#define GPIOR21 1
#define GPIOR20 0

  /* GPIOR1 */
#define GPIOR17 7
#define GPIOR16 6
#define GPIOR15 5
#define GPIOR14 4
#define GPIOR13 3
#define GPIOR12 2
#define GPIOR11 1
#define GPIOR10 0

  /* TIFR1 */
#define ICF1 5
#define OCF1B 2
#define OCF1A 1
#define TOV1 0

  /* TIFR0 */
#define OCF0B 2
#define OCF0A 1
#define TOV0 0

  /* PORTE */
#define PORTE2 2
#define PORTE1 1
#define PORTE0 0

  /* DDRE */
#define DDE2 2
#define DDE1 1
#define DDE0 0

  /* PINE */
#define PINE2 2
#define PINE1 1
#define PINE0 0

  /* PORTD */
#define PORTD7 7
#define PORTD6 6
#define PORTD5 5
#define PORTD4 4
#define PORTD3 3
#define PORTD2 2
#define PORTD1 1
#define PORTD0 0

  /* DDRD */
#define DDD7 7
#define DDD6 6
#define DDD5 5
#define DDD4 4
#define DDD3 3
#define DDD2 2
#define DDD1 1
#define DDD0 0

  /* PIND */
#define PIND7 7
#define PIND6 6
#define PIND5 5
#define PIND4 4
#define PIND3 3
#define PIND2 2
#define PIND1 1
#define PIND0 0

  /* PORTC */
#define PORTC7 7
#define PORTC6 6
#define PORTC5 5
#define PORTC4 4
#define PORTC3 3
#define PORTC2 2
#define PORTC1 1
#define PORTC0 0

  /* DDRC */
#define DDC7 7
#define DDC6 6
#define DDC5 5
#define DDC4 4
#define DDC3 3
#define DDC2 2
#define DDC1 1
#define DDC0 0

  /* PINC */
#define PINC7 7
#define PINC6 6
#define PINC5 5
#define PINC4 4
#define PINC3 3
#define PINC2 2
#define PINC1 1
#define PINC0 0

  /* PORTB */
#define PORTB7 7
#define PORTB6 6
#define PORTB5 5
#define PORTB4 4
#define PORTB3 3
#define PORTB2 2
#define PORTB1 1
#define PORTB0 0

  /* DDRB */
#define DDB7 7
#define DDB6 6
#define DDB5 5
#define DDB4 4
#define DDB3 3
#define DDB2 2
#define DDB1 1
#define DDB0 0

  /* PINB */
#define PINB7 7
#define PINB6 6
#define PINB5 5
#define PINB4 4
#define PINB3 3
#define PINB2 2
#define PINB1 1
#define PINB0 0



/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* Constants */
#define    RAMEND   0x08FF    /*Last On-Chip SRAM location*/
#define    XRAMEND  0x08FF
#define    E2END    0x03FF
#define    FLASHEND 0x7FFF

#endif /* ENABLE_BIT_DEFINITIONS */ 
#endif /* __IOM32M1_H (define part) */
#endif /* __IOM32M1_H (SFR part) */
