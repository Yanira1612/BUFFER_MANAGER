//
// AUTOR: Alonso Chullunquia
//
#ifndef PAGE_H
#define PAGE_H
#include <chrono>

#include "Block.h"

class Page {
public:
    int page_id;           // id de la página (la misma que el bloque)
    bool dirty;            // indica si la página ha sido modificada
    int pin_count;         // contador de fijaciones de la página
    std::time_t last_used; // hora de la última fijación para LRU
    Block* block;          // puntero al bloque de disco
    std::string data;      // datos de la página/bloque

    //Constructor de la clase Page a base del id del bloque
    Page (int BlockId) {
        page_id= BlockId;
        dirty = false;
        pin_count = 0;
        last_used = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        block = new Block(BlockId);
        // Extrayendo info del bloque
        std::ifstream file(block->pathDisk);
        std::string line;
        while(std::getline(file, line)) {
            data += line + "\n";
        }
    }

    //Destructor de la clase Page
    ~Page() {
        delete block;
    }
};

#endif //PAGE_H