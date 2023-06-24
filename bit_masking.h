/*
 * bit_masking.h
 *
 *  Created on: Jun 9, 2023
 *      Author: Walid Omar
 */

#ifndef BIT_MASKING_H_
#define BIT_MASKING_H_

/* Macros Declarations Function */
#define BIT_CLEAR(BIT_POSITION,REG)		(REG &= ~(1<<BIT_POSITION))
#define BIT_SET(BIT_POSITION,REG)		(REG |= (1<<BIT_POSITION))
#define BIT_TOGGLE(BIT_POSITION,REG)	(REG ^= (1<<BIT_POSITION))
#define BIT_READ(BIT_POSITION,REG)		((REG >> BIT_POSITION ) &1)

#endif /* BIT_MASKING_H_ */
