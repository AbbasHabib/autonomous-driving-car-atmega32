#include"../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../TIMER/TIMER_reg.h"
#include "PWM_interface.h"



void PWM0_VoidInit(void){
	// OC0
	// fast PWM mode
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
	// inverted PWM mode
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
	// no prescale
		SET_BIT(TCCR0,TCCR0_CS00);
}


void PWM0_VoidSetDutyCycle(uint8 Copy_u8DutyCycle){
	// on time
	OCR0 = 255 - ((float32)Copy_u8DutyCycle / 100.0f) * 255.0f;
}


void PWM1_VoidInit(void){
	// OC1A

		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);
	// inverted PWM mode
		SET_BIT(TCCR1B, TCCR1B_WGM12);
		SET_BIT(TCCR1B, TCCR1B_WGM13);
	// no prescale
		SET_BIT(TCCR1B, TCCR1B_CS10);
}

void PWM0_VoidSetDutyCycle(uint8 Copy_u8DutyCycle){
	// on time
	uint16 dutyCycle = 65536 - ((float32)Copy_u8DutyCycle / 100.0f) * 65536.0f;
	OCR1AL = dutyCycle & 0xff;
	OCR1AH = (dutyCycle >> 8) & 0xff;
}

