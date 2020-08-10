/*
 * Registers.h
 *
 *  Created on: Mar 22, 2020
 *      Author: elkarnk
 */
/******* SPECIAL PINS
 * PA[1:0] UART0
 * PA[5:2] SSI0
 * PB[3:2] I2C0
 * PC[3:0] JTAG
 * PD[7] GPIO
 * PF[0] GPIO
 * */
#ifndef REGISTERS_H_
#define REGISTERS_H_


#define NOOFFSET 0
/*****PORT***/
enum PORTNUM{PORTA,PORTB,PORTC,PORTD,PORTE = 32,PORTF};
/*****PINS***/
enum PINSNUM{PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7};
/****DIRECTION*///
enum PINSTATE {OUTPUT,INPUT,INPUT_PULLUP,INPUT_PULLDOWN,INPUT_OPENDRAIN,INTERUPT_PULLUP,INTERUPT_PULLDOWN,INTERUPT_OPENDRAIN,RX,TX,ANALOG_INPUT,SCL,SDA};
/*****VOLTAGE*/
enum VOLT{LOW,HIGH};
/***INTERRUPT*/
enum Interupt{levelSensitive,DetectBothedges,RisingEdge,fallingEdge};
enum InterruptMODE{InteruptedPin,InteruptedPort};
/******TIMER***/
enum MODE {NORMAL,WIDE};
enum TIMER {TIMER0,TIMER1,TIMER2,TIMER3,TIMER4,TIMER5,WTIMER0,WTIMER1,WTIMER2=28,WTIMER3,WTIMER4,WTIMER5};
enum WTIMER{WIDETIMER0,WIDETIMER1,WIDETIMER2,WIDETIMER3,WIDETIMER4,WIDETIMER5};
enum TIMERTYPE{TA,TB=8};
#define ONESECPERIOD (0x00F42400)
/*******UART*/
enum UART{UART0,UART1C,UART1B=1,UART2,UART3,UART4,UART5,UART6,UART7};
/*****ADC***/
enum ADC_PINS{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,AIN10,AIN11};
enum ADC{ADC0,ADC1};
enum SS{SS0,SS1,SS2,SS3}; // No of samples = same no of FIFO  = 8:4:4:1
/*****PWM*****/
enum PWM{PWM0,PWM1};
enum GENERATOR{GEN0,GEN1,GEN2,GEN3};
enum PWMPINS{PWMPIN0,PWMPIN1,PWMPIN2,PWMPIN3,PWMPIN4,PWMPIN5,PWMPIN6,PWMPIN7};
enum PWMMODE{UP_DOWNMODE,DOWNMODE};
/***********I2C***************/
enum I2C{I2C0,I2C1,I2C2,I2C3};
enum I2CMODE{LOOPBACK,MASTER=4,SLAVE,I2CGLITCHFILTER};

/*****GET ADRESS*/
#define BaseGBIOAdress (0x40004000)
#define BaseTIMERAdress (0x40030000)
#define BaseINTERUPTAdress (0xE000E000)
#define BaseUARTAdress (0x4000C000)
#define BaseADCAdress (0x40038000)
#define BasePwmAdress (0x40028000)
#define BaseI2CAdress (0x40020000)
/*******GETTING REG**/
#define GETREG(BaseAdrress,Offset,Prephiral) (*((volatile unsigned long *) (BaseAdrress+((0x1000)*Prephiral)+ Offset)))
/****BUILT IN FEATURES ***/
#define RED PIN1
#define BLUE PIN2
#define GREEN PIN3
#define LEDPORT PORTF
#define SWITCHPORT PORTF
#define SW2 PIN0
#define SW1 PIN4

/***Offset*/
/****GBIO**/
#define GPIOIS (0x404)
#define GPIOIBE (0x408)
#define GPIOIEV (0x40C)
#define GPIOIM (0x410)
#define GPIORIS (0x414)
#define GPIOIMIS (0x418)
#define GPIOICR (0x41C)
#define GPIODIR (0x400)
#define GPIOAFSEL (0x420)
#define GPIOSLR (0x518)
#define GPIODEN (0x51C)
#define GPIOLOCK (0x520)
#define GPIODATA (0x3FC)
#define GPIOCR (0x524)
#define GPIOAMSEL (0x528)
#define GPIOPCTL (0x52C)
#define GPIODR2R (0x500)
#define GPIODR4R (0x504)      //DRIVEN 4mA
#define GPIODR8R (0x508)  // DRIVEN 8mA
#define GPIOPUR (0x510)      // PULL UP
#define GPIOPDR (0x514)      // PULL DOWN
#define GPIOODR (0x50C)      // OPEN DRAIN
#define GPIOADCCTL (0x530)
#define GPIOCR (0x524)
/****TIMER ***/
#define GPTMCFG (0X000)
#define GPTMTAMR (0X004)
#define GPTMTBMR (0X008)
#define GPTMCTL (0X00C)   //
#define GPTMSYNC (0X010)  //SOFTWARE SYNC
#define GPTMIMR (0X018)  //INTERRUPT MASK
#define GPTMRIS (0X01C)  //RAW INTERRUPT STATUES MASK
#define GPTMICR (0x024)
#define GPTMTAILR (0x028) //  TIMER A COUNT NUMBER
#define GPTMTBILR (0x02C) //  TIMER B COUNT NUMBER
/***********INTERRUPT********/
#define ENO (0x100)
#define EN1 (0x104)
#define EN2 (0x108)
#define EN3 (0x10C)
#define EN4 (0x110)

#define DIS0 (0x180)
#define DIS1 (0x184)
#define DIS2 (0x188)
#define DIS3 (0x18C)
#define DIS4 (0x190)

#define PEND0 (0x200)
#define PEND1 (0x204)
#define PEND2 (0x208)
#define PEND3 (0x20C)
#define PEND4 (0x210)

#define UNPEND0 (0x280)
#define UNPEND1 (0x284)
#define UNPEND2 (0x288)
#define UNPEND3 (0x28C)
#define UNPEND4 (0x290)


#define ACTIVE0 (0x300)
#define ACTIVE1 (0x304)
#define ACTIVE2 (0x308)
#define ACTIVE3 (0x30C)
#define ACTIVE4 (0x310)

#define PRI0 (0x400) //0-3
#define PRI1 (0x404) //0-3
#define PRI2 (0x408) //0-3
#define PRI3 (0x40C) //0-3
#define PRI4 (0x410) //0-3
#define PRI5 (0x414) //0-3
#define PRI6 (0x418) //0-3
#define PRI7 (0x41C) //0-3
#define PRI8 (0x420) //0-3
#define PRI9 (0x424) //0-3
#define PRI10 (0x428) //0-3
#define PRI11 (0x42C) //0-3
#define PRI12 (0x430) //0-3
#define PRI13 (0x434) //0-3
#define PRI14 (0x438) //0-3
#define PRI15 (0x43C) //0-3
/******UART*/
#define UARTDR (0x000) //DATA
#define UARTRSR (0x004) //RECEIVE STATUE
#define UARTECR (0x004) // ERROR CLEAR
#define UARTFR (0x018) //FLAG
#define UARTILPR (0x020) //LOW POWER
#define UARTIBRD (0x024) //INTERGER BAUD RATE DIVISOR
#define UARTFBRD (0x028) //FRACTIONAL BAUD RATE DIVISOR
#define UARTLCRH (0x02C) //LINE CONTROL
#define UARTCTL (0x030) //CONTROL
#define UARTIFLS (0x034) //INTERRUPT FIFO LEVEL SELECT
#define UARTIM (0x038) //INTERRUPT MASK
#define UARTRIS (0x03C) //RAW INTERRUPT MASK
#define UARTMIS (0x040) //MASKED INTERRUPT STATUS
#define UARTICR (0x044) //INTERRUPT CLEAR
#define UARTDMACTL (0x048) //DMA CLEAR
#define UART9BITADDR (0x0A4) //9-BIT SELF ADDRESS
#define UART9BITAMASK (0x0A8) //MASKED 9-BIT SELF ADDRESS
#define UARTPP (0xFCO) //PERIPHERAIL ADDRESS
#define UARTCC (0xFC8) //PERIPHERAIL ADDRESS CONTROL
//*****ADC****/
#define ADCACTSS (0X000)
#define ADCRIS (0X004)
#define ADCIM (0X008)
#define ADCISC (0X00C)
#define ADCOSTAT (0X010)
#define ADCEMUX (0X014)
#define ADCUSTAT (0X018)
#define ADCTSSET (0X01C)
#define ADCSSPRI (0X020)
#define ADCSPC (0X024)
#define ADCPSSI (0X028)
#define ADCSAC (0X030)
#define ADCDCISC (0X034)
#define ADCCTL (0X038)

#define ADCSSCTL0 (0X044)
#define ADCSSCTL1 (0X064)
#define ADCSSCTL2 (0X084)
#define ADCSSCTL3 (0X0A4)

#define ADCSSMUX0 (0X040)
#define ADCSSMUX1 (0X060)
#define ADCSSMUX2 (0X080)
#define ADCSSMUX3 (0X0A0)

#define ADCSSFIFO0 (0x048)
#define ADCSSFIFO1 (0x068)
#define ADCSSFIFO2 (0x088)
#define ADCSSFIFO3 (0x0A8)

#define ADCSSFSTAT0 (0X04C)
#define ADCSSFSTAT1 (0X06C)
#define ADCSSFSTAT2 (0X08C)
#define ADCSSFSTAT3 (0X0AC)
/*****PWM****/
#define PWMCTL (0x000)
#define PWMSYNC (0x004)
#define PWMENABLE (0x008)
#define PWMINVERT (0x00C)
#define PWMFAULT (0x010)
#define PWMINTEN (0x014)
#define PWMRIS (0x018)
#define PWMISC (0x01C)
#define PWMSTATUS (0x020)
#define PWMFAULTVAL (0x024)
#define PWMENUPD (0x028)

#define PWM0CTL (0x040)
#define PWM1CTL (0x080)
#define PWM2CTL (0x0C0)
#define PWM3CTL (0x100)

#define PWM0INTEN (0x044)
#define PWM1INTEN (0x084)
#define PWM2INTEN (0x0C4)
#define PWM3INTEN (0x104)

#define PWM0RIS (0x048)
#define PWM1RIS (0x088)
#define PWM2RIS (0x0C8)
#define PWM3RIS (0x108)

#define PWM0ISC (0x04C)
#define PWM1ISC (0x08C)
#define PWM2ISC (0x0CC)
#define PWM3ISC (0x10C)

#define PWM0LOAD (0x050)
#define PWM1LOAD (0x090)
#define PWM2LOAD (0x0D0)
#define PWM3LOAD (0x110)


#define PWM0COUNT (0x054)
#define PWM1COUNT (0x094)
#define PWM2COUNT (0x0D4)
#define PWM3COUNT (0x114)

#define PWM0CMPA (0x058)
#define PWM1CMPA (0x098)
#define PWM2CMPA (0x0D8)
#define PWM3CMPA (0x118)

#define PWM0CMPB (0x05C)
#define PWM1CMPB (0x09C)
#define PWM2CMPB (0x0DC)
#define PWM3CMPB (0x11C)

#define PWM0GENA (0x060)
#define PWM1GENA (0x0A0)
#define PWM2GENA (0x0E0)
#define PWM3GENA (0x120)



#define PWM0GENB (0x064)
#define PWM1GENB (0x0A4)
#define PWM2GENB (0x0E4)
#define PWM3GENB (0x124)
/********I2C*****/

#define I2CMSA (0x000)
#define I2CMCS (0x004) //check flages and congf the frame
#define I2CMDR (0x008)
#define I2CMTPR (0x00C)
#define I2CMIMR (0x010)
#define I2CMRIS (0x014)
#define I2CMMIS (0x018)
#define I2CMICR (0x01C)
#define I2CMCR (0x020)
#define I2CMCLKOCNT (0x024)
#define I2CMBMON (0x02C)
#define I2CMCR2 (0x038)

#define I2CSOAR (0x800)
#define I2CSCSR (0x804)
#define I2CSDR (0x808)
#define I2CSIMR (0x80C)
#define I2CSRIS (0x810)
#define I2CSMIS (0x814)
#define I2CSICR (0x818)
#define I2CSOAR2 (0x81C)
#define I2CSACKCTL (0x820)

#define I2CPP (0xFC0)
#define I2CPC (0xFC4)



//*****CLOCK**/
#define RCC (*((volatile unsigned long *)(0x400FE060)))  //CONFIGURE CLOCK OF THE CONTROLLER
//*******ENABLE CLOCK *********//
#define RCGCGPIO (*((volatile unsigned long *)(0x400FE608)))     //Enable Clock
#define RCGCUART (*((volatile unsigned long *)(0x400FE618)))     //Enable Clock
#define RCGCTIMER (*((volatile unsigned long*)(0x400FE604)))  //16/32 BIT TIMER ENABLE
#define RCGCWTIMER (*((volatile unsigned long*)(0x400FE65C)))  //32/64 BIT TIMER ENABLE
#define RCGCADC (*((volatile unsigned long*)(0x400FE638)))  //ENABLE ADC CLOCK
#define RCGCPWM (*((volatile unsigned long*)(0x400FE640)))  //enable pwm clock
#define RCGCI2C (*((volatile unsigned long*)(0x400FE620)))  //enable I2C clock
#define RCGC2 (*((volatile unsigned long*)(0x400FE108)))



//*******PORTA
//
//#define GPIODIR_A (*((volatile unsigned long *)(0x40004400)))    //DIRECTION
//#define GPIOAFSEL_A (*((volatile unsigned long *)(0x40004420)))  // ALTERNATE OR GBIO
//#define GPIOSLR_A (*((volatile unsigned long *)(0x40004518)))  // SLEW RATE
//#define GPIODEN_A (*((volatile unsigned long *)(0x4000451C)))   //DIGITAL ENABLE
//#define GPIOLOCK_A (*((volatile unsigned long *)(0x40004520)))   //UNLOCK
//#define GPIODATA_A (*((volatile unsigned long *)(0x400043FC)))   //DATA
//#define GPIOCR_A (*((volatile unsigned long *)(0x40004524)))      // GBIO COMMIT
//
//#define GPIOAMSEL_A (*((volatile unsigned long *)(0x40004528)))      // ADC ISOLATION
//#define GPIOPCTL_A (*((volatile unsigned long *)(0x4000452C)))      //SPECIAL PINS
//
//#define GPIODR2R_A (*((volatile unsigned long *)(0x40004500)))      //DRIVEN 2mA
//#define GPIODR4R_A (*((volatile unsigned long *)(0x40004504)))      //DRIVEN 4mA
//#define GPIODR8R_A (*((volatile unsigned long *)(0x40004508)))  // DRIVEN 8mA
//
//#define GPIOPUR_A (*((volatile unsigned long *)(0x40004510)))      // PULL UP
//#define GPIOPDR_A (*((volatile unsigned long *)(0x40004514)))      // PULL DOWN
//#define GPIOODR_A (*((volatile unsigned long *)(0x4000450C)))      // OPEN DRAIN

//*******PORTB

//#define GPIODIR_B (*((volatile unsigned long *)(0x40005400)))    //DIRECTION
//#define GPIOAFSEL_B (*((volatile unsigned long *)(0x40005420)))  // ALTERNATE OR GBIO
//#define GPIOSLR_B (*((volatile unsigned long *)(0x40005518)))  // SLEW RATE
//#define GPIODEN_B (*((volatile unsigned long *)(0x4000551C)))   //DIGITAL ENABLE
//#define GPIOLOCK_B (*((volatile unsigned long *)(0x40005520)))   //UNLOCK
//#define GPIODATA_B (*((volatile unsigned long *)(0x400053FC)))   //DATA
//#define GPIOCR_B (*((volatile unsigned long *)(0x40005524)))      // GBIO COMMIT
//
//#define GPIOAMSEL_B (*((volatile unsigned long *)(0x40005528)))      // ADC ISOLATION
//#define GPIOPCTL_B (*((volatile unsigned long *)(0x4000552C)))      //SPECIAL PINS
//
//#define GPIODR2R_B (*((volatile unsigned long *)(0x40005500)))      //DRIVEN 2mA
//#define GPIODR4R_B (*((volatile unsigned long *)(0x40005504)))      //DRIVEN 4mA
//#define GPIODR8R_B (*((volatile unsigned long *)(0x40005508)))  // DRIVEN 8mA
//
//
//#define GPIOPUR_B (*((volatile unsigned long *)(0x40005510)))      // PULL UP
//#define GPIOPDR_B (*((volatile unsigned long *)(0x40005514)))      // PULL DOWN
//#define GPIOODR_B (*((volatile unsigned long *)(0x4000550C)))      // OPEN DRAIN

//*******PORTC
//#define GPIODIR_C (*((volatile unsigned long *)( 0x40006400)))    //DIRECTION
//#define GPIOAFSEL_C (*((volatile unsigned long *)(0x40006420)))  // ALTERNATE OR GBIO
//#define GPIOSLR_C (*((volatile unsigned long *)(0x40006518)))  // SLEW RATE
//#define GPIODEN_C (*((volatile unsigned long *)(0x4000651C)))   //DIGITAL ENABLE
//#define GPIOLOCK_C (*((volatile unsigned long *)(0x40006520)))   //UNLOCK
//#define GPIODATA_C (*((volatile unsigned long *)(0x400063FC)))   //DATA
//#define GPIOCR_C (*((volatile unsigned long *)(0x40006524)))      // GBIO COMMIT
//
//#define GPIOAMSEL_C (*((volatile unsigned long *)(0x40006528)))      // ADC ISOLATION
//#define GPIOPCTL_C (*((volatile unsigned long *)(0x4000652C)))      //SPECIAL PINS
//
//#define GPIODR2R_C (*((volatile unsigned long *)(0x40006500)))      //DRIVEN 2mA
//#define GPIODR4R_C (*((volatile unsigned long *)(0x40006504)))      //DRIVEN 4mA
//#define GPIODR8R_C (*((volatile unsigned long *)(0x40006508)))  // DRIVEN 8mA
//
//
//#define GPIOPUR_C (*((volatile unsigned long *)(0x40006510)))      // PULL UP
//#define GPIOPDR_C (*((volatile unsigned long *)(0x40006514)))      // PULL DOWN
//#define GPIOODR_C (*((volatile unsigned long *)(0x4000650C)))      // OPEN DRAIN


//*******PORTD
//#define GPIODIR_D (*((volatile unsigned long *)(0x40007400)))
//#define GPIOAFSEL_D (*((volatile unsigned long *)(0x40007420)))  // ALTERNATE OR GBIO
//#define GPIOSLR_D (*((volatile unsigned long *)(0x40007518)))  // SLEW RATE
//#define GPIODEN_D (*((volatile unsigned long *)(0x4000751C)))   //DIGITAL ENABLE
//#define GPIOLOCK_D (*((volatile unsigned long *)(0x40007520)))   //UNLOCK
//#define GPIODATA_D (*((volatile unsigned long *)(0x400073FC)))   //DATA
//#define GPIOCR_D (*((volatile unsigned long *)(0x40007524)))      // GBIO COMMIT
//#define GPIOODR_D (*((volatile unsigned long *)(0x4000750C)))      // OPEN DRAIN
//#define GPIOAMSEL_D (*((volatile unsigned long *)(0x40007528)))      // ADC ISOLATION
//#define GPIOPCTL_D (*((volatile unsigned long *)(0x4000752C)))      //SPECIAL PINS
//
//#define GPIODR2R_D (*((volatile unsigned long *)(0x40007500)))      //DRIVEN 2mA
//#define GPIODR4R_D (*((volatile unsigned long *)(0x40007504)))      //DRIVEN 4mA
//#define GPIODR8R_D (*((volatile unsigned long *)(0x40007508)))  // DRIVEN 8mA
//
//#define GPIOPUR_D (*((volatile unsigned long *)(0x40007510)))      // PULL UP
//#define GPIOPDR_D (*((volatile unsigned long *)(0x40007514)))      // PULL DOWN
//#define GPIOODR_D (*((volatile unsigned long *)(0x4000750C)))      // OPEN DRAIN


//*******PORTE
//#define GPIODIR_E (*((volatile unsigned long *)(0x40024400)))
//#define GPIOAFSEL_E (*((volatile unsigned long *)(0x40024420)))  // ALTERNATE OR GBIO
//#define GPIOSLR_E (*((volatile unsigned long *)(0x40024518)))  // SLEW RATE
//#define GPIODEN_E (*((volatile unsigned long *)(0x4002451C)))   //DIGITAL ENABLE
//#define GPIOLOCK_E (*((volatile unsigned long *)(0x40024520)))   //UNLOCK
//#define GPIODATA_E (*((volatile unsigned long *)(0x400243FC)))   //DATA
//#define GPIOCR_E (*((volatile unsigned long *)(0x40024524)))      // GBIO COMMIT
//
//#define GPIOAMSEL_E (*((volatile unsigned long *)(0x40024528)))      // ADC ISOLATION
//#define GPIOPCTL_E (*((volatile unsigned long *)(0x4002452C)))      //SPECIAL PINS
//
//#define GPIODR2R_E (*((volatile unsigned long *)(0x40024500)))      //DRIVEN 2mA
//#define GPIODR4R_E (*((volatile unsigned long *)(0x40024504)))      //DRIVEN 4mA
//#define GPIODR8R_E (*((volatile unsigned long *)(0x40024508)))  // DRIVEN 8mA
//
//
//
//#define GPIOPUR_E (*((volatile unsigned long *)(0x40024510)))      // PULL UP
//#define GPIOPDR_E (*((volatile unsigned long *)(0x40024514)))      // PULL DOWN
//#define GPIOODR_E (*((volatile unsigned long *)(0x4002450C)))      // OPEN DRAIN
//
//*******PORTF
//#define GPIODIR_F (*((volatile unsigned long *)(0x40025400)))
//#define GPIOAFSEL_F (*((volatile unsigned long *)(0x40025420)))  // ALTERNATE OR GBIO
//#define GPIODR8R_F (*((volatile unsigned long *)(0x40025508)))  // MAX CURRENT OUT
//#define GPIOSLR_F (*((volatile unsigned long *)(0x40025518)))  // SLEW RATE
//#define GPIODEN_F (*((volatile unsigned long *)(0x4002551C)))   //DIGITAL ENABLE
//#define GPIOLOCK_F (*((volatile unsigned long *)(0x40025520)))   //UNLOCK
//#define GPIODATA_F (*((volatile unsigned long *)(0x400253FC)))   //DATA
//#define GPIOCR_F (*((volatile unsigned long *)(0x40025524)))      // GBIO COMMIT
//#define GPIOODR_F (*((volatile unsigned long *)(0x4002550C)))      // OPEN DRAIN
//#define GPIOAMSEL_F (*((volatile unsigned long *)(0x40025528)))      // ADC ISOLATION
//#define GPIOPCTL_F (*((volatile unsigned long *)(0x4002552C)))      //SPECIAL PINS
//
//#define GPIODR2R_F (*((volatile unsigned long *)(0x40025500)))      //DRIVEN 2mA
//#define GPIODR4R_F (*((volatile unsigned long *)(0x40025504)))      //DRIVEN 4mA
//#define GPIODR8R_F (*((volatile unsigned long *)(0x40025508)))  // DRIVEN 8mA
//
//
//#define GPIOPUR_F (*((volatile unsigned long *)(0x40025510)))      // PULL UP
//#define GPIOPDR_F (*((volatile unsigned long *)(0x40025514)))      // PULL DOWN
//#define GPIOODR_F (*((volatile unsigned long *)(0x4002550C)))      // OPEN DRAIN





/*******TIMER*************/
//#define GPTMTBMR0 (*((volatile unsigned long*)(0x40030008)))
//#define GPTMTBILR0 (*((volatile unsigned long*)(0x4003002C)))
//
//#define GPTMTAMR0 (*((volatile unsigned long*)(0x40030004)))
//#define ADCACTSS (*((volatile unsigned long*)(0x40038000)))
#define ADC1_ADCACTSS (*((volatile unsigned long*)0x40039000))


//0x4003800




#endif /* REGISTERS_H_ */
