#ifndef DIO_REG_H_
#define DIO_REG_H_

#define PORTA *((volatile uint8*)0x3B)
#define PINA  *((volatile uint8*)0x39)

#define PORTB *((volatile uint8*)0x38)
#define PINB  *((volatile uint8*)0x36)

#define PORTC *((volatile uint8*)0x35)
#define PINC  *((volatile uint8*)0x33)

#define PORTD *((volatile uint8*)0x32)
#define PIND  *((volatile uint8*)0x30)

#endif
