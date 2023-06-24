/*
 * main.c
 *
 *  Created on: Jun 9, 2023
 *      Author: Walid Omar
 */


#include <util/delay.h>

#include "std_types.h"
#include "bit_masking.h"
#include "MCAL/gpio/gpio.h"
#include "MCAL/interrupt/external_interrupt.h"
#include "ecu/7-segment/ecu_7segment.h"
#include "ecu/BUTTON/button.h"
#include "ecu/keypad/keypad.h"
#include "ecu/LCD/lcd.h"


sint32 calculation(sint32 num1,sint32 num2,uint8 op)
{
	sint32 result;

	switch(op)
	{
	case '+':	{result = num1 + num2; break;}
	case '-':	{result = num1 - num2; break;}
	case '*':	{result = num1 * num2; break;}
	case '/':	{result = num1 / num2; break;}
	default : result=0;
	}

	return result;
}
Std_ReturnType ret=ERROR_NOT_OK;

keypad_t keypad_1 =
{
		.pin_row[0].portSel = PORTC_INDEX,
		.pin_row[0].pinSel = PIN_5,
		.pin_row[0].directionSel=OUTPUT,

		.pin_row[1].portSel = PORTC_INDEX,
		.pin_row[1].pinSel = PIN_4,
		.pin_row[1].directionSel=OUTPUT,

		.pin_row[2].portSel = PORTC_INDEX,
		.pin_row[2].pinSel = PIN_3,
		.pin_row[2].directionSel=OUTPUT,

		.pin_row[3].portSel = PORTC_INDEX,
		.pin_row[3].pinSel = PIN_2,
		.pin_row[3].directionSel=OUTPUT,

		.pin_col[0].portSel = PORTD_INDEX,
		.pin_col[0].pinSel = PIN_7,
		.pin_col[0].directionSel=INPUT,

		.pin_col[1].portSel = PORTD_INDEX,
		.pin_col[1].pinSel = PIN_6,
		.pin_col[1].directionSel=INPUT,

		.pin_col[2].portSel = PORTD_INDEX,
		.pin_col[2].pinSel = PIN_5,
	    .pin_col[2].directionSel=INPUT,

		.pin_col[3].portSel = PORTD_INDEX,
		.pin_col[3].pinSel = PIN_3,
		.pin_col[3].directionSel=INPUT,
};


lcd_4bit_t lcd_1 =
{
		.RS.portSel = PORTA_INDEX,
		.RS.pinSel = PIN_3,
		.RS.directionSel = OUTPUT,

		.EN.portSel = PORTA_INDEX,
		.EN.pinSel = PIN_2,
		.EN.directionSel = OUTPUT,

		.lcd_data[0].portSel = PORTB_INDEX,
		.lcd_data[0].pinSel = PIN_0,
		.lcd_data[0].directionSel = OUTPUT,

		.lcd_data[1].portSel = PORTB_INDEX,
		.lcd_data[1].pinSel = PIN_1,
		.lcd_data[1].directionSel = OUTPUT,

		.lcd_data[2].portSel = PORTB_INDEX,
	    .lcd_data[2].pinSel = PIN_2,
	    .lcd_data[2].directionSel = OUTPUT,

		.lcd_data[3].portSel = PORTB_INDEX,
		.lcd_data[3].pinSel = PIN_4,
		.lcd_data[3].directionSel = OUTPUT
};


int main()
{

	ret = lcd_4bit_init(&lcd_1);
	ret = KEYPAD_init(&keypad_1);

	uint8   i=0;
	uint8   flag=0;
	uint8   value;
	sint32  number1;
	sint32  number2;
	uint8   operation;

	sint32 result;

	for(i=0;i<4;i++)
		{
			while(!KEYPAD_read(&keypad_1,&value));

			if(value == '-' || value == '+' || value == '*' || value == '/' )
			{
				operation = value;
				lcd_4bit_send_char(&lcd_1,operation);
				flag = 1;
				break;
			}
			else
			{
				lcd_4bit_send_char(&lcd_1,value);
				number1= number1*10+value-'0';
			}
		}

		if(0 == flag)
		{
			while(!KEYPAD_read(&keypad_1,&value));
			operation = value;
			lcd_4bit_send_char(&lcd_1,operation);
		}

		for(i=0;i<4;i++)
		{
			while(!KEYPAD_read(&keypad_1,&value));

		if(value == '=')
		{
			lcd_4bit_send_char(&lcd_1,value);

			if(number2 == 0 && operation =='/')
			{
				lcd_4bit_send_string(&lcd_1,"Invalid");
				flag =1;
				break;

			}
			result = calculation(number1,number2,operation);
			lcd_4bit_send_number(&lcd_1,result);
			flag = 1;
			break;
		}
		else
		{
			number2 =number2*10+value-'0';
			lcd_4bit_send_char(&lcd_1,value);
		}
	}

	if(0 == flag)
	{
		lcd_4bit_send_char(&lcd_1,value);
		result = calculation(number1,number2,operation);
		lcd_4bit_send_number(&lcd_1,result);
	}

	while(1)
	{

		while(!KEYPAD_read(&keypad_1, &value));
		if('#' == value)
			lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
		else
		{
			operation = value;
			flag = 0;
			number1 = result;
			number2=0;
			lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
			lcd_4bit_send_string(&lcd_1,"answer");
			operation = value;
			lcd_4bit_send_char(&lcd_1,operation);

			for(i=0;i<4;i++)
			{
				while(!KEYPAD_read(&keypad_1,&value));

				if(value == '=')
				{
					lcd_4bit_send_char(&lcd_1,value);
					if(number2 == 0 && operation =='/')
					{
						lcd_4bit_send_string(&lcd_1,"Invalid");
						flag =1;
						break;
					}
					result = calculation(number1,number2,operation);
					lcd_4bit_send_number(&lcd_1,result);
					flag = 1;
					break;
				}
				else
				{
					number2 = number2*10+value-'0';
					lcd_4bit_send_char(&lcd_1,value);
				}
			}

			if(0 == flag)
			{
				lcd_4bit_send_char(&lcd_1,value);
				result = calculation(number1,number2,operation);
				lcd_4bit_send_number(&lcd_1,result);

			}

		}
	}
	return 0;
}
