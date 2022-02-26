#ifndef USS_PRIVATE_H_
#define USS_PRIVATE_H_

#define TIMER1_MAX_COUNT 65535


void setICP_RisingEdge(void);
void setICP_FallingEdge();
void stopTimer1();
void Clear_Timer1Flags();
uint32 calcuteDistance();

#endif
