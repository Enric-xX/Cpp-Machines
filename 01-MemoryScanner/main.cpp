}#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

using namespace std;

class MemoryMachine {
public:
    DWORD processId = 0;
    HANDLE hProcess = NULL;
    uintptr_t cachedAddress = 0; // Aquí recordamos la dirección encontrada

    // 1. La máquina busca el proceso
    bool FindProcess(const char* name) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe = { sizeof(pe) };
        if (Process32First(snap, &pe)) {
            do {
                if (!_stricmp(pe.szExeFile, name)) {
                    processId = pe.th32ProcessID;
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
                    return true;
                }
            } while (Process32Next(snap, &pe));
        }
        return false;
    }

    // 2. La máquina escanea la memoria buscando un patrón de bytes
    uintptr_t ScanPattern(uintptr_t base, size_t size, const char* pattern, const char* mask) {
        vector<BYTE> buffer(size);
        SIZE_T bytesRead;
        ReadProcessMemory(hProcess, (LPCVOID)base, buffer.data(), size, &bytesRead);

        for (size_t i = 0; i < bytesRead - strlen(mask); i++) {
            bool found = true;
            for (size_t j = 0; j < strlen(mask); j++) {
                if (mask[j] != '?' && (BYTE)pattern[j] != buffer[i + j]) {
                    found = false;
                    break;
                }
            }
            if (found) return base + i;
        }
        return 0;
    }

    // 3. Sistema de "Recuerdo" (Memory Cache)
    void RunLogic() {
        if (cachedAddress != 0) {
            // Comprobamos si la dirección antigua sigue siendo válida
            int val = 0;
            if (ReadProcessMemory(hProcess, (LPCVOID)cachedAddress, &val, sizeof(int), NULL)) {
                // Sigue viva, no hacemos nada
                return;
            } else {
                cout << "[!] La memoria cambio. Reiniciando escaner..." << endl;
                cachedAddress = 0;
            }
        }

        // Si no la recuerda o ha cambiado, la busca de nuevo
        // Este patrón es un ejemplo para encontrar la base del jugador
        cachedAddress = ScanPattern(0x1000000, 0xFFFFFFF, "\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0", "xxx????xxx");
        
        if (cachedAddress) {
            cout << "[+] Maquina: Nueva direccion encontrada y recordada: 0x" << hex << cachedAddress << endl;
        }
    }
};

int main() {
    SetConsoleTitleA("MAQUINA BUSCADORA DE MEMORIA);
    system("color 0b"); // Azul eléctrico

    MemoryMachine maquina;

    cout << "MAQUINA INICIADA. Buscando objetivo: elprocesoquehayaselegido.exe..." << endl;

    while (true) {
        if (maquina.processId == 0) {
            if (maquina.FindProcess("elprocesoquequieras.exe")) {
                cout << "[+] Objetivo localizado. Iniciando calculos de memoria..." << endl;
            }
        } else {
            maquina.RunLogic();
        }
        Sleep(2000); // La máquina chequea cada 2 segundos para no gastar CPU
    }

    return 0;


