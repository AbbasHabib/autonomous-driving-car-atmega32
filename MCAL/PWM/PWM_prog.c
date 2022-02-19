#include"../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../TIMER/TIMER_reg.h"




void PWM0_VoidInit(void){
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

