# 🌐 Machine 02: Neural Node Controller (Networking)

Esta máquina es un servidor de red asíncrono de alto rendimiento diseñado en C++. Utiliza la librería **Boost.Asio** para gestionar múltiples conexiones simultáneas sin bloquear el flujo principal del programa, lo que la hace ideal para sistemas de control remoto o redes distribuidas.

## 🚀 Cómo configurar tu Nodo

Para poner en marcha esta máquina, solo necesitas definir el puerto de escucha en tu archivo main.cpp:

-----------------------------------------------------------
int main() {
    try {
        // Inicializa el nodo en el puerto deseado (ejemplo: 1234)
        NodeServer server(1234); 
        
        std::cout << "Nodo activo. Esperando comandos..." << std::endl;
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Error en el nodo: " << e.what() << std::endl;
    }
    return 0;
}
-----------------------------------------------------------

## 📦 Requisito Crítico: Boost Libraries
Esta máquina utiliza tecnología avanzada de red que requiere la librería Boost. Para compilarla correctamente:

* Instalación: Descarga las librerías Boost (versión 1.80 o superior recomendada) o usa un gestor como vcpkg.
* Configuración del IDE: Añade la ruta de Boost en "Directorios de inclusión adicionales". Si usas Visual Studio, asegúrate de que el Linker reconozca los binarios de Boost.
* Gestión de Memoria: El código implementa std::shared_ptr para asegurar que cada conexión sea eliminada de la RAM automáticamente al terminar, evitando fugas de memoria (memory leaks).

## 🔍 Funcionamiento del Servidor
* Escucha Asíncrona: El nodo no se detiene; acepta nuevos clientes mientras procesa los datos de los anteriores.
* Comando ACK: Cada vez que la máquina recibe un paquete de datos, responde con un código "ACK" (Acknowledge) para confirmar que la instrucción ha sido recibida y ejecutada en el nodo.

---
Desarrollado por Enric-xX // Proyecto educativo de la Suite Cpp-Machines
