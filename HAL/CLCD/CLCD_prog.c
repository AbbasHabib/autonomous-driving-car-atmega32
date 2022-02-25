#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/ERR_TYPE.h"
#include <util/delay.h>
#include "../../MCAL/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"


#if CLCD_u8_MODE == FOUR_BIT
static void SetDataPins(uint8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN4,GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN5,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN6,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN7,GET_BIT(Copy_u8Data,3));
}
#endif

static void SendEnablePulse(void){
	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_E_PIN,DIO_u8_PIN_LOW);
}

void CLCD_voidSendCommand(uint8 Copy_u8Command)
{
	/*Set Rs pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RS_PIN,DIO_u8_PIN_LOW);

	/*set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RW_PIN,DIO_u8_PIN_LOW);

#if CLCD_u8_MODE == EIGHT_BIT
	/*send the command*/
	DIO_u8SetPortValue(CLCD_u8_DATA_PORT,Copy_u8Command);

	SendEnablePulse();
#elif CLCD_u8_MODE == FOUR_BIT
	SetDataPins(Copy_u8Command >> 4);
	SendEnablePulse();
	SetDataPins(Copy_u8Command);
	SendEnablePulse();
#endif
}

void CLCD_voidSendData(uint8 Copy_u8Data){
	/*Set Rs pin to high for Data*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RS_PIN,DIO_u8_PIN_HIGH);

	/*set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RW_PIN,DIO_u8_PIN_LOW);

#if CLCD_u8_MODE == EIGHT_BIT
	/*send the command*/
	DIO_u8SetPortValue(CLCD_u8_DATA_PORT,Copy_u8Data);
	SendEnablePulse();
#elif CLCD_u8_MODE == FOUR_BIT
	SetDataPins(Copy_u8Data >> 4);
	SendEnablePulse();
	SetDataPins(Copy_u8Data);
	SendEnablePulse();
#endif

}

void CLCD_voidInit(void){
	/*delay for more than 30ms*/
	_delay_ms(40);
#if CLCD_u8_MODE == EIGHT_BIT
	/*Function set command : 2 lines , font size : 5*7*/
	CLCD_voidSendCommand(0b00111000);
#elif CLCD_u8_MODE == FOUR_BIT
	SetDataPins(0b0010);
	SendEnablePulse();
	SetDataPins(0b0010);
	SendEnablePulse();
	SetDataPins(0b1000);
	SendEnablePulse();
#endif
	/*Function set command :  display on , cursor off , blink cursor off*/
	CLCD_voidSendCommand(0b00001100);
	/*Clear LCD*/
	CLCD_voidSendCommand(1);
}

uint8 CLCD_sendString(char Copy_u8StringArray[]){
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8StringArray == NULL){
		Local_u8ErrorState = NULL_POINTER;
	}
	else{
		for(int i = 0 ; Copy_u8StringArray[i] != '\0' ; i++){
			CLCD_voidSendData(Copy_u8StringArray[i]);
		}
	}

	return Local_u8ErrorState;
}

uint8 CLCD_sendNumebr(uint32 Copy_u8Number){

	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Number == 0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		uint32 Local_u8Inverter = 0;

		//this is iterator to solve problem of 12500 (zero)
		uint8 Local_u8Iterator = 0;

		while(Copy_u8Number != 0)
		{
			Local_u8Inverter *= 10;
			Local_u8Inverter += (Copy_u8Number % 10);
			Copy_u8Number /= 10;
			Local_u8Iterator++;
		}
		for(;Local_u8Iterator > 0 ; Local_u8Iterator--)
		{
			CLCD_voidSendData((Local_u8Inverter % 10) + '0');
			Local_u8Inverter /= 10;
		}
	}

	return Local_u8ErrorState;
}

void CLCD_voidGoToXY(uint8 Copy_u8XPos , uint8 Copy_YPos){
	uint8 Local_u8Add;
	if(Copy_YPos == 0)
		Local_u8Add = Copy_u8XPos;
	else if(Copy_YPos == 1)
		Local_u8Add = Copy_u8XPos + 0x40;

	/*Set bit number 7 for Set DDRAM Address*/
	SET_BIT(Local_u8Add,7);

	/*set DDRAM address for command*/
	CLCD_voidSendCommand(Local_u8Add);
}

uint8 CLCD_voidSendSpecialChatacter(uint8* Copy_u8Pattern,uint8 Copy_u8PatternNum,uint8 Copy_u8XPos, uint8 Copy_u8YPos){
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Pattern != NULL)
	{
		uint8 Local_u8Counter;
		uint8 Local_u8Add = Copy_u8PatternNum * 8;
		SET_BIT(Local_u8Add,6); //set bit number 6 for set CGRAM address Command

		CLCD_voidSendCommand(Local_u8Add); // Set CGRAM address command
		/*Draw the pattern inside CGRAM*/
		for(Local_u8Counter = 0; Local_u8Counter < 8 ; Local_u8Counter++){
			CLCD_voidSendData(Copy_u8Pattern[Local_u8Counter]);
		}

		/*Go back to DDRAM*/
		CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

		/*Display the drawn pattern*/
		CLCD_voidSendData(Copy_u8PatternNum);
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}

void CLCD_voidClearDisplay()
{
	CLCD_voidSendCommand(0b00000001);
}
