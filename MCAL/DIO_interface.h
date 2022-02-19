#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*PORTS*/
#define DIO_u8_PORTA	0
#define DIO_u8_PORTB	1
#define DIO_u8_PORTC	2
#define DIO_u8_PORTD	3

/*PINS*/
#define DIO_u8_PIN0		0
#define DIO_u8_PIN1		1
#define DIO_u8_PIN2		2
#define DIO_u8_PIN3		3
#define DIO_u8_PIN4		4
#define DIO_u8_PIN5		5
#define DIO_u8_PIN6		6
#define DIO_u8_PIN7		7

/*PIN STATUS*/
#define DIO_u8_PIN_HIGH  1
#define DIO_u8_PIN_LOW   0


uint8 DIO_u8SetPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum,uint8 Copy_u8Val);
uint8 DIO_u8SetPortValue(uint8 Copy_u8Port,uint8 Copy_u8Val);

uint8 DIO_u8ReadPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum,uint8* Copy_pu8Value);

uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum);


#endif
