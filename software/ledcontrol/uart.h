#ifndef UART_H_
#define UART_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifdef __AVR_ATmega8__
#define UART_CTRL_A			UCSRA
#define UART_CTRL_B			UCSRB
#define UART_DATA			UDR
#define RX_ENABLE			RXEN
#define TX_ENABLE			TXEN
#define RXCI_ENABLE			RXCIE
#define UDRI_ENABLE			UDRIE
#define UART_2X				U2X
#define RXC_ISR				USART_RXC_vect
#define UDRE_ISR			USART_UDRE_vect
#define UART_BAUDH			UBRRH
#define UART_BAUDL			UBRRL
#else
#ifdef __AVR_ATmega1284P__
#define UART_CTRL_A			UCSR0A
#define UART_CTRL_B			UCSR0B
#define UART_DATA			UDR0
#define RX_ENABLE			RXEN0
#define TX_ENABLE			TXEN0
#define RXCI_ENABLE			RXCIE0
#define UDRI_ENABLE			UDRIE0
#define UART_2X				U2X0
#define RXC_ISR				USART0_RX_vect
#define UDRE_ISR			USART0_UDRE_vect
#define UART_BAUDH			UBRR0H
#define UART_BAUDL			UBRR0L
#endif
#endif

#define BAUD				38400

/** Size of the UART transmit buffer. Must be a power of 2 */
#define UART_TX_BUFFER_SIZE		16
#define UART_TX_SIZE_MASK		(UART_TX_BUFFER_SIZE-1)
/** Size of the UART receive buffer. Must be a power of 2 */
#define UART_RX_BUFFER_SIZE		16
#define UART_RX_SIZE_MASK		(UART_RX_BUFFER_SIZE-1)

/** UART buffer struct */
struct {
	/** Data to be transmitted will be stored here */
	uint8_t TXBuffer[UART_TX_BUFFER_SIZE];
	/** Received data will be stored here */
	uint8_t RXBuffer[UART_RX_BUFFER_SIZE];
	/** Write position of the transmit ring buffer */
	uint8_t txWritePtr;
	/** Read position of the transmit ring buffer */
	volatile uint8_t txReadPtr;
	/** Write position of the receive ring buffer */
	volatile uint8_t rxWritePtr;
	/** Read position of the receive ring buffer */
	uint8_t rxReadPtr;
} uart;

/**
 * \brief Initializes UART module.
 */
void uart_Init();

/**
 * \brief Retrieves a byte from the receive buffer.
 *
 * \param b Pointer to where the byte will be stored
 * \return 1 if data has been received, 0 if not
 */
uint8_t uart_getByte(uint8_t *b);

/**
 * \brief Adds a byte to the transmit buffer.
 *
 * This function blocks until there is space in the buffer.
 * \param b Byte to be transmitted
 */
void uart_sendByte(uint8_t b);

/**
 * \brief Sends a string to the transmit buffer
 *
 * This function blocks until there is space in the buffer.
 * \param s Pointer to a null terminated string
 */
void uart_sendString(const char *s);

/**
 * \brief Sends a string from FLASH
 *
 * Like uart_sendString() but expects a pointer to a FLASH string
 */
void uart_sendString_P(const char *s);

void uart_sendValue(int16_t val, uint8_t base);

void uart_sendUnsignedValue(uint16_t val, uint8_t base);

ISR(USART0_RX_vect);

ISR(USART0_UDRE_vect);

#endif
