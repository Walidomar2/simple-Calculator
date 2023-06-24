/*
 * gpio.h
 *
 *  Created on: Jun 9, 2023
 *      Author: Walid Omar
 */

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

/* Macros Declarations */
#define MAX_PINS_NUMBER		8
#define PORTS_NUMBER		4

#define DIO_u8_PORT_OUTPUT	0xff
#define DIO_u8_PORT_INPUT 	0x00

#define DIO_u8_PORT_HIGH	0xff
#define DIO_u8_PORT_LOW		0x00

// Memory mapping

#define DIO_PORTA		(*((volatile uint8 *)0x3B))
#define DIO_DDRA		(*((volatile uint8 *)0x3A))
#define DIO_PINA		(*((volatile uint8 *)0x39))

#define DIO_PORTB		(*((volatile uint8 *)0x38))
#define DIO_DDRB		(*((volatile uint8 *)0x37))
#define DIO_PINB		(*((volatile uint8 *)0x36))

#define DIO_PORTC		(*((volatile uint8 *)0x35))
#define DIO_DDRC		(*((volatile uint8 *)0x34))
#define DIO_PINC		(*((volatile uint8 *)0x33))

#define DIO_PORTD		(*((volatile uint8 *)0x32))
#define DIO_DDRD		(*((volatile uint8 *)0x31))
#define DIO_PIND		(*((volatile uint8 *)0x30))


/* Data Types Declarations */

typedef enum{
	LOW = 0,
	HIGH

}logic_t;

typedef enum{
	PORTA_INDEX=0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}portIndex_t;

typedef enum
{
	PIN_0=0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
}pinIndex_t;

typedef enum
{
	INPUT=0,
	OUTPUT
}direction_t;

typedef struct
{
	portIndex_t	portSel;
	pinIndex_t	pinSel;
	direction_t	directionSel;

}pinConfig_t;

/* Functions Declarations */

Std_ReturnType DIO_pin_init(const pinConfig_t *pin_object);
Std_ReturnType DIO_pin_read(const pinConfig_t *pin_object ,logic_t *value);
Std_ReturnType DIO_pin_write(const pinConfig_t *pin_object,logic_t value);
Std_ReturnType DIO_pin_toggle(const pinConfig_t *pin_object);
Std_ReturnType DIO_pin_pull_up_active(const pinConfig_t *pin_object);
Std_ReturnType DIO_pin_pull_up_deactive(const pinConfig_t *pin_object);

Std_ReturnType DIO_port_init(portIndex_t port_object,direction_t direction);
Std_ReturnType DIO_port_read(portIndex_t port_object,uint8 *value);
Std_ReturnType DIO_port_write(portIndex_t port_object,uint8 value);
Std_ReturnType DIO_port_toggle(portIndex_t port_object);


#endif /* MCAL_GPIO_GPIO_H_ */
