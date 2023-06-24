/*
 * ecu_7segment.c
 *
 *  Created on: Jun 10, 2023
 *      Author: Walid Omar
 */

#include "../../std_types.h"
#include "../../MCAL/gpio/gpio.h"
#include "ecu_7segment.h"


static uint8 cathodArr[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//static uint8 anodeArr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};


Std_ReturnType SSD_init(const SSD_t *ssd_object)
{
	Std_ReturnType retValue=ERROR_NOT_OK;

		if(ssd_object == NULL)
		{
			retValue=ERROR_NULL;
		}
		else
		{
			retValue= DIO_port_init(ssd_object->Copy_uSSDPort, OUTPUT);

		}
		return retValue;
}

Std_ReturnType SSD_setNumber(const SSD_t *ssd_object,uint8 value)
{
	Std_ReturnType retValue=ERROR_NOT_OK;

	if(ssd_object == NULL)
	{
		retValue=ERROR_NULL;
	}
	else
	{
		if(ssd_object->Copy_u8SSDType == COMMON_CATHOD)
		{
			switch(ssd_object->Copy_uSSDPort)
			{
			case PORTA_INDEX : {DIO_PORTA=cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTB_INDEX : {DIO_PORTB=cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTC_INDEX : {DIO_PORTC=cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTD_INDEX : {DIO_PORTD=cathodArr[value]; retValue=ERROR_OK; break;}
			default:retValue = ERROR_NOT_OK;
			}
		}
		else if(ssd_object->Copy_u8SSDType == COMMON_ANODE)
		{
			switch(ssd_object->Copy_uSSDPort)
			{
			case PORTA_INDEX : {DIO_PORTA=~cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTB_INDEX : {DIO_PORTB=~cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTC_INDEX : {DIO_PORTC=~cathodArr[value]; retValue=ERROR_OK; break;}
			case PORTD_INDEX : {DIO_PORTD=~cathodArr[value]; retValue=ERROR_OK; break;}
			default:retValue = ERROR_NOT_OK;
			}
		}
		else
		{
			retValue = ERROR_NOT_OK;
		}
	}
	return retValue;
}
