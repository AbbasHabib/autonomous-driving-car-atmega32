#include"UTIL/STD_TYPES.h"
#include"MCAL/PORT_interface.h"
#include"MCAL/DIO_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/TIMER/TIMER_reg.h"
#include "UTIL/BIT_MATH.h"
#include "MCAL/PWM/PWM_interface.h"
#include <util/delay.h>
#include "MCAL/INTERRUPT/GIE_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "HAL/USS/USS_interface.h"
#include "HAL/SERVO/SERVO_interface.h"
#include "HAL/MOTOR/MOTOR_interface.h"



uint8 u8MoveServo180Degrees(){
	static uint8 Local_u8CurrentAngle = 0;
	static uint8 Local_u8IncFlag = 1;
	uint8 Local_u8Direction = ' ';
	if(Local_u8IncFlag)
		Local_u8CurrentAngle += 50;
	else
		Local_u8CurrentAngle -= 50;

	switch(Local_u8CurrentAngle){
	case 0:
		Local_u8Direction = 'L';
		break;
	case 50:
		Local_u8Direction = 'C';
		break;
	case 100:
		Local_u8Direction = 'R';
		break;
	default:
		Local_u8Direction = ' ';
		break;
	}

	SERVO_voidRotateToAngle(Local_u8CurrentAngle);
	if(Local_u8CurrentAngle <= 1 || Local_u8CurrentAngle >= 100)
		Local_u8IncFlag = !Local_u8IncFlag;
	else{
		/* nothing */
	}
	return Local_u8Direction;
}


//uint8 u8CheckObstacle_MoveAccordingly(uint8 Copy_USSDistance){
//
//}


int main(){
	PORT_voidInit();
	CLCD_voidInit();
	USS_voidInit();
	while(1){
		uint8 Local_u8Direction = MoveServo180Degrees();
		uint32 Local_u32distance = USS_u32GetDistance();
		CLCD_sendString("distance: ");
		CLCD_sendNumebr((uint32)Local_u32distance);
		_delay_ms(500);
		CLCD_voidClearDisplay();
	}
	return 0;
}
