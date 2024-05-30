//Autor: Yanira Suni 
#ifndef FRAME_H
#define FRAME_H
#include <iostream>

#include "Page.h"

// Clase Frame: Representa un frame en el buffer pool, que puede contener una página.
class Frame {
public:
    int frame_id; //Identificador único del frame
    Page* page; //Puntero a la página almacenada en el frame

    Frame(int id) : frame_id(id), page(nullptr) {} //Constructor para inicializar un frame con un ID específico

    ~Frame() { //Destructor para liberar la memoria ocupada por la página
        delete page;
    }

    void showPage() { //Muestra la información de la página almacenada en el frame.
        std::cout << "== Frame Info ==================================\n";
        std::cout << "Frame: " << frame_id << std::endl;
        std::cout << "Page: " << page->page_id << std::endl;
        std::cout << "Dirty: " << page->dirty << std::endl;
        std::cout << "Pin Count: " << page->pin_count << std::endl;
        std::cout << "Last Used: " << std::ctime(&page->last_used);
        std::cout << "Data: \n" << page->data << std::endl;
        std::cout << "================================================\n";
    }
};

#endif //FRAME_H