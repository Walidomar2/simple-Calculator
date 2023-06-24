/*
 * keypad.c
 *
 *  Created on: Jun 11, 2023
 *      Author: Walid Omar
 */

#include "../../bit_masking.h"
#include "../../std_types.h"
#include <util/delay.h>
#include "keypad.h"

static uint8 keypadValues[KEYPAD_ROWS_NUMBER][KEYPAD_COLUMN_NUMBER] ={  {'7','8','9','/'},
																		{'4','5','6','*'},
																		{'1','2','3','-'},
																		{'#','0','=','+'}};

Std_ReturnType KEYPAD_init(const keypad_t *keypad_object)
{
	Std_ReturnType retValue = ERROR_NOT_OK;

	if(keypad_object == NULL)
	{
		retValue = ERROR_NULL;
	}
	else
	{
		int i=0;
		for(i=0;i<KEYPAD_ROWS_NUMBER;i++)
		{
			retValue = DIO_pin_init(&keypad_object->pin_row[i]);
		}

		for(i=0;i<KEYPAD_COLUMN_NUMBER;i++)
		{
			retValue = DIO_pin_init(&keypad_object->pin_col[i]);
			retValue = DIO_pin_pull_up_active(&keypad_object->pin_col[i]);
		}
	}
	return retValue;
}

uint8 KEYPAD_read(const keypad_t *keypad_object,uint8	*value)
{
	uint8 flag=0;
	uint8 rowCounter=0;
	uint8 colCounter=0;
	uint8 counter=0;
	logic_t key_state = HIGH;

	for(rowCounter=0;rowCounter<KEYPAD_ROWS_NUMBER;rowCounter++)
	{
		for(counter=0;counter<KEYPAD_ROWS_NUMBER;counter++)
			{
				DIO_pin_write(&keypad_object->pin_row[counter], HIGH);
			}

				DIO_pin_write(&keypad_object->pin_row[rowCounter], LOW);


				for(colCounter=0;colCounter<KEYPAD_COLUMN_NUMBER;colCounter++)
				{
					DIO_pin_read(&keypad_object->pin_col[colCounter],&key_state);
					if(key_state == LOW)
					{
						*value = keypadValues[rowCounter][colCounter];
						flag=1;
						_delay_ms(400);
						break;
					}
				}
				if(key_state == LOW)	{break;}
	}

	return flag;
}
