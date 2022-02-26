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

uint16 volatile time_overflow = 0;


int main(){
	PORT_voidInit();
	CLCD_voidInit();
	USS_voidInit();
	while(1){
		uint32 distance = USS_u32GetDistance();
		CLCD_sendString("distance: ");
		CLCD_sendNumebr((uint32)distance);
		_delay_ms(200);
		CLCD_voidClearDisplay();
	}

	return 0;
}
