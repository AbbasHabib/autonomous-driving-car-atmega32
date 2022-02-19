#include"UTIL/STD_TYPES.h"
#include"MCAL/PORT_interface.h"
#include"MCAL/DIO_interface.h"

#include "UTIL/BIT_MATH.h"
#include <util/delay.h>





int main(){
	PORT_voidInit();

	while(1){
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN2, DIO_u8_PIN_HIGH);
		_delay_ms(2000);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN2, DIO_u8_PIN_LOW);
		_delay_ms(2000);
	}

	return 0;
}
