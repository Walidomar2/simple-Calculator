/*
 * gpio.c
 *
 *  Created on: Jun 9, 2023
 *      Author: Walid Omar
 */

#include "../../bit_masking.h"
#include "../../std_types.h"
#include "gpio.h"

Std_ReturnType DIO_pin_init(const pinConfig_t *pin_object)
{
	Std_ReturnType retValue=ERROR_NOT_OK;

	if(pin_object == NULL)
	{
		retValue=ERROR_NULL;
	}
	else
	{
		if(pin_object->directionSel == OUTPUT)
		{
			switch(pin_object->portSel)
			{
			case PORTA_INDEX:	{BIT_SET(pin_object->pinSel,DIO_DDRA); retValue= ERROR_OK;	break;}
			case PORTB_INDEX:	{BIT_SET(pin_object->pinSel,DIO_DDRB); retValue= ERROR_OK;	break;}
			case PORTC_INDEX:	{BIT_SET(pin_object->pinSel,DIO_DDRC); retValue= ERROR_OK;	break;}
			case PORTD_INDEX:	{BIT_SET(pin_object->pinSel,DIO_DDRD); retValue= ERROR_OK;	break;}
			default:retValue=ERROR_NOT_OK;
			}

		}
		else if(pin_object->directionSel == INPUT)
		{
			switch(pin_object->portSel)
			{
			case PORTA_INDEX:	{BIT_CLEAR(pin_object->pinSel,DIO_DDRA); retValue= ERROR_OK; break;}
			case PORTB_INDEX:	{BIT_CLEAR(pin_object->pinSel,DIO_DDRB); retValue= ERROR_OK; break;}
			case PORTC_INDEX:	{BIT_CLEAR(pin_object->pinSel,DIO_DDRC); retValue= ERROR_OK; break;}
			case PORTD_INDEX:	{BIT_CLEAR(pin_object->pinSel,DIO_DDRD); retValue= ERROR_OK; break;}
			default:retValue=ERROR_NOT_OK;
			}
		}
		else
		{
			retValue = ERROR_NOT_OK;
		}
	}
	return retValue;
}

Std_ReturnType DIO_pin_read(const pinConfig_t *pin_object,logic_t *value)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(pin_object == NULL || value == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		switch(pin_object->portSel)
		{
		case PORTA_INDEX : {*value=BIT_READ(pin_object->pinSel,DIO_PINA); retValue= ERROR_OK; break;}
		case PORTB_INDEX : {*value=BIT_READ(pin_object->pinSel,DIO_PINB); retValue= ERROR_OK; break;}
		case PORTC_INDEX : {*value=BIT_READ(pin_object->pinSel,DIO_PINC); retValue= ERROR_OK; break;}
		case PORTD_INDEX : {*value=BIT_READ(pin_object->pinSel,DIO_PIND); retValue= ERROR_OK; break;}
		default:retValue=ERROR_NOT_OK;
		}
	}
	return retValue;
}

Std_ReturnType DIO_pin_write(const pinConfig_t *pin_object,logic_t value)
{
	Std_ReturnType retValue=ERROR_NOT_OK;
	if(pin_object == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		if(value == HIGH)
		{
			switch(pin_object->portSel)
			{
			case PORTA_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTA); retValue= ERROR_OK; break;}
			case PORTB_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTB); retValue= ERROR_OK; break;}
			case PORTC_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTC); retValue= ERROR_OK; break;}
			case PORTD_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTD); retValue= ERROR_OK; break;}
			default: retValue = ERROR_NOT_OK;
			}

		}
		else if(value == LOW)
		{
			switch(pin_object->portSel)
			{
			case PORTA_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTA); retValue= ERROR_OK; break;}
			case PORTB_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTB); retValue= ERROR_OK; break;}
			case PORTC_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTC); retValue= ERROR_OK; break;}
			case PORTD_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTD); retValue= ERROR_OK; break;}
			default: retValue = ERROR_NOT_OK;

			}
		}
		else{retValue= ERROR_NOT_OK;}

	}
	return retValue;
}

Std_ReturnType DIO_pin_toggle(const pinConfig_t *pin_object)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(pin_object == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		switch(pin_object->portSel)
		{
		case PORTA_INDEX:{BIT_TOGGLE(pin_object->pinSel,DIO_PORTA); retValue= ERROR_OK; break;}
		case PORTB_INDEX:{BIT_TOGGLE(pin_object->pinSel,DIO_PORTB); retValue= ERROR_OK; break;}
		case PORTC_INDEX:{BIT_TOGGLE(pin_object->pinSel,DIO_PORTC); retValue= ERROR_OK; break;}
		case PORTD_INDEX:{BIT_TOGGLE(pin_object->pinSel,DIO_PORTD); retValue= ERROR_OK; break;}
		default : retValue = ERROR_NOT_OK;
		}
	}
	return retValue;
}

Std_ReturnType DIO_pin_pull_up_active(const pinConfig_t *pin_object)
{
	Std_ReturnType retValue = ERROR_NOT_OK;
	if(pin_object == NULL)
	{
		retValue = ERROR_NULL;
	}
	else
	{
		if(pin_object->directionSel == INPUT)
		{
			switch(pin_object->portSel)
			{
			case PORTA_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTA); retValue= ERROR_OK; break;}
			case PORTB_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTB); retValue= ERROR_OK; break;}
			case PORTC_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTC); retValue= ERROR_OK; break;}
			case PORTD_INDEX:{BIT_SET(pin_object->pinSel,DIO_PORTD); retValue= ERROR_OK; break;}
			default : retValue = ERROR_NOT_OK;
			}
		}

	}
	return retValue;
}

Std_ReturnType DIO_pin_pull_up_deactive(const pinConfig_t *pin_object)
{
	Std_ReturnType retValue = ERROR_NOT_OK;
		if(pin_object == NULL)
		{
			retValue = ERROR_NULL;
		}
		else
		{
			if(pin_object->directionSel == INPUT)
			{
				switch(pin_object->portSel)
				{
				case PORTA_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTA); retValue= ERROR_OK; break;}
				case PORTB_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTB); retValue= ERROR_OK; break;}
				case PORTC_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTC); retValue= ERROR_OK; break;}
				case PORTD_INDEX:{BIT_CLEAR(pin_object->pinSel,DIO_PORTD); retValue= ERROR_OK; break;}
				default : retValue = ERROR_NOT_OK;
				}
			}
		}
		return retValue;
}

Std_ReturnType DIO_port_init(portIndex_t port_object,direction_t direction)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(direction == OUTPUT)
	{
		switch(port_object)
		{
		case PORTA_INDEX :{DIO_DDRA=DIO_u8_PORT_OUTPUT; retValue=ERROR_OK; break;}
		case PORTB_INDEX :{DIO_DDRB=DIO_u8_PORT_OUTPUT; retValue=ERROR_OK; break;}
		case PORTC_INDEX :{DIO_DDRC=DIO_u8_PORT_OUTPUT; retValue=ERROR_OK; break;}
		case PORTD_INDEX :{DIO_DDRD=DIO_u8_PORT_OUTPUT; retValue=ERROR_OK; break;}
		default: retValue = ERROR_NOT_OK;
		}
	}
	else if(direction == INPUT)
	{
		switch(port_object)
		{
		case PORTA_INDEX :{DIO_DDRA=DIO_u8_PORT_INPUT; retValue=ERROR_OK; break;}
		case PORTB_INDEX :{DIO_DDRB=DIO_u8_PORT_INPUT; retValue=ERROR_OK; break;}
		case PORTC_INDEX :{DIO_DDRC=DIO_u8_PORT_INPUT; retValue=ERROR_OK; break;}
		case PORTD_INDEX :{DIO_DDRD=DIO_u8_PORT_INPUT; retValue=ERROR_OK; break;}
		default: retValue = ERROR_NOT_OK;
		}
	}
	else{retValue = ERROR_NOT_OK;}

	return retValue;
}

Std_ReturnType DIO_port_read(portIndex_t port_object,uint8 *value)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(value == NULL)
	{
		retValue= ERROR_NULL;
	}
	else{
		switch(port_object)
		{
		case PORTA_INDEX :{*value=DIO_PINA; retValue=ERROR_OK; break;}
		case PORTB_INDEX :{*value=DIO_PINB; retValue=ERROR_OK; break;}
		case PORTC_INDEX :{*value=DIO_PINC; retValue=ERROR_OK; break;}
		case PORTD_INDEX :{*value=DIO_PIND; retValue=ERROR_OK; break;}
		default: retValue=ERROR_NOT_OK;
		}
	}
	return retValue;
}

Std_ReturnType DIO_port_write(portIndex_t port_object,uint8 value)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	switch(port_object)
	{
	case PORTA_INDEX :{DIO_PORTA = value; retValue=ERROR_OK; break;}
	case PORTB_INDEX :{DIO_PORTB = value; retValue=ERROR_OK; break;}
	case PORTC_INDEX :{DIO_PORTC = value; retValue=ERROR_OK; break;}
	case PORTD_INDEX :{DIO_PORTD = value; retValue=ERROR_OK; break;}
	default: retValue=ERROR_NOT_OK;
	}

	return retValue;
}


Std_ReturnType DIO_port_toggle(portIndex_t port_object)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	switch(port_object)
	{
	case PORTA_INDEX :{DIO_PORTA ^=0xff; retValue=ERROR_OK; break;}
	case PORTB_INDEX :{DIO_PORTB ^=0xff; retValue=ERROR_OK; break;}
	case PORTC_INDEX :{DIO_PORTC ^=0xff; retValue=ERROR_OK; break;}
	case PORTD_INDEX :{DIO_PORTD ^=0xff; retValue=ERROR_OK; break;}
	default: retValue=ERROR_NOT_OK;
	}

	return retValue;
}

