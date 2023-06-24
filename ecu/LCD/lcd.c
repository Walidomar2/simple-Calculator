/*
 * lcd.c
 *
 *  Created on: Jun 11, 2023
 *      Author: Walid Omar
 */

#include <util/delay.h>

#include "../../std_types.h"
#include "../../bit_masking.h"
#include "lcd.h"

static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd, uint8 data_command)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		uint8 counter=0;
		for(counter=0;counter<4;counter++)
		{
			retValue = DIO_pin_write(&(lcd->lcd_data[counter]),(data_command >> counter )&(uint8)0x01);
		}
	}
	return retValue;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		retValue = DIO_pin_write(&lcd->EN, HIGH);
		_delay_us(5);
		retValue = DIO_pin_write(&lcd->EN, LOW);
		_delay_us(5);
	}
	return retValue;
}

/****************************************************************************************************************************************/

Std_ReturnType lcd_4bit_init(const lcd_4bit_t *lcd)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		uint8 counter=0;
		retValue = DIO_pin_init(&lcd->RS);
		retValue = DIO_pin_init(&lcd->EN);

		for(counter=0;counter<4;counter++)
		{
			retValue = DIO_pin_init(&lcd->lcd_data[counter]);
		}

	    _delay_ms(20);
		retValue = lcd_4bit_send_command(lcd, 0x33);
		_delay_ms(5);
		retValue = lcd_4bit_send_command(lcd, 0x32);
		_delay_us(150);
		retValue = lcd_4bit_send_command(lcd, 0x28);

		retValue = lcd_4bit_send_command(lcd, _LCD_CLEAR);
		retValue = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
		retValue = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_SET_INC_SHIFT_OFF);
		retValue = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_CURSOR_OFF);
		//retValue = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINES);
		retValue = lcd_4bit_send_command(lcd, 0x80);

		_delay_ms(5);
	}
		return retValue;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd ,uint8 command)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		retValue = DIO_pin_write(&lcd->RS, LOW);
		retValue = lcd_send_4bit(lcd, command >> 4);
		retValue = lcd_4bit_send_enable_signal(lcd);
		retValue = lcd_send_4bit(lcd, command);
		retValue = lcd_4bit_send_enable_signal(lcd);
	}
	return retValue;
}

Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd ,uint8 data)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		retValue = DIO_pin_write(&lcd->RS, HIGH);
		retValue = lcd_send_4bit(lcd, data >> 4);
		retValue = lcd_4bit_send_enable_signal(lcd);
		retValue = lcd_send_4bit(lcd, data);
		retValue = lcd_4bit_send_enable_signal(lcd);

	}
	return retValue;
}

Std_ReturnType lcd_4bit_send_char_at_pos(const lcd_4bit_t *lcd ,uint8 data,uint8 row,uint8 column)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		switch(row)
		{
		case ROW1:{lcd_4bit_send_command(lcd,(0x80 + column-1)); break;}
		case ROW2:{lcd_4bit_send_command(lcd,(0xC0 + column-1)); break;}
		case ROW3:{lcd_4bit_send_command(lcd,(0x94 + column-1)); break;}
		case ROW4:{lcd_4bit_send_command(lcd,(0xD4 + column-1)); break;}
		}

		retValue = lcd_4bit_send_char(lcd, data);
	}
	return retValue;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd ,uint8 *str)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		while(*str)
		{
			retValue = lcd_4bit_send_char(lcd,*str++);
		}
	}
	return retValue;
}

Std_ReturnType lcd_4bit_send_string_at_pos(const lcd_4bit_t *lcd ,uint8 *str,uint8 row,uint8 column)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL || str == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		switch(row)
		{
		case ROW1:{lcd_4bit_send_command(lcd,(0x80 + column-1)); break;}
		case ROW2:{lcd_4bit_send_command(lcd,(0xC0 + column-1)); break;}
		case ROW3:{lcd_4bit_send_command(lcd,(0x94 + column-1)); break;}
		case ROW4:{lcd_4bit_send_command(lcd,(0xD4 + column-1)); break;}
		}
		retValue = lcd_4bit_send_string(lcd, str);

	}
	return retValue;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos)
{
	Std_ReturnType retValue= ERROR_NOT_OK;

	if(lcd == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		uint8 counter=0;

		retValue = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START +(mem_pos+8)));

		for(counter=0;counter<=7;counter++)
		{
			lcd_4bit_send_char(lcd, chr[counter]);
		}

		retValue = lcd_4bit_send_char_at_pos(lcd,mem_pos, row, column);
	}

	return retValue;
}

Std_ReturnType lcd_4bit_send_number(const lcd_4bit_t *lcd,sint32 num)
{
		Std_ReturnType retValue=ERROR_NOT_OK;
		if(lcd == NULL)
			retValue = ERROR_NULL;
		else
		{
			uint8 str[10],i=0,j;
			if (num==0)
			{
				lcd_4bit_send_char(lcd,'0');
				retValue =ERROR_OK;
				return retValue;
			}
			if (num<0)
			{
				num=num*(-1);
				lcd_4bit_send_char(lcd,'-');
			}
			while (num)
			{
				str[i]=num%10+'0';
				i++;
				num=num/10;
			}
			for (j=i;j>0;j--)
			{
				lcd_4bit_send_char(lcd,str[j-1]);
			}
			retValue =ERROR_OK;
		}
		return retValue;
}


/*Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str)
{
	Std_ReturnType retValue = ERROR_NOT_OK;
	if(str == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		 memset((uint8 *)str, '\0', 4);
		 sprintf(str, "%i", value);
	}
	return retValue;
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
	Std_ReturnType retValue = ERROR_NOT_OK;
	if(str == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		memset((uint8 *)str, '\0',5);
		sprintf(str, "%i", value);
	}
	return retValue;
}
*/

/*Std_ReturnType convert_uint32_to_string(int value, char *str)
{
	Std_ReturnType retValue = ERROR_NOT_OK;
	if(str == NULL)
	{
		retValue= ERROR_NULL;
	}
	else
	{
		memset((char *)str, '\0',11);
		sprintf(str,"%d", value);
	}
	return retValue;
}*/

