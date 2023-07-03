all: libubit.a

UBIT_OBJS = acelerometro.o botones.o buzzer.o display.o misc.o
MICROBIAN_OBJS = ../microbian/display.o ../microbian/i2c.o ../microbian/lib.o ../microbian/microbian.o ../microbian/mpx-m4.o ../microbian/radio.o ../microbian/serial.o ../microbian/startup.o ../microbian/timer.o

FLAGS = -mcpu=cortex-m4 -mthumb -O -g -Wall -ffreestanding

libubit.a: $(UBIT_OBJS) $(MICROBIAN_OBJS)
	arm-none-eabi-ar cr $@ $^

%.o: %.c
	arm-none-eabi-gcc $(FLAGS) -c $< -o $@ 

clean:
	rm -f libubit.a *.o
