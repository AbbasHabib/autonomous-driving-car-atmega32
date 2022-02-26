#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


// every instance would take 16 bits = 2 bytes
struct Motor{
	uint8 motor_u8_port 		: 4;
	uint8 motor_u8_pin1 		: 4;
	uint8 motor_u8_pin2 		: 4;
	uint8 motor_u8_enablePin 	: 4;
};


#define MOTOR_u8_CLOCKWISE			0
#define MOTOR_u8_ANTICLOCKWISE		1

void MOTOR_voidSetMotorPWMDutyCycle(struct Motor Copy_Motor, uint8 Copy_u8DutyCycle)

void MOTOR_voidMoveMotor(struct Motor Copy_Motor , uint8 Copy_u8Dirction);

void MOTOR_voidStopMotor(struct Motor Copy_Motor);


#endif
