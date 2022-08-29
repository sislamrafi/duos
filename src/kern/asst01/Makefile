CC=arm-none-eabi-gcc
MACH=cortex-m4
FPU = -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mthumb-interwork
TARGET = target
OBJECT = object
MAPDIR = mapfiles
CFLAGS = -mcpu=$(MACH) -mthumb -c -g -DSTM32 -DSTM32F4  $(FPU) -std=gnu11 -Wall -O1 -Wall
LFLAGS =   -nostdlib -nostartfiles -nodefaultlibs  -mcpu=$(MACH) -mthumb $(FPU) -T stm32_ls.ld -Wl,-Map=$(MAPDIR)/asst01.map -Wl,--start-group -lc -lm -lgcc -Wl,--end-group


all:app_libs_timer_timer.o app_libs_debug_debug.o __kern_kstdio_kstdio.o __kern_kmain_kmain.o __kern_softfp_softfp.o __kern_kmain_sys_init.o __kern_arch_stm32f446re_dev_clock.o __kern_arch_stm32f446re_dev_gpio.o __kern_arch_stm32f446re_dev_usart.o __kern_arch_stm32f446re_dev_timer.o __kern_arch_cortex-m4_dev_fpu.o __kern_arch_stm32f446re_sys_stm32_startup.o asst01

asst01:app_libs_timer_timer.o app_libs_debug_debug.o __kern_kstdio_kstdio.o __kern_kmain_kmain.o __kern_softfp_softfp.o __kern_kmain_sys_init.o __kern_arch_stm32f446re_dev_clock.o __kern_arch_stm32f446re_dev_gpio.o __kern_arch_stm32f446re_dev_usart.o __kern_arch_stm32f446re_dev_timer.o __kern_arch_cortex-m4_dev_fpu.o __kern_arch_stm32f446re_sys_stm32_startup.o 
	$(CC) $(LFLAGS) $(OBJECT)/*.o  -o $(TARGET)/$@


app_libs_timer_timer.o:../../sotom-dev/app/libs/timer/timer.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

app_libs_debug_debug.o:../../sotom-dev/app/libs/debug/debug.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_kstdio_kstdio.o:../kstdio/kstdio.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_kmain_kmain.o:../kmain/kmain.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_softfp_softfp.o:../softfp/softfp.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_kmain_sys_init.o:../kmain/sys_init.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_stm32f446re_dev_clock.o:../arch/stm32f446re/dev/clock.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_stm32f446re_dev_gpio.o:../arch/stm32f446re/dev/gpio.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_stm32f446re_dev_usart.o:../arch/stm32f446re/dev/usart.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_stm32f446re_dev_timer.o:../arch/stm32f446re/dev/timer.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_cortex-m4_dev_fpu.o:../arch/cortex-m4/dev/fpu.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

__kern_arch_stm32f446re_sys_stm32_startup.o:../arch/stm32f446re/sys/stm32_startup.c
	$(CC) $(CFLAGS) -o $(OBJECT)/$@ $^

clean:
	rm -rf $(OBJECT)/*.o $(MAPDIR)/*.map $(TARGET)/* *.o *.elf


