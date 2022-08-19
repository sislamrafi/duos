#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include "../../../../kern/arch/stm32f446re/include/sys/stm32_peps.h"
#include "../../../../kern/arch/cortex-m4/include/sys/cortex_m4_preps.h"

#include "../debug/debug.h"

#define TIM2_CLOCK_SPEED 90000000U
#define TIM2_PSC 90U
#define TIM2_TICK_TIME (uint32_t)(TIM2_CLOCK_SPEED/TIM2_PSC)
#define TIM2_TICK_TIME_MS_DIV (uint32_t)((TIM2_TICK_TIME)/1000U)
#define TIM2_TICK_TIME_US_DIV (uint32_t)((TIM2_TICK_TIME)/1000000U)
#define TIM2_ARR (uint32_t)1000U // 1ms //max: 0xffffffff - 1

extern void SYS_DEBUG_ROUTINE(void);
extern void TIM2_IRQHandler(void);

void ConfigTimer2ForSotom(void);
void Delay(uint32_t delay); // milisecond
void Delay_micro_second(uint32_t delay);
uint32_t getMiliseconds(); // can track upto 71days
uint32_t getMicroseconds(); // upto 1 hour 12 min

#endif
