/*============================================================================*
 * COPYRIGHT                                                                  *
 *                                                                            *
 * Copyright (c) 2026 waj42553. All rights reserved.                          *
 *============================================================================*/

/**
 *----------------------------------------------------------------------------*
 * @file Usart.c
 * @brief ATmega328P USART driver implementation.
 * @author waj42553
 * @date 2026-09-12
 * @version 0.1
 *----------------------------------------------------------------------------*/

/**
 * =============================== USART DRIVER =============================
 * @ingroup Usart
 * @addtogroup Usart
 * @{
 */

/*----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Usart.h"
#include "Event.h"

/*----------------------------------------------------------------------------
 * Defines/Typedefs
 *---------------------------------------------------------------------------*/

#define USART_RX_BUFFER_INDEX(X) ((X) % 32u)

#define XON 17
#define XOFF 19

#define USART_BUFFER_HIGH_MARK 24
#define USART_BUFFER_LOW_MARK 8

/*----------------------------------------------------------------------------
 * Static Function Prototypes
 *---------------------------------------------------------------------------*/

uint8_t USART_BufferSize();

/*----------------------------------------------------------------------------
 * Global Variables
 *---------------------------------------------------------------------------*/

volatile uint8_t USART_Buffer[32];
volatile uint8_t USART_Buffer_HeadPtr;
volatile uint8_t USART_Buffer_TailPtr;
volatile uint8_t USART_Buffer_MARK;

/*----------------------------------------------------------------------------
 * Static/File-scope Variables (compilation unit)
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * ISRs
 *---------------------------------------------------------------------------*/

ISR(USART_RX_vect)
{
    uint8_t received = UDR0;
    if (USART_RX_BUFFER_INDEX(USART_Buffer_TailPtr + 1) != USART_RX_BUFFER_INDEX(USART_Buffer_HeadPtr))
    {
        if (USART_BufferSize() > USART_BUFFER_HIGH_MARK)
        {
            EVENT_Set(EVENT_USART_TX_XOFF);
        }
        USART_Buffer[USART_Buffer_TailPtr] = received;
        
        USART_Buffer_TailPtr = USART_RX_BUFFER_INDEX(USART_Buffer_TailPtr + 1);
    }
}

/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

 uint8_t USART_BufferSize()
{
    uint8_t size_ePtr = USART_RX_BUFFER_INDEX(USART_Buffer_TailPtr);
    uint8_t size_sPtr = USART_RX_BUFFER_INDEX(USART_Buffer_HeadPtr);
    return (size_ePtr >= size_sPtr)? size_ePtr - size_sPtr : 32 - (size_sPtr - size_ePtr);
}