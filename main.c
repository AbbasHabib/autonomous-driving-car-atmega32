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

uint16 volatile time_overflow = 0;



void __vector_9(void) __attribute__((signal));

void __vector_9(void)
{
	time_overflow++;
}


int main(){
	PORT_voidInit();
	CLCD_voidInit();

	//CLCD_voidClearDisplay();

	// distance in cm = 17150 * TIMER
	// = 17150 x (TIMER value) x 0.0625 x 10^-6 cm
	// = (TIMER value) * (0.343 / 320)
	// = 1/923.94

	// trigger pin DIO_u8_PORTA

	GIE_voidEnableGlobal(); //  enable global intterupt
	TIMEROvf_u8Enable(TIMER1); // enable over flow interrupt for timer 1
	TCCR1A = 0; /* Set all bit to zero Normal operation */


	while(1)
	{

		// send 10us puls ti trigger pin
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_PIN_LOW);

		TCNT1H = 0;	/* Clear Timer counter */
		TCNT1L = 0;

		SET_BIT(TCCR1B,TCCR1B_ICES1); // capture on rising edge
		SET_BIT(TCCR1B, TCCR1B_CS10); // start cont no prescaler

		SET_BIT(TIFR, TIFR_ICF1);/* Clear ICP flag (Input Capture flag) */
		SET_BIT(TIFR, TIFR_TOV1);/* Clear Timer Overflow flag */

		while ((TIFR & (1 << TIFR_ICF1)) == 0);// wait for rising edge
		TCNT1H = 0;	/* Clear Timer counter */
		TCNT1L = 0;
		CLR_BIT(TCCR1B, TCCR1B_ICES1); // Capture on falling edge
		SET_BIT(TCCR1B, TCCR1B_CS10); // start count no prescaler

		SET_BIT(TIFR, TIFR_ICF1);/* Clear ICP flag (Input Capture flag) */
		SET_BIT(TIFR, TIFR_TOV1);/* Clear Timer Overflow flag */

		time_overflow = 0;

		while ((TIFR & (1 << TIFR_ICF1)) == 0);/* Wait for falling edge */
		uint32 count  = ICR1L;
		count = count | ICR1H << 8;
		count += 65535 * time_overflow;

		float32 distance = (float32)count / 923.94;
		CLCD_sendString("distance: ");
		CLCD_sendNumebr((uint32)distance);
		_delay_ms(200);
		CLCD_voidClearDisplay();



	}

	return 0;
}
