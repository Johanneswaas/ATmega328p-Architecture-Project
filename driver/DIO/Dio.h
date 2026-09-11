/*============================================================================*
 * COPYRIGHT                                                                  *
 *                                                                            *
 * Copyright (c) 2026 waj42553. All rights reserved.                          *
 *============================================================================*/

/**
 *----------------------------------------------------------------------------*
 * @file Dio.h
 * @brief Public interface for the ATmega328P DIO driver.
 * @author waj42553
 * @date 2026-09-11
 * @version 0.1
 *----------------------------------------------------------------------------*/

/**
 * ================================ DIO DRIVER ===============================
 * @defgroup Dio DIO Driver
 * @{
 */

#ifndef DIO_H
#define DIO_H

/*----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 * Defines/Typedefs
 *---------------------------------------------------------------------------*/

typedef enum {
    DIO_PORT_B,
    DIO_PORT_C,
    DIO_PORT_D
} DIO_Port_t;

typedef uint8_t DIO_Pin_t;

typedef enum {
    DIO_INPUT,
    DIO_OUTPUT
} DIO_PinDir_t;

typedef enum {
    DIO_LOW,
    DIO_HIGH,
    DIO_ERROR
} DIO_ReturnPinState_t;

typedef enum {
    LOW, 
    HIGH
} DIO_PinState_t;

typedef enum {
    DIO_INIT_LOW,
    DIO_INIT_HIGH,
    DIO_INIT_PULLUP_OFF,
    DIO_INIT_PULLUP_ON
} DIO_PinInit_t;

typedef struct {
    DIO_Port_t DIOx;
    DIO_Pin_t Pin;
    DIO_PinDir_t dir;
    DIO_PinInit_t initialSetting;
} DIO_Cfg_t;

/*----------------------------------------------------------------------------
 * Global Variables
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

void Dio_Init(const DIO_Cfg_t* Cfg, uint8_t n);

DIO_ReturnPinState_t Dio_ReadPin(DIO_Port_t DIOx, DIO_Pin_t Pin);

void Dio_WritePin(DIO_Port_t DIOx, DIO_Pin_t Pin, DIO_PinState_t PinState);

#endif /* DIO_H */