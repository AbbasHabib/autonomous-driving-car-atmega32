#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/ERR_TYPE.h"

#include "../INTERRUPT/EXTI_config.h"
#include "../INTERRUPT/EXTI_interface.h"
#include "../INTERRUPT/EXTI_private.h"
#include "../INTERRUPT/EXTI_reg.h"

/*GLobal array of pointer to function*/
void (*EXTI_pvCallBackFunc[3])(void) = {NULL,NULL,NULL};

void EXTI_voidInit(void)
{

#if EXTI_u8_INT0_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);
#elif EXTI_u8_INT0_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);
#elif EXTI_u8_INT0_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	CLR_BIT(MCUCR,MCUCR_ISC00);
#elif EXTI_u8_INT0_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(MCUCR,MCUCR_ISC00);
#else
#error "Wrong EXIT_u8_INT0_SENSE_ CONTROL configuration option"
#endif

/******************************************************************/
#if EXTI_u8_INT1_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
#elif EXTI_u8_INT1_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#elif EXTI_u8_INT1_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
#elif EXTI_u8_INT1_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#else
#error "Wrong EXIT_u8_INT1_SENSE_ CONTROL configuration option"
#endif
/*******************************************************************/
#if EXTI_u8_INT2_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC2);
#elif EXTI_u8_INT2_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error "Wrong EXIT_u8_INT2_SENSE_ CONTROL configuration option"
#endif

/*******************************************************************/
/*******************************************************************/

#if EXTI_u8_INT0_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#elif EXTI_u8_INT0_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#else
#error "Wrong EXIT_u8_INT0_INIT_SENSE_CONTROL configuration option"
#endif

#if EXTI_u8_INT1_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#elif EXTI_u8_INT1_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#else
#error "Wrong EXIT_u8_INT1_INIT_SENSE_CONTROL configuration option"
#endif

#if EXTI_u8_INT2_INIT_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#elif EXTI_u8_INT2_INIT_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#else
#error "Wrong EXIT_u8_INT2_INIT_SENSE_CONTROL configuration option"
#endif

}
uint8 EXTI_u8SetSenseControl(uint8 Copy_u8IntNum,uint8 Copy_u8Sense)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8IntNum == EXTI_u8_INT0)
	{
		switch(Copy_u8Sense)
		{
		case LOW_LEVEL : 	CLR_BIT(MCUCR,MCUCR_ISC01); CLR_BIT(MCUCR,MCUCR_ISC00); break;
		case ON_CHANGE : 	CLR_BIT(MCUCR,MCUCR_ISC01); SET_BIT(MCUCR,MCUCR_ISC00); break;
		case FALLING_EDGE : SET_BIT(MCUCR,MCUCR_ISC01); CLR_BIT(MCUCR,MCUCR_ISC00); break;
		case RISING_EDGE :  SET_BIT(MCUCR,MCUCR_ISC01); SET_BIT(MCUCR,MCUCR_ISC00); break;
		default : Local_u8ErrorState = NOK;
		}
	}
	else if(Copy_u8IntNum == EXTI_u8_INT1)
	{
		switch(Copy_u8Sense)
		{
		case LOW_LEVEL : 	CLR_BIT(MCUCR,MCUCR_ISC11); CLR_BIT(MCUCR,MCUCR_ISC10); break;
		case ON_CHANGE : 	CLR_BIT(MCUCR,MCUCR_ISC11); SET_BIT(MCUCR,MCUCR_ISC10); break;
		case FALLING_EDGE : SET_BIT(MCUCR,MCUCR_ISC11); CLR_BIT(MCUCR,MCUCR_ISC10); break;
		case RISING_EDGE :  SET_BIT(MCUCR,MCUCR_ISC11); SET_BIT(MCUCR,MCUCR_ISC10); break;
		default : Local_u8ErrorState = NOK;
		}
	}
	else if(Copy_u8IntNum == EXTI_u8_INT2)
	{
		switch(Copy_u8Sense)
		{
		case FALLING_EDGE : CLR_BIT(MCUCSR,MCUCSR_ISC2); break;
		case RISING_EDGE :  SET_BIT(MCUCSR,MCUCSR_ISC2); break;
		default : Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
uint8 EXTI_u8EnableInt(uint8 Copy_u8IntNum)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8_INT0 : SET_BIT(GICR,GICR_INT0); break;
	case EXTI_u8_INT1 : SET_BIT(GICR,GICR_INT1); break;
	case EXTI_u8_INT2 : SET_BIT(GICR,GICR_INT2); break;
	default : Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
uint8 EXTI_u8DisableInt(uint8 Copy_u8IntNum)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8_INT0 : CLR_BIT(GICR,GICR_INT0); break;
	case EXTI_u8_INT1 : CLR_BIT(GICR,GICR_INT1); break;
	case EXTI_u8_INT2 : CLR_BIT(GICR,GICR_INT2); break;
	default : Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum , void (*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		EXTI_pvCallBackFunc[Copy_u8IntNum] = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}
/*INT0 ISR*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_pvCallBackFunc[EXTI_u8_INT0] != NULL)
	{
		EXTI_pvCallBackFunc[EXTI_u8_INT0]();
	}
	else
	{
		/*Do nothing*/
	}
}
/*INT0 ISR*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pvCallBackFunc[EXTI_u8_INT1] != NULL)
	{
		EXTI_pvCallBackFunc[EXTI_u8_INT1]();
	}
	else
	{
		/*Do nothing*/
	}}
/*INT0 ISR*/
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pvCallBackFunc[EXTI_u8_INT2] != NULL)
	{
		EXTI_pvCallBackFunc[EXTI_u8_INT2]();
	}
	else
	{
		/*Do nothing*/
	}}
