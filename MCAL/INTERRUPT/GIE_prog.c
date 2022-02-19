#include "../INTERRUPT/GIE_interface.h"
#include "../INTERRUPT/GIE_reg.h"
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"


void GIE_voidEnableGlobal(void)
{
	__asm volatile("SEI");
}

void GIE_voidDisableGlobal(void)
{
	__asm volatile("CLI");
}
