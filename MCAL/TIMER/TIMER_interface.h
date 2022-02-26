#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define TIMER0	0
#define TIMER1	1
#define TIMER2	2



uint8 TIMEROvf_u8Enable(uint8 Copy_u8TimerNumber);
uint8 TIMEROvf_u8Disable(uint8 Copy_u8TimerNumber);
uint8 TIMER0ovf_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));
void Timer0_voidSetTimerValue(uint8 Copy_u8Value);


#endif
