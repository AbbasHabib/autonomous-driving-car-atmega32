#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_u8_DATA_PORT		DIO_u8_PORTA
/*Choose your connection mode , options : 1- EIGHT_BIT
 * 										  2- FOUR_BIT*/
#define CLCD_u8_MODE			FOUR_BIT

#if CLCD_u8_MODE == FOUR_BIT
#define CLCD_u8_PIN4			DIO_u8_PIN4
#define CLCD_u8_PIN5			DIO_u8_PIN5
#define CLCD_u8_PIN6			DIO_u8_PIN6
#define CLCD_u8_PIN7			DIO_u8_PIN7
#endif

#define CLCD_u8_CTRL_PORT		DIO_u8_PORTB
#define CLCD_u8_RS_PIN			DIO_u8_PIN1
#define CLCD_u8_RW_PIN			DIO_u8_PIN2
#define CLCD_u8_E_PIN			DIO_u8_PIN3

#endif
