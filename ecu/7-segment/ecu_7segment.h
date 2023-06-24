/*
 * ecu_7segment.h
 *
 *  Created on: Jun 10, 2023
 *      Author: Walid Omar
 */

#ifndef ECU_7_SEGMENT_ECU_7SEGMENT_H_
#define ECU_7_SEGMENT_ECU_7SEGMENT_H_

typedef enum
{
	COMMON_ANODE=0,
	COMMON_CATHOD
}type_t;

typedef struct
{
	portIndex_t	Copy_uSSDPort;
	type_t		Copy_u8SSDType:1;
	//uint8		Copy_u8Number;

}SSD_t;

Std_ReturnType SSD_init(const SSD_t *ssd_object);
Std_ReturnType SSD_setNumber(const SSD_t *ssd_object,uint8 value);

#endif /* ECU_7_SEGMENT_ECU_7SEGMENT_H_ */
