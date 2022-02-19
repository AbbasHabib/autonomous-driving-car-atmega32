#ifndef	EXIT_REG_H_
#define EXIT_REG_H_

#define MCUCR 			*((volatile uint8*) 0x55)	/*MCU control register*/
#define MCUCR_ISC11		3							/*Int1 Sense control bit 1*/
#define MCUCR_ISC10		2							/*Int1 Sense control bit 0*/
#define MCUCR_ISC01		1							/*Int0 Sense control bit 1*/
#define MCUCR_ISC00		0							/*Int0 Sense control bit 0*/

#define MCUCSR 			*((volatile uint8*) 0x54)	/*MCU control and status register*/
#define MCUCSR_ISC2		6

#define GICR 			*((volatile uint8*) 0x5B)
#define GICR_INT1		7
#define GICR_INT0		6
#define GICR_INT2		5

#endif

