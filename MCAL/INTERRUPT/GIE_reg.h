#ifndef	GIE_REG_H_
#define GIE_REG_H_

#define SREG 		*((volatile uint8*) 0x5F) /*Status Register*/
#define SREG_I 		7						  /*Interrupt bit*/
#endif
