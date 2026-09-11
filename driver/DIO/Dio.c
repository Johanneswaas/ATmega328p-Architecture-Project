/*============================================================================*
 * COPYRIGHT                                                                  *
 *                                                                            *
 * Copyright (c) 2026 waj42553. All rights reserved.                          *
 *============================================================================*/

/**
 *----------------------------------------------------------------------------*
 * @file Dio.c
 * @brief ATmega328P DIO driver implementation.
 * @author waj42553
 * @date 2026-09-11
 * @version 0.1
 *----------------------------------------------------------------------------*/

/**
 * ================================ DIO DRIVER ===============================
 * @ingroup Dio
 * @addtogroup Dio
 * @{
 */

/*----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/

#include <avr/io.h>

#include "Dio.h"

/*----------------------------------------------------------------------------
 * Defines/Typedefs
 *---------------------------------------------------------------------------*/

typedef struct {
    volatile uint8_t* ddr;
    volatile uint8_t* port;
    volatile uint8_t* pin;
} DIO_PortRegs_t;

/*----------------------------------------------------------------------------
 * Static Function Prototypes
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Variables
 *---------------------------------------------------------------------------*/

static const DIO_PortRegs_t DioPortRegs[] = {
    [DIO_PORT_B] = {&DDRB, &PORTB, &PINB},
    [DIO_PORT_C] = {&DDRC, &PORTC, &PINC},
    [DIO_PORT_D] = {&DDRD, &PORTD, &PIND},
};

/*----------------------------------------------------------------------------
 * Static/File-scope Variables (compilation unit)
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

/**
 * @brief Initializes the configured ATmega328P digital I/O pins.
 *
 * Configures each pin as an input or output and applies its initial setting.
 * Output pins are initialized LOW unless @p initialSetting is
 * DIO_INIT_HIGH. Input pins have the internal pull-up enabled only when
 * @p initialSetting is DIO_INIT_PULLUP_ON.
 *
 * @param[in] Cfg Pointer to the pin configuration array.
 * @param[in] n Number of entries in @p Cfg.
 */
void Dio_Init(const DIO_Cfg_t* Cfg, uint8_t n)
{
    for (uint8_t i = 0; i < n; i++)
    {
        DIO_Port_t DIOx = Cfg[i].DIOx;
        DIO_Pin_t Pin = Cfg[i].Pin;
        DIO_PinInit_t initialSetting = Cfg[i].initialSetting;
        DIO_PinDir_t dir = Cfg[i].dir;
    
        if ((Pin >= 8)|| (DIOx < DIO_PORT_B) || (DIOx > DIO_PORT_D)) continue;

        const DIO_PortRegs_t* regs = &DioPortRegs[DIOx]; 

        uint8_t mask = (uint8_t)(1u << Pin);

        if (dir == DIO_OUTPUT)
        {
            if (initialSetting == DIO_INIT_HIGH)
            {
                *regs->port |= mask;
                *regs->ddr |= mask;
            }
            else
            {
                *regs->port &= ~mask;
                *regs->ddr |= mask;
            }
        }
        else if (dir == DIO_INPUT)
        {
            if (initialSetting == DIO_INIT_PULLUP_ON) 
            {
                *regs->port |= mask;
                *regs->ddr &= ~mask;
            } 
            else 
            {
                *regs->port &= ~mask;
                *regs->ddr &= ~mask;
            }
        }
    }
}

/**
 * @brief Reads the current logic level of an ATmega328P digital input pin.
 *
 * The function reads the selected PINx register and returns HIGH or LOW.
 * An invalid pin number returns ERROR.
 *
 * @param[in] DIOx Port containing the pin to read.
 * @param[in] Pin Pin number to read, from 0 to 7.
 * @return HIGH if the pin is logic high, LOW if the pin is logic low, or
 *         ERROR if @p Pin is outside the valid range.
 */
DIO_ReturnPinState_t Dio_ReadPin(DIO_Port_t DIOx, DIO_Pin_t Pin)
{
    DIO_ReturnPinState_t state = DIO_ERROR;

    if (Pin < 8 && (DIOx >= DIO_PORT_B) && (DIOx <= DIO_PORT_D))
    {
        uint8_t mask = (uint8_t)(1u << Pin);
        const DIO_PortRegs_t* reg = &DioPortRegs[DIOx];
        state = (*reg->pin & mask)? DIO_HIGH : DIO_LOW;
    }
    
    return state;
}

/**
 * @brief Writes a logic level to a configured digital output pin.
 *
 * The function changes the PORTx latch only when the selected pin is
 * currently configured as an output. Input pins, invalid ports, invalid pin
 * numbers, and ERROR states are ignored.
 *
 * @param[in] DIOx Port containing the pin to write.
 * @param[in] Pin Pin number to write, from 0 to 7.
 * @param[in] PinState Logic level to write, either LOW or HIGH.
 */
void Dio_WritePin(DIO_Port_t DIOx, DIO_Pin_t Pin, DIO_PinState_t PinState)
{
    if ((Pin < 8u) && (DIOx >= DIO_PORT_B) && (DIOx <= DIO_PORT_D))
    {
        const DIO_PortRegs_t* reg = &DioPortRegs[DIOx];
        
        uint8_t mask = (uint8_t)(1u << Pin);
    
        if (*reg->ddr & mask)
        {
            if (PinState == LOW) 
            {
                *reg->port &= (uint8_t)~mask;
            }
            else if (PinState == HIGH)
            {
                *reg->port |= mask;
            }
        }
    }
}