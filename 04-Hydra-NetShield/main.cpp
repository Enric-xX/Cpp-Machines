#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <queue>

/**
 * NUEVA MÁQUINA: EL PROXY (Gateway / Firewall)
 * Es la primera línea de defensa. Filtra peticiones y balancea.
 */
class ClusterProxy {
private:
    bool is_firewall_active = true;

public:
    // El Proxy decide si una petición es segura antes de pasarla al Master
    bool validateRequest(std::string packet) {
        std::cout << "[PROXY] Analizando paquete entrante: '" << packet << "'\n";
        
        // Filtro de seguridad simple: si contiene la palabra "HACK", se bloquea
        if (packet.find("HACK") != std::string::npos) {
            std::cerr << "[!] SEGURIDAD: Petición bloqueada por el Proxy.\n";
            return false;
        }
        
        std::cout << "[PROXY] Tráfico legítimo. Redirigiendo al Master...\n";
        return true;
    }
};

/**
 * CAPA: EL SANDBOX (Aislamiento)
 */
class SecureSandbox {
public:
    void executeSafe(std::string taskName, std::function<void()> task) {
        std::cout << "   [SANDBOX] Entorno aislado creado para: " << taskName << "\n";
        task();
    }
};

/**
 * CAPA: EL NODO TRABAJADOR (Worker Node)
 */
class WorkerNode {
private:
    int id;
    SecureSandbox sandbox;
public:
    WorkerNode(int _id) : id(_id) {}
    void process(std::string cmd) {
        std::cout << "      [NODE " << id << "] Ejecutando tarea...\n";
        sandbox.executeSafe(cmd, [](){ 
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
        });
    }
};

/**
 * CAPA: EL MAESTRO (Master Watcher)
 */
class MasterWatcher {
private:
    std::vector<std::unique_ptr<WorkerNode>> nodes;
    int current = 0;
public:
    void addNode(int id) { nodes.push_back(std::make_unique<WorkerNode>(id)); }
    
    void onNewTask(std::string task) {
        if (nodes.empty()) return;
        std::cout << "[MASTER] Recibido del Proxy. Asignando a nodo " << nodes[current]->process(task);
        current = (current + 1) % nodes.size();
    }
};

/**
 * MAIN: Simulación de la Red Completa
 */
int main() {
    std::cout << "=== HYDRA-NET: SISTEMA DISTRIBUIDO SEGURO ===\n\n";

    ClusterProxy proxy;
    MasterWatcher master;
    
    master.addNode(1);
    master.addNode(2);

    // ESCENARIO 1: Petición normal
    std::string peticion1 = "Calcular_Nomina_V2";
    if (proxy.validateRequest(peticion1)) {
        master.onNewTask(peticion1);
    }

    std::cout << "\n-------------------------------------------\n\n";

    // ESCENARIO 2: Intento de inyección/ataque
    std::string peticion2 = "DROP_TABLE_USERS_HACK";
    if (proxy.validateRequest(peticion2)) {
        master.onNewTask(peticion2);
    }

    std::cout << "\n[SISTEMA] El Proxy ha protegido el cluster con éxito.\n";

    return 0;
}
