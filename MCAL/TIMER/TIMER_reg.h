#ifndef TIMER_REG_H_
#define TIMER_REG_H_


#define TCCR0		 *((volatile uint8*)0x53)

#define TCCR0_CS00		0
#define TCCR0_CS01		1
#define TCCR0_CS02		2
#define TCCR0_WGM01		3
#define TCCR0_COM00		4
#define TCCR0_COM01		5
#define TCCR0_WGM00		6
#define TCCR0_FOC0		7


#define TCNT0		 *((volatile uint8*)0x52)

#define OCR0		 *((volatile uint8*)0x5c)

#define TIMSK		 *((volatile uint8*)0x59)


#define TIMSK_TOIE0		0
#define TIMSK_OCIE0		1



#endif
