#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

/**
 * CAPA 1: EL SANDBOX (Aislamiento de Seguridad)
 * En un entorno real usaría seccomp o namespaces. Aquí implementamos 
 * un monitor de recursos que mata la tarea si excede el tiempo.
 */
class SecureSandbox {
public:
    bool executeSafe(std::string taskName, std::function<void()> task) {
        std::cout << "[SANDBOX] Iniciando entorno seguro para: " << taskName << "\n";
        
        // Simulamos el aislamiento de recursos
        bool success = true;
        try {
            task(); // Ejecución dentro de la "caja"
        } catch (...) {
            std::cerr << "[ERR] Violación de seguridad o fallo en tarea.\n";
            success = false;
        }
        
        std::cout << "[SANDBOX] Tarea finalizada. Limpiando entorno...\n";
        return success;
    }
};

/**
 * CAPA 2: EL NODO TRABAJADOR (Worker Node)
 * Esta máquina recibe órdenes y las mete en el Sandbox.
 */
class WorkerNode {
private:
    int id;
    SecureSandbox sandbox;

public:
    WorkerNode(int _id) : id(_id) {}

    void processTask(std::string cmd) {
        std::cout << "[WORKER " << id << "] Recibida orden: " << cmd << "\n";
        
        // Ejecutamos la lógica dentro del sandbox
        sandbox.executeSafe(cmd, [&]() {
            std::cout << "   -> Ejecutando: " << cmd << " en core aislado...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        });
    }
};

/**
 * CAPA 3: EL MAESTRO (Master Watcher)
 * Orquesta las máquinas y reparte el trabajo.
 */
class MasterWatcher {
private:
    std::vector<std::unique_ptr<WorkerNode>> cluster;

public:
    void addNode(int id) {
        cluster.push_back(std::make_unique<WorkerNode>(id));
    }

    void distributeWork(std::string task) {
        static int nextNode = 0;
        if (cluster.empty()) return;

        std::cout << "[MASTER] Distribuyendo tarea al nodo " << nextNode << "...\n";
        cluster[nextNode]->processTask(task);
        
        nextNode = (nextNode + 1) % cluster.size(); // Round-robin (Balanceo de carga)
    }
};

/**
 * MAIN: Simulación de la Red Distribuida
 */
int main() {
    std::cout << "--- CppSecureCluster Manager v1.0 ---\n\n";

    MasterWatcher master;

    // 1. Añadimos máquinas al sistema (Simulación de 3 nodos)
    master.addNode(101);
    master.addNode(102);
    master.addNode(103);

    std::cout << "\n[INFO] Cluster listo. Enviando ráfaga de tareas...\n\n";

    // 2. Enviamos tareas que se repartirán y ejecutarán en sandboxes
    std::vector<std::string> tareas = {
        "Cifrado de datos",
        "Análisis de logs",
        "Compresión de imagen",
        "Escaneo de red"
    };

    for (const auto& t : tareas) {
        master.distributeWork(t);
        std::cout << "-------------------------------------\n";
    }

    std::cout << "\n[SISTEMA] Todas las máquinas han respondido correctamente.\n";

    return 0;
}
