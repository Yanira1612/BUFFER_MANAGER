#ifndef PAGE_H
#define PAGE_H


#include "Block.h"

class Page {
public:
    int page_id;           // id de la página (la misma que el bloque)
    Block* block;          // puntero al bloque de disco
    std::string data;      // datos de la página/bloque

    //Constructor de la clase Page a base del id del bloque
    Page (int BlockId) {
        page_id= BlockId;
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
