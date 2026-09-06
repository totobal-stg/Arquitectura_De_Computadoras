# Instalar toolchain de AVR
> sudo apt-get install gcc-avr binutils-avr avr-libc avrdude simavr avra

# Ensamblar y enlazar
> avr-gcc -mmcu=atmega328p -Os -o blink.elf blink.S

# Generar archivo HEX para grabar
> avr-objcopy -O ihex -R .eeprom blink.elf blink.hex

# (Opcional) Ver el código desensamblado
> avr-objdump -S blink.elf > blink.lst

# Ejecutar emulador
> simavr -g -m atmega328p -f 16000000 blink.elf

# Conectar al emulador
target remote :1234

# Establecer breakpoint en main
break main

# Ejecutar hasta el breakpoint
continue

# Ahora puedes depurar paso a paso
step          # Ejecuta una instrucción
stepi         # Ejecuta una instrucción (modo ensamblador)
info registers # Ver registros
print/d R18    # Ver valor de R18
