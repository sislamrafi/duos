#include "../sys/cortex_m4_preps.h"

extern volatile uint32_t ms_count;
extern volatile uint32_t sys_tick_load_value_in_ms;

void sysTick_init(uint32_t);
void sysTick_enable(void);
void sysTick_disable(void);
uint32_t getSysTickCount(void);
void updateSysTick(uint32_t);
uint32_t getTime(void);
void delay(uint32_t);