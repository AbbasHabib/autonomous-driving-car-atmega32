#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/ERR_TYPE.h"
#include "../../MCAL/DIO_interface.h"
#include <util/delay.h>
#include "../../MCAL/PWM/PWM_interface.h"
#include "MOTOR_interface.h"



uint8 MOTOR_u8MoveMotor(struct Motor Copy_Motor , uint8 Copy_u8Dirction){
	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8Dirction){
	case MOTOR_u8_CLOCKWISE:
		DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin1, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin2, DIO_u8_PIN_HIGH);
		break;
	case MOTOR_u8_ANTICLOCKWISE:
		DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin2, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin1, DIO_u8_PIN_HIGH);
		break;
	default:
		Local_u8ErrorState = NOK;
		break;
	}
	return Local_u8ErrorState;
}

/* this function stops pin1 and pin2 of the motor does not affect PWM*/
void MOTOR_voidStopMotor(struct Motor Copy_Motor){
	DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin1, DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(Copy_Motor.motor_u8_port, Copy_Motor.motor_u8_pin2, DIO_u8_PIN_LOW);
}


/* PWM pin at OC0 (PWM0) */
void MOTOR_voidSetMotorsPWMDutyCycle(uint8 Copy_u8DutyCycle){
	PWM0_VoidSetDutyCycle(Copy_u8DutyCycle);
	return;
}
