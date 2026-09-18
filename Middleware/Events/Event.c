/*============================================================================*
 * COPYRIGHT                                                                  *
 *                                                                            *
 * Copyright (c) 2026 waj42553. All rights reserved.                          *
 *============================================================================*/

/**
 *----------------------------------------------------------------------------*
 * @file Event.c
 * @brief Event middleware implementation.
 * @author waj42553
 * @date 2026-09-18
 * @version 0.1
 *----------------------------------------------------------------------------*/

/**
 * ================================ EVENT ===================================
 * @ingroup Event
 * @addtogroup Event
 * @{
 */

/*----------------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------------*/

#include "Event.h"

/*----------------------------------------------------------------------------
 * Defines/Typedefs
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Prototypes
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Variables
 *---------------------------------------------------------------------------*/

static volatile EVENT_t events = 0;

/*----------------------------------------------------------------------------
 * Static/File-scope Variables (compilation unit)
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions
 *---------------------------------------------------------------------------*/

/**
 * @brief Sets one or more pending event flags.
 *
 * The bits set in @p ev are added to the pending event mask. Existing
 * pending events remain set.
 *
 * @param[in] ev Event mask to set.
 */
void Event_Set(EVENT_t ev)
{
    events |= ev;
}

/**
 * @brief Clears one or more pending event flags.
 *
 * The bits set in @p ev are removed from the pending event mask.
 *
 * @param[in] ev Event mask to clear.
 */
void Event_Clear(EVENT_t ev)
{
    events &= ~ev;
}

/**
 * @brief Checks whether one or more event flags are pending.
 *
 * @param[in] ev Event mask to check.
 * @return SET if at least one bit in @p ev is pending; otherwise NOT_SET.
 */
EVENT_State_t Event_IsSet(EVENT_t ev)
{
    return ((events & ev) != 0u) ? SET : NOT_SET;
}

/**
 * @brief Returns the current pending event mask.
 *
 * This function does not clear any pending events.
 *
 * @return Current event mask.
 */
EVENT_t Event_Get(void)
{
    return events;
}