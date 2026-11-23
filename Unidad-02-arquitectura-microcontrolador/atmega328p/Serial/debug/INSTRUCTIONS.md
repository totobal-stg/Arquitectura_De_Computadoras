# 🛠️ Guía de Depuración AVR con GDBGUI

Sigue estos pasos para compilar, simular y depurar tu código ensamblador en el entorno interactivo.

## Paso 1: Iniciar el Entorno
Abre una terminal en la carpeta de tu proyecto y ejecuta el script de automatización:
```bash
./launch_debug.sh
```
*Nota: La primera vez tardará un poco porque instalará `gdbgui` de forma local. En las siguientes ejecuciones se abrirá de inmediato.*

---

## Paso 2: Conexión y Configuración en GDBGUI
Una vez que se abra tu navegador web en la interfaz de **gdbgui**, dirígete a la **consola de comandos** ubicada en la barra inferior de la pantalla e introduce los siguientes comandos en orden:

1. **Conectarse al simulador:**
   ```text
   target remote localhost:1234
   ```
2. **Cargar el mapa de símbolos de tu código:**
   ```text
   file build/main.elf
   ```
   *(Si aparece un mensaje de confirmación, presiona la tecla `y` o acepta).*

3. **Colocar un punto de interrupción en el inicio:**
   ```text
   break main
   ```

4. **Correr el programa hasta el inicio:**
   ```text
   continue
   ```

---

## Paso 3: ¿Cómo depurar tu código paso a paso?
Ahora que la flecha de ejecución está posicionada en tu código, usa los comandos de la consola para avanzar:

* `stepi` (o simplemente `si`): Ejecuta exactamente **una instrucción de ensamblador** a la vez. Es el comando ideal para este curso.
* `info registers`: Muestra el estado actual de todos los registros del microcontrolador.
* `info registers r16 r17`: Muestra únicamente el valor de los registros específicos `R16` y `R17`.

---
💡 **Tip de oro:** Cada vez que hagas modificaciones en tu archivo `main.S`, solo debes cerrar la ventana de GDBGUI, escribir `./launch_debug.sh` en tu terminal y el proyecto se volverá a compilar con tus cambios actualizados.
