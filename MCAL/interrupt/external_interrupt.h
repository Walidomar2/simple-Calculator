/*
 * external_interrupt.h
 *
 *  Created on: Jun 14, 2023
 *      Author: Walid Omar
 */

#ifndef MCAL_INTERRUPT_EXTERNAL_INTERRUPT_H_
#define MCAL_INTERRUPT_EXTERNAL_INTERRUPT_H_


/* Macros declarations */

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)
#define  GLOBAL_INTE_ENABLE()   sei()
#define  GLOBAL_INTE_DISABLE()	cli()


#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))

#define ISR(vector,...) \
	void vector(void) __attribute__((signal))__VA_ARGS__; \
	void vector(void)


#define GICR_REG		    (*(volatile uint8*) 0x5B)
#define INT0				6
#define INT1				7
#define INT2				5

#define GIFR_REG			(*(volatile uint8*)0x5A)
#define INTF0				6
#define INTF1				7
#define INTF2				5


#define MCUCR_REG			(*(volatile uint8*)0x55)
#define ISC00				0
#define ISC01				1
#define	ISC10				2
#define ISC11				3

#define MCUCSR_REG			(*(volatile uint8*)0x55)
#define ISC2				6


#define INT0_VECTOR			__vector_1
#define INT1_VECTOR			__vector_2
#define INT2_VECTOR			__vector_3

/* Data types Declarations*/

typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_type;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;



/*Functions declaration*/
Std_ReturnType EXT_Enable(ExInterruptSource_type interrupt,TriggerEdge_type edge);
Std_ReturnType EXT_Disable(ExInterruptSource_type interrupt);
Std_ReturnType SET_CallBack(ExInterruptSource_type interrupt,void(*callback_Func)(void));

#endif /* MCAL_INTERRUPT_EXTERNAL_INTERRUPT_H_ */
