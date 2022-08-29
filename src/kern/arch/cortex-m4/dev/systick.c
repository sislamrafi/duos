#include "../include/dev/systick.h"

volatile uint32_t ms_count = 0;
volatile uint32_t sys_tick_load_value_in_ms = 0;

void sysTick_enable()
{
    if (STK->CTRL & 0b1 == 0)
        ms_count = 0;
    else
        STK->CTRL |= (1 << 0); // Enable systick
}

void sysTick_disable()
{
    STK->CTRL &= ~(1 << 0); // disable systick
}

void sysTick_init(uint32_t time_in_ms)
{
    // disable systick
    sysTick_disable();

    // clear current systick val
    STK->VAL = 0;

    // Set TICKINIT value, interrupt
    STK->CTRL |= (1 << 1);

    /*
    Set clock source to AHB/8
    if the clock source is 180MHz then Systick
    clock is 22.5MHz
    */
    STK->CTRL &= ~(1 << 2);

    // Set load reg value
    STK->LOAD = (180000000U / 8U) / 1000U * time_in_ms;
    sys_tick_load_value_in_ms = time_in_ms;

    // enable systick
    sysTick_enable();

    __NVIC_EnableIRQ(SysTick_IRQn);
}

uint32_t getSysTickCount(void)
{
    return STK->VAL;
}

void updateSysTick(uint32_t time_in_ms)
{
    // disable systick
    sysTick_disable();
    // Set load reg value
    STK->LOAD = (180000000U / 8U) / 1000U * time_in_ms;
    sys_tick_load_value_in_ms = time_in_ms;
    // enable systick
    sysTick_enable();
}

uint32_t getTime(void)
{
    return sys_tick_load_value_in_ms * ms_count + (sys_tick_load_value_in_ms / STK->LOAD * STK->VAL);
}

void delay(uint32_t dly)
{
    uint32_t t_target = getTime() + dly;
    while (t_target > getTime())
        ;
}

void SysTick_Handler(void)
{

    // uint32_t *pICSR = (uint32_t*)0xE000ED04;

    ms_count++;

    // unblock_tasks();

    // pend the pendsv exception
    //*pICSR |= ( 1 << 28);

    // removes the pendsv exception
    //*pICSR |= ( 1 << 27);
}