#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include <stdint.h>

int POKEMON = 0;
void kmain(void)
{
	__sys_init();

	volatile int a, b;
	volatile float fp = -45.125f;
	volatile char str[50] = "Test String";
	volatile char ch = 'a';

	kprintf("Booting OS CSE: Version: 1.0, Time:%d\r\n\r", getTime());
	kprintf("Wellcome ....\r\n\r");
	kprintf("\nCSEOS is ready to take input:\r\n");

	delay(2000);

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



