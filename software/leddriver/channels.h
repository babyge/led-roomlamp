/**
 * \file
 * \brief Defines and routines for accessing the auxiliary channels
 */
#ifndef CHANNELS_H_
#define CHANNELS_H_

#include <avr/io.h>
#include <util/delay.h>

#define CH1_SOFTUART	0

/**
 * \name Port defines for the three auxiliary channels
 * @{
 */
#define CH1_DDR			DDRA
#define CH1_PIN			PINA
#define CH1_PORT		PORTA
#define CH1_BIT			PA2

#define CH2_DDR			DDRA
#define CH2_PIN			PINA
#define CH2_PORT		PORTA
#define CH2_BIT			PA1

#define CH3_DDR			DDRB
#define CH3_PIN			PINB
#define CH3_PORT		PORTB
#define CH3_BIT			PB2
/** @} */

/**
 * \name Turn on/off macros for auxiliary channels
 * @{
 */
#define CH1_On()		CH1_PORT |= (1<<CH1_BIT)
#define CH1_Off()		CH1_PORT &= ~(1<<CH1_BIT)
#define CH1_Toggle()	CH1_PIN |= (1<<CH1_BIT)

#define CH2_On()		CH2_PORT |= (1<<CH2_BIT)
#define CH2_Off()		CH2_PORT &= ~(1<<CH2_BIT)
#define CH2_Toggle()	CH2_PIN |= (1<<CH2_BIT)

#define CH3_On()		CH3_PORT |= (1<<CH3_BIT)
#define CH3_Off()		CH3_PORT &= ~(1<<CH3_BIT)
#define CH3_Toggle()	CH3_PIN |= (1<<CH3_BIT)
/** @} */

/**
 * \brief Initializes the control pins for the external channels
 */
void channels_Init(void);

#if CH1_SOFTUART
void CH1_SendString(uint8_t *s);

void CH1_SendChar(uint8_t c);
#endif

#endif
