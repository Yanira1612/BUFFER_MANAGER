#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Classes/BufferPool.h"
#include "Classes/BufferPool.cpp"
#include "Classes/Block.h"
#include "Classes/Page.h"
#include "Classes/Frame.h"
#include "Classes/BufferManager.h"
#include "Classes/BufferManager.cpp"


int main() {
    // inicializando buffer manager
    BufferManager buffer_manager(3);

    // inicializando mainFrame puntero a Frame para mostrar la página
    Frame* mainFrame;

    int policy;
                std::cout << "Ingrese la política de reemplazo (1->LRU, 2->MRU, 3->CLOCK): ";
                std::cin >> policy;

    // menú de acciones
    int option;
    do {
        std::cout << "1. Solicitar página\n";
        std::cout << "2. Liberar página\n";
        std::cout << "3. Mostrar páginas\n";
        std::cout << "4. Guardar pagina en disco\n";
        std::cout << "5. Pinned pagina\n";
        std::cout << "6. Unpinned pagina\n";
        std::cout << "7. Salir\n";
        std::cin >> option;
        switch (option) {

            // solicitar página
            case 1:
                int block_id;
                std::cout << "Ingrese el block_id: ";
                std::cin >> block_id;
                mainFrame = buffer_manager.requestPage(block_id,policy); // solicita una página

                break;

            // liberar página
            case 2:
                int page_id;
                std::cout << "Ingrese el page_id: ";
                std::cin >> page_id;
                buffer_manager.releasePage(page_id,policy);
                break;

            // mostrar páginas
            case 3:
                buffer_manager.showFrames(policy);
                break;
            case 4:
                std::cout << "Ingrese el page_id: ";
                std::cin >> page_id;
                buffer_manager.savePage(page_id);
                break;
            case 5:
                std::cout << "Ingrese el page_id a pinnear: ";
                std::cin >> page_id;
                buffer_manager.pinned(page_id);
                break;
            case 6:
                std::cout << "Ingrese el page_id a unpinnear: ";
                std::cin >> page_id;
                buffer_manager.unpinned(page_id);
                break;
            case 7:
                break;
                // salir
            default:
                std::cout << "Opción inválida\n";
                break;
        }
    } while (option != 7);
    return 0;
}
