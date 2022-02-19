#include "../UTIL/STD_TYPES.h"
#include "../UTIL/BIT_MATH.h"
#include "../UTIL/ERR_TYPE.h"

#include "DIO_interface.h"
#include "DIO_reg.h"
uint8 DIO_u8SetPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum,uint8 Copy_u8Val)
{
	uint8 Local_u8ErrorState = OK;
	if((Copy_u8PinNum <= DIO_u8_PIN7)&& (Copy_u8Val <= DIO_u8_PIN_HIGH)){
		switch(Copy_u8Port)
		{
			case DIO_u8_PORTA : ASSIGN_BIT(PORTA,Copy_u8PinNum,Copy_u8Val); break;
			case DIO_u8_PORTB : ASSIGN_BIT(PORTB,Copy_u8PinNum,Copy_u8Val); break;
			case DIO_u8_PORTC : ASSIGN_BIT(PORTC,Copy_u8PinNum,Copy_u8Val); break;
			case DIO_u8_PORTD : ASSIGN_BIT(PORTD,Copy_u8PinNum,Copy_u8Val); break;
			default : Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8 DIO_u8SetPortValue(uint8 Copy_u8Port,uint8 Copy_u8Val)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8Port)
	{
		case DIO_u8_PORTA : PORTA = Copy_u8Val; break;
		case DIO_u8_PORTB : PORTB = Copy_u8Val; break;
 		case DIO_u8_PORTC : PORTC = Copy_u8Val; break;
		case DIO_u8_PORTD : PORTD = Copy_u8Val; break;
		default : Local_u8ErrorState = NOK; break;
	}
	return Local_u8ErrorState;
}

uint8 DIO_u8ReadPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum,uint8* Copy_pu8Val)
{
	uint8 Local_u8ErrorState = OK;
	if((Copy_u8PinNum <= DIO_u8_PIN7) && (Copy_pu8Val != NULL)){
		switch(Copy_u8Port)
		{
			case DIO_u8_PORTA : *Copy_pu8Val = GET_BIT(PINA,Copy_u8PinNum); break;
			case DIO_u8_PORTB : *Copy_pu8Val = GET_BIT(PINB,Copy_u8PinNum); break;
			case DIO_u8_PORTC : *Copy_pu8Val = GET_BIT(PINC,Copy_u8PinNum); break;
			case DIO_u8_PORTD : *Copy_pu8Val = GET_BIT(PIND,Copy_u8PinNum); break;
			default : Local_u8ErrorState = NOK; break;
		}
	}
	else if(Copy_pu8Val == NULL)
	{
		Local_u8ErrorState  = NULL_POINTER;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8 DIO_u8TogglePinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNum)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8PinNum <= DIO_u8_PIN7){
		switch(Copy_u8Port)
		{
			case DIO_u8_PORTA : TOG_BIT(PORTA,Copy_u8PinNum); break;
			case DIO_u8_PORTB : TOG_BIT(PORTB,Copy_u8PinNum); break;
			case DIO_u8_PORTC : TOG_BIT(PORTC,Copy_u8PinNum); break;
			case DIO_u8_PORTD : TOG_BIT(PORTD,Copy_u8PinNum); break;
			default : Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
//<------------------------------------------------------>



