/*
 * std_types.h
 *
 *  Created on: Jun 9, 2023
 *      Author: Walid Omar
 */

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

typedef signed char     sint8;
typedef signed short    sint16;
typedef  int    	    sint32;

typedef uint8			Std_ReturnType;

#define ERROR_OK		(Std_ReturnType)0x01
#define ERROR_NOT_OK	(Std_ReturnType)0x00
#define ERROR_NULL		(Std_ReturnType)0x00
#define NULL ((void *)0)
