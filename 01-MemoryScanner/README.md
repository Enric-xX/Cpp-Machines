# ⚙️ Machine 01: Deep Memory Pattern Scanner (AOB)

Esta es una máquina de escaneo profundo diseñada en C++. Utiliza la técnica **AOB (Array of Bytes)** para localizar direcciones de memoria dinámicas que cambian cada vez que se reinicia un programa.

## 🚀 Cómo configurar tu Objetivo

Para que la máquina funcione con el proceso que tú quieras, solo tienes que editar el archivo `main.cpp`. Sigue estos pasos:

### 1. Cambiar el Proceso objetivo
Busca esta línea en el `main()` y cambia `"cs2.exe"` por el proceso que quieras:
```cpp
if (maquina.FindProcess("proceso_que_quieras.exe"))

2. Configurar el Patrón de Búsqueda
En la función RunLogic(), verás la línea del escáner. Aquí es donde pones la "huella dactilar" del código que buscas:

C++
cachedAddress = ScanPattern(0x1000000, 0xFFFFFFF, "\x48\x8B\x05...", "xxx???...");
Bytes (\x00): Son los valores exactos que buscas.

Máscara (x e ?): Usa x para bytes que nunca cambian y ? para bytes que son variables (como punteros o offsets).

🔍 ¿Cómo saber el nombre exacto del proceso?
Si no estás seguro de cómo se llama el archivo .exe que quieres escanear, haz lo siguiente:

Abre el programa o juego que quieras analizar.

Pulsa Ctrl + Shift + Esc para abrir el Administrador de Tareas.

Ve a la pestaña Detalles.

Busca el programa en la lista. El nombre que aparece en la columna "Nombre" (incluyendo el .exe) es el que debes poner en el código.

Ejemplo: Notepad.exe, Calculator.exe, VLC.exe.

🛠️ Requisitos de Compilación
Para que la máquina tenga acceso total a la memoria del sistema:

Arquitectura: Compila en x64 para procesos de 64 bits (como CS2).

Permisos: El ejecutable resultante debe correr como Administrador (Clic derecho -> Ejecutar como administrador).

IDE: Recomendado Visual Studio 2022.
