#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/ERR_TYPE.h"
#include "../../MCAL/DIO_interface.h"
#include <util/delay.h>
#include "SERVO_config.h"
#include "SERVO_interface.h"


void SERVO_voidRotateToAngle(uint8 Copy_u8AngleValue){
	if (Copy_u8AngleValue <= 0)
		Copy_u8AngleValue = 1;
	float32 Local_DelayValue = (1009.0f * (float32)Copy_u8AngleValue) / 50.0;
	DIO_u8SetPinValue(SERVO_u8_PORT, SERVO_u8_PIN, DIO_u8_PIN_HIGH);
	_delay_us(Local_DelayValue);
	DIO_u8SetPinValue(SERVO_u8_PORT, SERVO_u8_PIN, DIO_u8_PIN_LOW);
}
