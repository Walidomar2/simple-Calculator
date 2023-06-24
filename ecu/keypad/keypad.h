/*
 * keypad.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Walid Omar
 */

#include "../../MCAL/gpio/gpio.h"

#ifndef ECU_KEYPAD_KEYPAD_H_
#define ECU_KEYPAD_KEYPAD_H_

#define KEYPAD_ROWS_NUMBER		4
#define KEYPAD_COLUMN_NUMBER	4

#define KEYPAD_NOT_PRESSED		(uint8)0xFF

typedef struct
{
	pinConfig_t	pin_row[4];
	pinConfig_t	pin_col[4];
}keypad_t;

Std_ReturnType KEYPAD_init(const keypad_t *keypad_object);
uint8 KEYPAD_read(const keypad_t *keypad_object,uint8 *value);


#endif /* ECU_KEYPAD_KEYPAD_H_ */
