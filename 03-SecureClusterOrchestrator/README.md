# 🖥️ Machine 03: Secure Cluster Orchestrator

Esta máquina es un sistema de orquestación distribuida diseñado en C++. Simula un entorno de computación en la nube donde un "Maestro" distribuye tareas de forma inteligente entre varios "Nodos Trabajadores", asegurando que cada tarea se ejecute dentro de un Sandbox de seguridad.

## 🚀 Cómo funciona el Cluster

La máquina está dividida en tres niveles de inteligencia:

1. **The Sandbox:** Aísla la ejecución de las tareas para evitar que un fallo en una orden detenga todo el sistema.
2. **Worker Nodes:** Máquinas individuales que reciben órdenes y gestionan sus propios recursos.
3. **Master Watcher:** El cerebro del sistema. Utiliza un algoritmo de **Round-robin** para repartir el trabajo de forma equitativa entre todos los nodos disponibles.

## 🛠️ Configuración de la Red de Nodos

En el archivo main.cpp puedes escalar el sistema añadiendo tantos nodos como necesites:

-----------------------------------------------------------
int main() {
    MasterWatcher master;

    // Añadir nodos al cluster (puedes añadir 3 o 300)
    master.addNode(101);
    master.addNode(102);
    master.addNode(103);

    // Enviar tareas para que el sistema las distribuya automáticamente
    master.distributeWork("Cifrado de datos");
}
-----------------------------------------------------------

## 🔍 Conceptos Avanzados Aplicados
* **Smart Pointers (std::unique_ptr):** Gestión de memoria eficiente y segura para los nodos del cluster.
* **Programación Funcional:** Uso de `std::function` y lambdas para pasar tareas complejas a través de las capas.
* **Balanceo de Carga:** Algoritmo matemático para optimizar el uso de los recursos del sistema.
* **Concurrencia:** Simulación de tiempos de respuesta mediante hilos (`std::this_thread`).

---
Desarrollado por Enric-xX // Proyecto educativo de la Suite Cpp-Machines
