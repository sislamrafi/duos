#include "../include/sys/sys.h"

/*
    ****************************SysTick Functions ***************************************
*/
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
    // kprintf("tick! %d\n", TICKCOUNT);
}
/*
    End of SysTick
*/

/*
    *********************** NVIC Functions ********************************
*/
uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

    if ((int32_t)(IRQn) >= 0)
    {
        return (NVIC->IP[((uint32_t)IRQn)] >> 4U);
    }
    else {
        if (IRQn == SysTick_IRQn) {
            return (SCB->SHPR3 >> 4 >> 24) & 0xF;
        }
        else if (IRQn = PendSV_IRQn) {
            return (SCB->SHPR3 >> 4 >> 16) & 0xF;
        }
        else if (IRQn = SVCall_IRQn) {
            return (SCB->SHPR2 >> 4 >> 24) & 0xF;
        }
        else if (IRQn = MemoryManagement_IRQn) {
            return (SCB->SHPR1 >> 4 >> 0) & 0xF;
        }
        else if (IRQn = BusFault_IRQn) {
            return (SCB->SHPR1 >> 4 >> 8) & 0xF;
        }
        else if (IRQn = UsageFault_IRQn) {
            return (SCB->SHPR1 >> 4 >> 16) & 0xF;
        }
        else
            return 0;
    }
}

void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    priority = priority & 0xF;
    if ((int32_t)(IRQn) >= 0)
    {
        NVIC->IP[((uint32_t)IRQn)] = (uint8_t)(priority << 4U);
    }
    else
    {
        if (IRQn == SysTick_IRQn) {
            SCB->SHPR3 &= ~((priority << 4U) << 24);
            SCB->SHPR3 |= (priority << 4U) << 24;
        }
        else if (IRQn = PendSV_IRQn) {
            SCB->SHPR3 &= ~((priority << 4U) << 16);
            SCB->SHPR3 |= (priority << 4U) << 16;
        }
        else if (IRQn = SVCall_IRQn) {
            SCB->SHPR2 &= ~((priority << 4U) << 24);
            SCB->SHPR2 |= (priority << 4U) << 24;
        }
        else if (IRQn = MemoryManagement_IRQn) {
            SCB->SHPR1 &= ~((priority << 4U) << 0);
            SCB->SHPR1 |= (priority << 4U) << 0;
        }
        else if (IRQn = BusFault_IRQn) {
            SCB->SHPR1 &= ~((priority << 4U) << 8);
            SCB->SHPR1 |= (priority << 4U) << 8;
        }
        else if (IRQn = UsageFault_IRQn) {
            SCB->SHPR1 &= ~((priority << 4U) << 16);
            SCB->SHPR1 |= (priority << 4U) << 16;
        }
    }
}

void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        NVIC->ISER[reg_pos] = (1UL << bit_pos);
    }
    else {
        if (IRQn == UsageFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr |= 1 << 18;
            SCB->SHCSR = shcsr;
        }
        else if (IRQn == BusFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr |= 1 << 17;
            SCB->SHCSR = shcsr;
        }
        else if (IRQn == MemoryManagement_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr |= 1 << 16;
            SCB->SHCSR = shcsr;
        }
    }
}

void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        NVIC->ICER[reg_pos] = (1UL << bit_pos);
    }
    else {
        if (IRQn == UsageFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr &= ~(1 << 18);
            SCB->SHCSR = shcsr;
        }
        else if (IRQn == BusFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr &= ~(1 << 17);
            SCB->SHCSR = shcsr;
        }
        else if (IRQn == MemoryManagement_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            shcsr &= ~(1 << 16);
            SCB->SHCSR = shcsr;
        }
    }

}

uint32_t __NVIC_getStatus(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        return ((NVIC->ISER[reg_pos] >> bit_pos) & 0x1);
    }
    else {
        if (IRQn == UsageFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            return (shcsr >> 18) & 0x1;
        }
        else if (IRQn == BusFault_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            return (shcsr >> 17) & 0x1;
        }
        else if (IRQn == MemoryManagement_IRQn) {
            uint32_t shcsr = SCB->SHCSR;
            return (shcsr >> 16) & 0x1;
        }
        else return 0;
    }
}

void __disable_irq(void) {
    __set_PRIMASK(1);
}

void __enable_irq(void) {
    __set_PRIMASK(0);
}

void __set_PRIMASK(uint32_t value) {
    value = value & 0x1;
    __asm volatile ("MSR primask, %0" : : "r" (value));
}

uint32_t __get_PRIMASK(void) {
    uint32_t value = 0;
    __asm volatile ("MRS %0, primask" : "=r" (value));
    return value;
}

void __set_BASEPRI(uint32_t value) {
    value = value & 0xF;
    __asm volatile ("MSR basepri, %0" : : "r" (value));
}

void __unset_BASEPRI(void) {
    uint32_t value = 0x0;
    __asm volatile ("MSR basepri, %0" : : "r" (value));
}

uint32_t __get_BASEPRI(void) {
    uint32_t value = 0;
    __asm volatile ("MRS %0, basepri" : "=r" (value));
    return value;
}

void __set_FAULTMASK(uint32_t value) {
    value = value & 0x1;
    __asm volatile ("MSR faultmask, %0" : : "r" (value));
}

void __enable_fault_irq(void) {
    __asm volatile ("CPSIE F");
}

void __disable_fault_irq(void) {
    __asm volatile ("CPSID F");
}

void __set_pending_IRQn(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        NVIC->ISPR[reg_pos] |= (1UL << bit_pos);
    }
    else {
        if (IRQn == NonMaskableInt_IRQn) {
            SCB->ICSR |= 1 << 31;
        }
        else if (IRQn == PendSV_IRQn) {
            SCB->ICSR |= 1 << 28;
        }
        else if (IRQn == SysTick_IRQn) {
            SCB->ICSR |= 1 << 26;
        }
    }
}

void __clear_pending_IRQn(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        NVIC->ICPR[reg_pos] |= (1UL << bit_pos);
    }
    else {
        if (IRQn == PendSV_IRQn) {
            SCB->ICSR |= 1 << 27;
        }
        else if (IRQn == SysTick_IRQn) {
            SCB->ICSR |= 1 << 25;
        }
    }
}

uint32_t __get_pending_IRQn(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        return ((NVIC->ISPR[reg_pos] >> bit_pos) & 0x1);
    }
    else {
        if (IRQn == PendSV_IRQn) {
            return (SCB->ICSR >> 28) & 0x1;
        }
        else if (IRQn == SysTick_IRQn) {
            return (SCB->ICSR >> 26) & 0x1;
        }
        else if (IRQn == UsageFault_IRQn) {
            return (SCB->SHCSR >> 12) & 0x1;
        }
        else if (IRQn == MemoryManagement_IRQn) {
            return (SCB->SHCSR >> 13) & 0x1;
        }
        else if (IRQn == BusFault_IRQn) {
            return (SCB->SHCSR >> 14) & 0x1;
        }
        else if (IRQn == SVCall_IRQn) {
            return (SCB->SHCSR >> 15) & 0x1;
        }
        else {
            return 0;
        }
    }
}

uint32_t __get_active_IRQn(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0)
    {
        uint32_t reg_pos = (((uint32_t)IRQn) >> 5UL);
        uint32_t bit_pos = (((uint32_t)IRQn) & 0x1FUL);
        return ((NVIC->IABR[reg_pos] >> bit_pos) & 0x1);
    }
    else {
        if (IRQn == MemoryManagement_IRQn) {
            return (SCB->SHCSR >> 0) & 0x1;
        }
        else if (IRQn == BusFault_IRQn) {
            return (SCB->SHCSR >> 1) & 0x1;
        }
        else if (IRQn == UsageFault_IRQn) {
            return (SCB->SHCSR >> 3) & 0x1;
        }
        else if (IRQn == SVCall_IRQn) {
            return (SCB->SHCSR >> 7) & 0x1;
        }
        else if (IRQn == DebugMonitor_IRQn) {
            return (SCB->SHCSR >> 8) & 0x1;
        }
        else if (IRQn == PendSV_IRQn) {
            return (SCB->SHCSR >> 10) & 0x1;
        }
        else if (IRQn == SysTick_IRQn) {
            return (SCB->SHCSR >> 11) & 0x1;
        }
        else {
            return 0;
        }
    }
}


/*
void __set_BASEPRI(uint32_t value) {
    register uint32_t __basepri __ASM("basepri");
    __basepri = value;
}

void __unset_BASEPRI() {
    register uint32_t __basepri __ASM("basepri");
    __basepri = 0x0;
}

uint32_t __get_BASEPRI(void) {
    register uint32_t __basepri __ASM("basepri");
    return __basepri;
}
*/

// System Reset Request (to be tested)
void __system_reset(void) {
    // write 0x5FA to VECTKEY, otherwise the write is ignored
    SCB->AIRCR &= ~(0xFFFF << 16);
    SCB->AIRCR |= (0x5FA << 16);
    SCB->AIRCR |= (0x1 << 2); // Write 1 to asserts a signal to the outer system that requests a reset.
}

// activate FPU
void DRV_FPU_ACTIVE(void) {
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
}