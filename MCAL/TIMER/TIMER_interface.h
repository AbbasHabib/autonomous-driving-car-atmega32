#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_Init(void);
uint8 TIMER0ovf_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));
void Timer0_voidSetTimerValue(uint8 Copy_u8Value);

#endif
