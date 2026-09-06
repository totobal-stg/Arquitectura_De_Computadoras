CC := avr-gcc
CFLAGS := -ggdb3 -O0 -mmcu=atmega328p

all:
	$(info Inicializando compilación ...)
	mkdir -p build
	$(CC) $(CFLAGS) main.S -o build/main.elf

clean:
	rm -rf build/
