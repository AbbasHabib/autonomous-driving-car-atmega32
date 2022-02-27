#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


// every instance would take 16 bits = 2 bytes
struct Motor{
	uint8 motor_u8_port 		: 4;
	uint8 motor_u8_pin1 		: 4;
	uint8 motor_u8_pin2 		: 4;
};


#define MOTOR_u8_CLOCKWISE			0
#define MOTOR_u8_ANTICLOCKWISE		1
/* set motor Dirction CW or ACW*/
uint8 MOTOR_u8MoveMotor(struct Motor Copy_Motor , uint8 Copy_u8Dirction);
/* this function stops pin1 and pin2 of the motor does not affect PWM*/
void MOTOR_voidStopMotor(struct Motor Copy_Motor);
/* control motor speed from PWM pin at OC0 (PWM0) */
void MOTOR_voidSetMotorsPWMDutyCycle(uint8 Copy_u8DutyCycle);


#endif
