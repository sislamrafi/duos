#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/cortex-m4/include/sys/cortex_m4_preps.h"
#include <stdint.h>

void __systickTest(void);
void __interruptTest(void);

void kmain(void)
{
	__sys_init();


	kprintf("Booting OS CSE: Version: 1.0, Time:%d\r\n\r", getTime());
	kprintf("Wellcome ....\r\n\r");
	kprintf("\nCSEOS is ready to take input:\r\n");

	delay(2000);

	__interruptTest();

}



void __interruptTest() {
	int priority = 0;
	int status = 0;
	__NVIC_EnableIRQ(USART1_IRQn);
	__NVIC_SetPriority(USART1_IRQn, 10);
	kprintf("USART1 Interrupt enabled\n");
	priority = __NVIC_GetPriority(USART1_IRQn);
	kprintf("USART1 Priority = %d\n", priority);
	__NVIC_EnableIRQ(USART2_IRQn);
	__NVIC_SetPriority(USART2_IRQn, 11);
	kprintf("USART2 Interrupt enabled\n");
	priority = __NVIC_GetPriority(USART2_IRQn);
	kprintf("USART2 Priority = %d\n", priority);
	__NVIC_EnableIRQ(TIM2_IRQn);
	__NVIC_SetPriority(TIM2_IRQn, 12);
	kprintf("TIMER2 Interrupt enabled\n");
	priority = __NVIC_GetPriority(TIM2_IRQn);
	kprintf("Timer2 Priority = %d\n", priority);

	status = __NVIC_getStatus(USART2_IRQn);
	kprintf("Usart2 irq status: %d\n", status);
	delay(1000);

	NVIC->ISER[1] = 0xFF;
	kprintf("Disabling USART1 interrupt..\n");
	__NVIC_DisableIRQ(USART1_IRQn);
	status = __NVIC_getStatus(USART1_IRQn);
	kprintf("Usart1 irq status: %d\n", status);

	delay(1000);
	__NVIC_EnableIRQ(USART1_IRQn);
	__NVIC_DisableIRQ(USART2_IRQn);
	status = __NVIC_getStatus(USART1_IRQn);
	kprintf("Usart1 irq status: %d\n", status);
	status = __NVIC_getStatus(USART2_IRQn);
	kprintf("Usart2 irq status: %d\n", status);
	status = __NVIC_getStatus(TIM2_IRQn);
	kprintf("timer2 irq status: %d\n", status);





}



void __systickTest() {
	volatile int a, b;
	volatile float fp = -45.125f;
	volatile char str[50] = "Test String";
	volatile char ch = 'a';

	while (1)
	{
		kprintf("Time: %d\r\n\r", getTime());
		kprintf("input new value for int(a):\r\n\r");
		kscanf("%d", &a);
		kprintf("value of int(a) is (%d)B10 (%x)B16\r\n\r", a, a);

		kprintf("Time: %d\r\n\r", getTime());
		kprintf("input new value for int(b):\r\n\r");
		kscanf("%d", &b);
		kprintf("value of int(b) is %d\r\n\r", b);

		kprintf("Time: %d\r\n\r", getTime());
		kprintf("input new value for float(fp):\r\n\r");
		kscanf("%f", &fp);
		kprintf("value of float(fp) is %f\r\n\r", fp);

		kprintf("Time: %d\r\n\r", getTime());
		kprintf("input new value for char(ch):\r\n\r");
		kscanf("%c", &ch);
		kprintf("value of char(ch) is %c\r\n\r", ch);

		kprintf("Time: %d\r\n\r", getTime());
		kprintf("input new value for char(str[50]):\r\n\r");
		kscanf("%s", &str);
		kprintf("value of char(str[50]) is %s\r\n\r", str);
		a++;
		b++;
		// you can change the following line by replacing a delay function
		for (uint32_t i = 0; i < 1000000; i++)
		{
		}
	}

}



