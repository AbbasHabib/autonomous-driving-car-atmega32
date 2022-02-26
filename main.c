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

uint16 volatile time_overflow = 0;

void MoveServo(){
	static uint8 Local_currentAngle = 0;
	static uint8 Local_incFlag = 1;
	if(Local_incFlag)
		Local_currentAngle += 50;
	else
		Local_currentAngle -= 50;
	SERVO_voidRotateToAngle(Local_currentAngle);
	if(Local_currentAngle <= 1 || Local_currentAngle >= 100)
		Local_incFlag = !Local_incFlag;
}


int main(){
	PORT_voidInit();
	CLCD_voidInit();
	USS_voidInit();
	while(1){
		MoveServo();
		uint32 distance = USS_u32GetDistance();
		CLCD_sendString("distance: ");
		CLCD_sendNumebr((uint32)distance);
		_delay_ms(500);
		CLCD_voidClearDisplay();
	}

	return 0;
}
