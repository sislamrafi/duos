#include "../include/dev/systick.h"

void DRV_SYSTICK_INIT()
{
    STK->CTRL |= (1 << 0); // Enable systick

    STK->CTRL |= (1 << 1); //Set TICKINIT value, interrupt

    /*
    Set clock source to AHB/8
    if the clock source is 180MHz then Systick
    clock is 22.5MHz
    */
    STK->CTRL &= ~(1 << 2);

    /*
    Set load reg value
    */
    STK->LOAD = 11250000;

    //clear current systick val
    STK->VAL = 0;

    __NVIC_EnableIRQ(SysTick_IRQn);
}