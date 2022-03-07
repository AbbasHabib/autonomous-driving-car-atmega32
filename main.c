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


#define CRITICAL_u8_DISTANCE 		80
#define CAR_u16_OBSTCALE_SKIP_TIME 	1000
#define SERVO_u8_DELAY				200

struct Motor MOTOR1, MOTOR2;

uint8 MoveServo180Degrees();
void voidInitMotors();
void voidCheckObstacle_MoveAccordingly(uint32 Copy_32USSDistance, uint8 Copy_u8Dirction);


uint8 MoveServo180Degrees(){
	/* This function moves the servo 0 to 90 to 180 and back
	 * based on the last angle stored in Local_u8CurrentAngle static variable  */
	static uint8 Local_u8CurrentAngle = 0;
	/* inc_flag is used ro rotate the servo on the
	 * specified angles Clock wise or anti clock wise */
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
	/* rotate servo according to changes */
	SERVO_voidRotateToAngle(Local_u8CurrentAngle);
	if(Local_u8CurrentAngle <= 1 || Local_u8CurrentAngle >= 100)
		Local_u8IncFlag = !Local_u8IncFlag;
	else{
		/* nothing */
	}
	_delay_ms(SERVO_u8_DELAY);
	return Local_u8Direction;
}


void voidInitMotors(){
	/* sets port and pin numbers of the connected motors */
	MOTOR1.motor_u8_port = DIO_u8_PORTB;
	MOTOR1.motor_u8_pin1 = DIO_u8_PIN4;
	MOTOR1.motor_u8_pin2 = DIO_u8_PIN5;

	MOTOR2.motor_u8_port = DIO_u8_PORTB;
	MOTOR2.motor_u8_pin1 = DIO_u8_PIN6;
	MOTOR2.motor_u8_pin2 = DIO_u8_PIN7;
}



void voidCheckObstacle_MoveAccordingly(uint32 Copy_32USSDistance, uint8 Copy_u8Dirction){
	/* 	check if ultrasonic measured distance (Copy_32USSDistance) lower than the critical value
	 *	if true then move according to the direction of Servo motor (Copy_u8Dirction)
	 */
	if(Copy_32USSDistance <= CRITICAL_u8_DISTANCE){
		MOTOR_voidSetMotorsPWMDutyCycle(100);
		switch(Copy_u8Dirction){
		case 'L':
			MOTOR_u8MoveMotor(MOTOR1, MOTOR_u8_ANTICLOCKWISE);
			MOTOR_voidStopMotor(MOTOR2);
			_delay_ms(CAR_u16_OBSTCALE_SKIP_TIME);
			break;
		case 'R':
			MOTOR_u8MoveMotor(MOTOR2, MOTOR_u8_ANTICLOCKWISE);
			MOTOR_voidStopMotor(MOTOR1);
			_delay_ms(CAR_u16_OBSTCALE_SKIP_TIME);
			break;
		case 'C':
			MOTOR_u8MoveMotor(MOTOR1, MOTOR_u8_ANTICLOCKWISE);
			MOTOR_u8MoveMotor(MOTOR2, MOTOR_u8_CLOCKWISE);
			_delay_ms(CAR_u16_OBSTCALE_SKIP_TIME);
		}
	}
	else{
		/* set speed of the motor by chaning dutycycle */
		MOTOR_voidSetMotorsPWMDutyCycle(100);
		MOTOR_u8MoveMotor(MOTOR1, MOTOR_u8_CLOCKWISE);
		MOTOR_u8MoveMotor(MOTOR2, MOTOR_u8_CLOCKWISE);
	}

}

char* charptrCarDirection(uint32 Copy_32USSDistance, uint8 Copy_u8Dirction){
	/* this function returns a string of 3 letters descriping the current
	 * direction the car is taking
	 */
	static char Local_carDir[3] = "F \0";
	Local_carDir[0] = 'F';
	Local_carDir[1] = ' ';
	if(Copy_32USSDistance <= CRITICAL_u8_DISTANCE){
		switch(Copy_u8Dirction){
		case 'L':
			/* Backward - Right */
			Local_carDir[0] = 'B';
			Local_carDir[1] = 'R';
			break;
		case 'R':
			/* Backward - Left */
			Local_carDir[0] = 'B';
			Local_carDir[1] = 'L';
			break;
		case 'C':
			/* rotate arount it self */
			Local_carDir[0] = 'R';
			Local_carDir[1] = 'R';
			break;
		}
	}
	Local_carDir[2] = '\0';
	return Local_carDir;
}

int main(){
	/* Init directions and initial values configured in PORT_config.h file */
	PORT_voidInit();
	/* Init CLCD 8bit mode */
	CLCD_voidInit();
	/* init ultra sonic sensor
	 *  - enables Global interrupt
	 *  - enables overflow interrupt for timer 1
	 *  - start count
	 */
	USS_voidInit();
	/*  init PWM of timer0 fast PWM, inverted */
	PWM0_VoidInit();
	/*  Call Motor init function in main file */
	voidInitMotors();
	while(1){
		/* Moves the servo 0 to 90 to 180 and back */
		uint8 Local_u8ServoDirection = MoveServo180Degrees();
		/* get distance in cm from ultra sonic sensor */
		uint32 Local_u32distance = USS_u32GetDistance();
		CLCD_sendString("distance:");
		/* print distance of ultrasonic to CLCD */
		CLCD_sendNumebr((uint32)Local_u32distance);
		/* Newline */
		CLCD_voidGoToXY(0, 1);
		CLCD_sendString("srvo:");
		/* print current servo direction on CLCD */
		CLCD_voidSendData(Local_u8ServoDirection);
		CLCD_sendString(" dir:");
		char* Local_charptrCarDir = charptrCarDirection
				(Local_u32distance, Local_u8ServoDirection);
		/* print current car direction to CLCD */
		CLCD_sendString(Local_charptrCarDir);
		voidCheckObstacle_MoveAccordingly(Local_u32distance, Local_u8ServoDirection);
		_delay_ms(500);
		/* clear CLCD */
		CLCD_voidClearDisplay();
	}
	return 0;
}
