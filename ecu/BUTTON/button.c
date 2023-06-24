/*
 * button.c
 *
 *  Created on: Jun 10, 2023
 *      Author: Walid Omar
 */

#include "../../bit_masking.h"
#include "../../std_types.h"
#include "button.h"


Std_ReturnType BTN_init(const btn_t *btn_object)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(btn_object == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		retValue = DIO_pin_init(&btn_object->btn_pin);
		retValue = DIO_pin_pull_up_active(&btn_object->btn_pin);
	}

	return retValue;
}

Std_ReturnType BTN_read(const btn_t *btn_object,button_state *btn_state)
{
	Std_ReturnType retValue= ERROR_NOT_OK;
	logic_t pin_state;

	if(btn_object == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		if(btn_object->button_connection == BUTTON_ACTIVE_HIGH)
		{
			retValue = DIO_pin_read(&btn_object->btn_pin, &pin_state);
			if(pin_state == HIGH){*btn_state = BUTTON_PRESSED; retValue= ERROR_OK;}
			else if(pin_state == LOW){*btn_state = BUTTON_RELEASED; retValue= ERROR_OK;}
			else{retValue= ERROR_NOT_OK;}
		}
		else if(btn_object->button_connection == BUTTON_ACTIVE_LOW)
		{
			retValue = DIO_pin_read(&btn_object->btn_pin, &pin_state);
			if(pin_state == HIGH){*btn_state = BUTTON_RELEASED; retValue= ERROR_OK;}
			else if(pin_state == LOW){*btn_state = BUTTON_PRESSED; retValue= ERROR_OK;}
			else{retValue= ERROR_NOT_OK;}

		}
		else
		{
			retValue= ERROR_NOT_OK;
		}
	}

	return retValue;
}
