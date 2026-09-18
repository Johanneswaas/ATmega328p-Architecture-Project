/*============================================================================*
 * COPYRIGHT                                                                  *
 *                                                                            *
 * Copyright (c) 2026 waj42553. All rights reserved.                          *
 *============================================================================*/

/**
 *----------------------------------------------------------------------------*
 * @file Event.h
 * @brief Public interface for the event middleware.
 * @author waj42553
 * @date 2026-09-18
 * @version 0.1
 *----------------------------------------------------------------------------*/

/**
 * ================================ EVENT ===================================
 * @defgroup Event Event Middleware
 * @{
 */

#ifndef EVENT_H
#define EVENT_H

/*----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 * Defines/Typedefs
 *---------------------------------------------------------------------------*/

/**
 * @brief Result returned when querying an event mask.
 */
typedef enum {
    SET,
    NOT_SET,
} EVENT_State_t;

/**
 * @brief Bit mask containing one or more pending events.
 */
typedef uint32_t EVENT_t;

/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

/**
 * @brief Marks one or more events as pending.
 *
 * @param[in] ev Event mask to set.
 */
void Event_Set(EVENT_t ev);

/**
 * @brief Clears one or more pending events.
 *
 * @param[in] ev Event mask to clear.
 */
void Event_Clear(EVENT_t ev);

/**
 * @brief Tests whether one or more events are pending.
 *
 * @param[in] ev Event mask to test.
 * @return SET if at least one event in @p ev is pending, otherwise NOT_SET.
 */
EVENT_State_t Event_IsSet(EVENT_t ev);

/**
 * @brief Returns a snapshot of all currently pending events.
 *
 * This function does not clear the returned events.
 *
 * @return Current pending-event mask.
 */
EVENT_t Event_Get(void);

#endif /* EVENT_H */
