#ifndef FRAME_H
#define FRAME_H
#include <iostream>

#include "Page.h"
#include <chrono>

// Clase Frame: Representa un frame en el buffer pool, que puede contener una página.
class Frame {
public:
    int frame_id; //Identificador único del frame
    Page* page; //Puntero a la página almacenada en el frame
    bool reference_bit;
    bool dirty;            // indica si la página ha sido modificada
    bool pinned;           // indica si la pagina esta pinneada o no
    int pin_count;         // contador de fijaciones de la página
    std::time_t last_used; // hora de la última fijación para LRU

    Frame(int id) : frame_id(id), page(nullptr), reference_bit(false) , pinned(false) {
        dirty = false;
        pin_count = 0;
        last_used = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());} //Constructor para inicializar un frame con un ID específico

    ~Frame() { //Destructor para liberar la memoria ocupada por la página
        delete page;
    }

    void showPage() { //Muestra la información de la página almacenada en el frame.
        std::cout << "== Frame Info ==================================\n";
        std::cout << "Frame: " << frame_id << std::endl;
        std::cout << "Page: " << page->page_id << std::endl;
        std::cout << "Dirty: " << this->dirty << std::endl;
        std::cout << "Pin Count: " << this->pin_count << std::endl;
        std::cout << "Last Used: " << std::ctime(&this->last_used);
    //    std::cout << "Data: \n" << page->data << std::endl;
    //   std::cout << "================================================\n";
    }
};

#endif //FRAME_H
