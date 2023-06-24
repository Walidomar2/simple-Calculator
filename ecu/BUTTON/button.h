/*
 * button.h
 *
 *  Created on: Jun 10, 2023
 *      Author: Walid Omar
 */

#ifndef ECU_BUTTON_BUTTON_H_
#define ECU_BUTTON_BUTTON_H_

#include "../../MCAL/gpio/gpio.h"


typedef enum{
	BUTTON_RELEASED=0,
	BUTTON_PRESSED
}button_state;

typedef enum
{
	BUTTON_ACTIVE_LOW=0,
	BUTTON_ACTIVE_HIGH
}button_active;

typedef struct{
	pinConfig_t	btn_pin;
	button_active button_connection;
}btn_t;


Std_ReturnType BTN_init(const btn_t *btn_object);
Std_ReturnType BTN_read(const btn_t *btn_object,button_state *btn_state);

#endif /* ECU_BUTTON_BUTTON_H_ */
