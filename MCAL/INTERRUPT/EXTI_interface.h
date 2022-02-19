#ifndef	EXIT_INTERFACE_H_
#define EXIT_INTERFACE_H_

#define EXTI_u8_INT0		0
#define EXTI_u8_INT1		1
#define EXTI_u8_INT2		2


#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4


void EXTI_voidInit(void);

uint8 EXTI_u8SetSenseControl(uint8 Copy_u8IntNum,uint8 Copy_u8Sense);
uint8 EXTI_u8EnableInt(uint8 Copy_u8IntNum);
uint8 EXTI_u8DisableInt(uint8 Copy_u8IntNum);

uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum , void (*Copy_pvCallBackFunc)(void));

#endif
