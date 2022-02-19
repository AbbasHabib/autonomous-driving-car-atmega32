#include"UTIL/STD_TYPES.h"
#include"MCAL/PORT_interface.h"
#include"MCAL/DIO_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/TIMER/TIMER_reg.h"
#include "UTIL/BIT_MATH.h"
#include "MCAL/PWM/PWM_interface.h"
#include <util/delay.h>



int main(){
	PORT_voidInit(); //  here we will set PB3 as output (OC0)
	PWM0_VoidInit();
	uint8 dutyCycle = 50;
	PWM0_VoidSetDutyCycle(dutyCycle);


	while(1){
		PWM0_VoidSetDutyCycle(100);

		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN1, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_HIGH);

		_delay_ms(500);

		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN1, DIO_u8_PIN_HIGH);

		_delay_ms(500);

		PWM0_VoidSetDutyCycle(70);

		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN1, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_HIGH);

		_delay_ms(500);

		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN1, DIO_u8_PIN_HIGH);

		_delay_ms(500);

	}

	return 0;
}
