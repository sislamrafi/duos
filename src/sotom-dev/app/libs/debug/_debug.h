#ifndef __LIBS_DEBUG_LINKER_H__
#define __LIBS_DEBUG_LINKER_H__


#include "../timer/timer.h"
#include "debug.h"

extern uint32_t STACK_START;

static uint32_t _LAST_RAM_USAGE_UPDATE = 0;

/* EXPORT VALUES */
volatile uint32_t CURRENT_MSP = 0;

extern uint16_t DEBUG_BUTTON;
extern uint16_t DEBUG_ANALOG_IO;

extern void SYS_DEBUG_ROUTINE(void);

#endif