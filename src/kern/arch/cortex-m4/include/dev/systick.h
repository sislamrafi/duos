#include "../sys/cortex_m4_preps.h"

extern volatile uint32_t MSCOUNT;
extern volatile uint32_t TICKCOUNT;

void sysTick_init(uint32_t);
void sysTick_enable(void);
void sysTick_disable(void);
uint32_t getSysTickCount(void);
void updateSysTick(uint32_t);
uint32_t getTime(void);
void delay(uint32_t);