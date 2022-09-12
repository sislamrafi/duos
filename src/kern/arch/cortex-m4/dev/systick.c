#include "../include/dev/systick.h"
#include "../../../include/kstdio.h"

volatile uint32_t MSCOUNT = 0;
volatile uint32_t TICKCOUNT = 0;


void sysTick_enable(void) {
    SysTick->CTRL |= (1 << 0);
}

void sysTick_disable(void) {
    SysTick->CTRL &= ~(1 << 0);
}
void sysTick_init(uint32_t tick_time) {
    SysTick->CTRL &= ~(1 << 0);     // Disable SysTick Counter
    SysTick->VAL = 0;               // Set the value of systick to 0
    SysTick->LOAD = 22500U * tick_time - 1;    // AHB/8 = 22.5 MHz; 1ms requires 22500 clock cycles
    MSCOUNT = 0;
    TICKCOUNT = 0;
    SysTick->CTRL &= ~(1 << 2);     // Set clocksource to AHB/8
    SysTick->CTRL |= (1 << 1);     // Enable SysTick Interrupt
    SysTick->CTRL |= (1 << 0);     // Enable SysTick Counter
}

uint32_t getSysTickCount(void)
{
    return SysTick->VAL;
}

void updateSysTick(uint32_t tick_time) {
    SysTick->CTRL &= ~(1 << 0);     // Disable SysTick Counter
    SysTick->VAL = 0;               // Set the value of systick to 0
    SysTick->LOAD = 22500 * tick_time - 1;     // AHB/8 = 22.5 MHz; 1ms requires 22500 clock cycles
    SysTick->CTRL |= (1 << 0);     // Enable SysTick Counter
}

uint32_t getTime(void) {
    uint32_t tick_elapsed = SysTick->LOAD - SysTick->VAL;
    return MSCOUNT + (tick_elapsed / 22500);
}

void delay(uint32_t dly)
{
    uint32_t t_target = getTime() + dly;
    while (t_target > getTime())
        ;
}

void SysTick_Handler() {
    MSCOUNT += ((SysTick->LOAD + 1) / 22500);
    TICKCOUNT++;
    // kprintf("tick=%d ms=%d\n", TICKCOUNT, MSCOUNT);
}