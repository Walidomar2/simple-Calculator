/*
 * external_interrupt.c
 *
 *  Created on: Jun 14, 2023
 *      Author: Walid Omar
 */

#include "../../bit_masking.h"
#include "../../std_types.h"
#include "external_interrupt.h"

static void (*INT0_Fptr) (void)=NULL;
static void (*INT1_Fptr) (void)=NULL;
static void (*INT2_Fptr) (void)=NULL;


Std_ReturnType EXT_Enable(ExInterruptSource_type interrupt,TriggerEdge_type edge)
{
	Std_ReturnType retValue =ERROR_NOT_OK;

	switch(interrupt)
	{
	case EX_INT0 :
		{
			BIT_SET(INT0,GICR_REG);
			retValue = ERROR_OK;
			switch(edge)
			{
			case LOW_LEVEL:{BIT_CLEAR(ISC00,MCUCR_REG);	BIT_CLEAR(ISC01,MCUCR_REG);	break;}
			case ANY_LOGIC_CHANGE:{BIT_SET(ISC00,MCUCR_REG); BIT_CLEAR(ISC01,MCUCR_REG); break;}
			case FALLING_EDGE:{BIT_CLEAR(ISC00,MCUCR_REG); BIT_SET(ISC01,MCUCR_REG); break;}
			case RISING_EDGE:{BIT_SET(ISC00,MCUCR_REG); BIT_SET(ISC01,MCUCR_REG); break;}
			default:retValue =ERROR_NOT_OK;
			}
			break;
		}
	case EX_INT1:
		{
			BIT_SET(INT1,GICR_REG);
			retValue = ERROR_OK;
			switch(edge)
			{
			case LOW_LEVEL:{BIT_CLEAR(ISC10,MCUCR_REG);	BIT_CLEAR(ISC11,MCUCR_REG);	break;}
			case ANY_LOGIC_CHANGE:{BIT_SET(ISC10,MCUCR_REG); BIT_CLEAR(ISC11,MCUCR_REG); break;}
			case FALLING_EDGE:{BIT_CLEAR(ISC10,MCUCR_REG); BIT_SET(ISC11,MCUCR_REG); break;}
			case RISING_EDGE:{BIT_SET(ISC10,MCUCR_REG); BIT_SET(ISC11,MCUCR_REG); break;}
			default:retValue =ERROR_NOT_OK;
			}
			break;
		}
	case EX_INT2:
		{
			BIT_SET(INT2,GICR_REG);
			retValue = ERROR_OK;
			switch(edge)
			{
			case FALLING_EDGE:{BIT_CLEAR(ISC2,MCUCSR_REG); break;}
			case RISING_EDGE:{BIT_SET(ISC2,MCUCSR_REG); break;}
			default:BIT_SET(ISC2,MCUCSR_REG);
			}
			break;
		}

	}

	return retValue;
}

Std_ReturnType EXT_Disable(ExInterruptSource_type interrupt)
{
	Std_ReturnType retValue=ERROR_NOT_OK;
	switch(interrupt)
	{
	case EX_INT0:{BIT_CLEAR(INT0,GICR_REG); retValue=ERROR_OK; break;}
	case EX_INT1:{BIT_CLEAR(INT1,GICR_REG); retValue=ERROR_OK; break;}
	case EX_INT2:{BIT_CLEAR(INT2,GICR_REG); retValue=ERROR_OK; break;}
	default: retValue =ERROR_NOT_OK;
	}
	return retValue;
}

Std_ReturnType SET_CallBack(ExInterruptSource_type interrupt,void(*callback_Func)(void))
{
	Std_ReturnType retValue=ERROR_NOT_OK;

	switch(interrupt)
	{
	case EX_INT0:{INT0_Fptr = callback_Func; retValue=ERROR_OK; break;}
	case EX_INT1:{INT1_Fptr = callback_Func; retValue=ERROR_OK; break;}
	case EX_INT2:{INT2_Fptr = callback_Func; retValue=ERROR_OK; break;}
	default :retValue =ERROR_NOT_OK;
	}
	return retValue;
}


/******************************** ISR VECTORS **************************************/

ISR(INT0_VECTOR)
{
	if(INT0_Fptr != NULL)
	{
		INT0_Fptr();
	}
}

ISR(INT1_VECTOR)
{
	if(INT1_Fptr != NULL)
	{
		INT1_Fptr();
	}
}

ISR(INT2_VECTOR)
{
	if(INT2_Fptr != NULL)
	{
		INT2_Fptr();
	}
}
