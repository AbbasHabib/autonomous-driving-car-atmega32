#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(uint8 Copy_u8Command);
void CLCD_voidSendData(uint8 Copy_u8Data);
void CLCD_voidInit(void);
uint8 CLCD_sendString(char Copy_u8StringArray[]);
uint8 CLCD_sendNumebr(uint32 Copy_u8Number);
void CLCD_voidGoToXY(uint8 Copy_u8XPos , uint8 Copy_YPos);
uint8 CLCD_voidSendSpecialChatacter(uint8* Copy_u8Pattern,uint8 Copy_u8PatternNum,uint8 Copy_u8XPos, uint8 Copy_u8YPos);
void CLCD_voidClearDisplay();
#endif
