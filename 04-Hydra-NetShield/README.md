# 🛡️ Machine 04: Hydra-Net Shield (Proxy & Firewall)

Esta máquina es la primera línea de defensa de la suite Cpp-Machines. Actúa como un **Gateway/Firewall** inteligente que intercepta, analiza y filtra todas las peticiones entrantes antes de que lleguen al cluster de computación.

## 🚀 Cómo funciona el Escudo

El sistema implementa una arquitectura de inspección de paquetes en tres niveles:

1. **The Proxy (Gateway):** Analiza cada cadena de datos entrante. Si detecta patrones de ataque o palabras prohibidas (como inyecciones de código), bloquea la petición inmediatamente.
2. **The Master Watcher:** Solo recibe tráfico que ya ha sido validado y "limpiado" por el Proxy, distribuyéndolo entre los nodos disponibles.
3. **The Secure Nodes:** Ejecutan la tarea final en un entorno controlado.

## 🛠️ Configuración del Firewall

Puedes personalizar las reglas de seguridad dentro de la clase `ClusterProxy` para adaptar la máquina a tus necesidades:

-----------------------------------------------------------
int main() {
    ClusterProxy proxy;
    MasterWatcher master;
    
    master.addNode(1); // Añadir nodos de ejecución

    std::string peticion = "Calcular_Datos_HACK"; 

    // El Proxy decide si la petición pasa al sistema o se destruye
    if (proxy.validateRequest(peticion)) {
        master.onNewTask(peticion);
    }
}
-----------------------------------------------------------

## 🔍 Características Técnicas
* **Traffic Filtering:** Implementa una capa lógica de firewall para detectar intrusiones.
* **Architecture Gateway:** Separa la red pública (entrada de datos) de la red privada (nodos de trabajo).
* **Load Balancing:** Una vez validada la petición, se utiliza un algoritmo de rotación para no saturar los nodos.
* **Simulación de Latencia:** Utiliza `std::chrono` para simular el tiempo de inspección real de un firewall profesional.

---
Desarrollado por Enric-xX // Proyecto educativo de la Suite Cpp-Machines
