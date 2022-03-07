#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/ERR_TYPE.h"
#include "../../MCAL/DIO_interface.h"
#include <util/delay.h>
#include "../../MCAL/INTERRUPT/GIE_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include "../../MCAL/TIMER/TIMER_reg.h"

#include "USS_private.h"
#include "USS_config.h"
#include "USS_interface.h"

static uint16 volatile TIMER1_OVER_FLOW = 0;



void USS_voidInit(void){
	GIE_voidEnableGlobal(); //  enable global intterupt
	TIMEROvf_u8Enable(TIMER1); // enable over flow interrupt for timer 1
	TCCR1A = 0; // normal counter no compare or PWM
}


void setICP_RisingEdge(){
	/* wait for rising edge on USS_ECHO pin (input capture pin ICP1)*/
	/* change bits of timer counter control 1 */
	SET_BIT(TCCR1B, TCCR1B_ICES1); /* set capture on rising edge */
	SET_BIT(TCCR1B, TCCR1B_CS10); /* start timer with no prescaler */
}


void setICP_FallingEdge(){
	CLR_BIT(TCCR1B, TCCR1B_ICES1); // Capture on falling edge
	SET_BIT(TCCR1B, TCCR1B_CS10); // start count no prescaler
}

void stopTimer1(){
	CLR_BIT(TCCR1B, TCCR1B_CS10);
}

void Clear_Timer1Flags(){
	/* clear flags */
	SET_BIT(TIFR, TIFR_ICF1); /* Clear ICP flag (Input Capture flag) */
	SET_BIT(TIFR, TIFR_TOV1); /* Clear Timer Overflow flag */
}


uint32 calcuteDistance(){
	/*
		this calculation is based on the used crystal oscillator
		which is 16 MHZ
		 distance in cm = 17150 * TIMER
		 = 17150 x (TIMER value) x 0.0625 x 10^-6 cm
		 = (TIMER value) * (0.343 / 320)
		 = 1/923.94

		 trigger pin DIO_u8_PORTA
		 */

	/* current count */
	uint32 count  = (uint16)ICR1L;
	//count = count | (ICR1H << 8);

	count += TIMER1_MAX_COUNT * TIMER1_OVER_FLOW;

	return (uint32)((float32)count / 923.94);
}


uint32 USS_u32GetDistance(void){

	/*
	 * make sure that global interrupt is enabled
		 timer 1 over flow is enabled
		 register TCCR1A set as normal operation i.e. TCCR1A = 0;
	 * */

	/* send 10us pulse to trigger pin */
	DIO_u8SetPinValue(USS_u8_TRIGGER_PORT, USS_u8_TRIGGER_PIN, DIO_u8_PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(USS_u8_TRIGGER_PORT, USS_u8_TRIGGER_PIN, DIO_u8_PIN_LOW);

	TCNT1H = 0;	/* Clear Timer1 counter */
	TCNT1L = 0;

	setICP_RisingEdge(); /* set capture on rising edge and start timer */
	Clear_Timer1Flags(); /* clear TIMER1 ovf and ICP flag from TIFR*/

	/* when ICP1 receives a rising edge TIFR_ICF1 in TIFR will get triggered*/
	while ((TIFR & (1 << TIFR_ICF1)) == 0);/* wait for rising edge */

	TCNT1H = 0;	/* Clear Timer1 counter */
	TCNT1L = 0;

	setICP_FallingEdge(); /* set capture on falling edge and start timer */
	Clear_Timer1Flags(); /* clear TIMER1 ovf and ICP flag from TIFR*/
	TIMER1_OVER_FLOW = 0;

	while ((TIFR & (1 << TIFR_ICF1)) == 0);/* Wait for falling edge */

	return calcuteDistance();
}


void __vector_9(void) __attribute__((signal));

void __vector_9(void)
{
	TIMER1_OVER_FLOW++;
}




