#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,BITNO)   ((var) |=  (1<<(BITNO)))
#define CLR_BIT(var,BITNO) ((var) &= ~(1<<(BITNO)))
#define TOG_BIT(var,BITNO)  ((var) ^=  (1<<(BITNO)))
#define GET_BIT(var,BITNO) ((var>>BITNO) & 1)
#define ASSIGN_BIT(var,BITNO,val) (var=(var & (~(1<<BITNO))) | (val<<BITNO))

#endif
