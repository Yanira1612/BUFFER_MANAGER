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
        std::cout << "5. Salir\n";
        std::cin >> option;
        switch (option) {

            // solicitar página
            case 1:
                int block_id;
                std::cout << "Ingrese el block_id: ";
                std::cin >> block_id;
                mainFrame = buffer_manager.requestPage(block_id,policy);

                // si la página no se pudo cargar por falta de espacio
                if(mainFrame == nullptr) {
                    std::cout << "No se pudo cargar la página\n";
                    break;
                }
                if(mainFrame->dirty==false){
                mainFrame->showPage();
                // modificar la data
                std::cout << "desea modificar la data? (1: si, 0: no): ";
                int mod;
                std::cin >> mod;
                if (mod == 1) {
                    std::string data;
                    std::cout << "Ingrese la nueva data: ";
                    //cin de linea entera
                    std::cin.ignore();
                    std::getline(std::cin, data);
                    mainFrame->page->data = data;
                    mainFrame->dirty = true;
                }}
                else{
                    std::cout<<"No se puede solicitar la pagina"<<std::endl;
                }
                break;

            // liberar página
            case 2:
                int page_id;
                std::cout << "Ingrese el page_id: ";
                std::cin >> page_id;
                if(buffer_manager.getFrame(page_id))
                buffer_manager.releasePage(page_id,buffer_manager.getFrame(page_id)->dirty);
                else
                buffer_manager.releasePage(page_id,false);
                break;

            // mostrar páginas
            case 3:
                buffer_manager.showFrames(policy);
                break;
            case 4:
                std::cout << "Ingrese el page_id: ";
                std::cin >> page_id;
                buffer_manager.savePage(page_id);
            case 5:
                break;
                // salir
            default:
                std::cout << "Opción inválida\n";
                break;
        }
    } while (option != 5);
    return 0;
}
