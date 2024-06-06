#ifndef BUFFERPOOLMANAGER_H 
#define BUFFERPOOLMANAGER_H
#include "BufferPool.h"
// Clase BufferManager: Maneja las operaciones del Buffer Pool, 
// controla solicitudes de página y liberacion de paginas
class BufferManager {
private:
    BufferPool* buffer_pool; //Puntero al BufferPool gestionado por el BufferManager

public:
    BufferManager(int buffer_pool_size) { //Constructor para inicializar el BufferManager con un tamaño específico para el BufferPool.
        buffer_pool = new BufferPool(buffer_pool_size);//bufferPoolSize Tamaño del BufferPool.
    }

    ~BufferManager() {//Destructor para liberar la memoria ocupada por el BufferPool
        delete buffer_pool;
    }

    /**
    Solicita una página del BufferPool y realiza pinPage.
    Parametro: Identificador del bloque a solicitar.
    Retorna: Puntero al Frame que contiene la página solicitada.
    */
    Frame* requestPage(int block_id,int policy) {
        return buffer_pool->pinPage(block_id,policy);
    }

    /**
    Libera una página del BufferPool, determinando si está sucia o no.
    Parametros: pageId Identificador de la página a liberar,dirty Indica si la página está sucia
    */
    void releasePage(int page_id, bool dirty = false) {
        buffer_pool->unpinPage(page_id, dirty);
    }

    // Obtiene una página del BufferPool por su ID.
    Page* getPage(int page_id) {
        return buffer_pool->getPage(page_id);
    }

    void savePage(int page_id) {
        Page* pageNew = getPage(page_id);
        if(pageNew->dirty==true){
            buffer_pool->writePageToDisk(pageNew);
        }
        else{
            std::cout << "La pagina no ha sido modificada" << std::endl;
        }
        
    }


    //Muestra la información de todos los frames en el BufferPool.
    void showFrames() { 
        buffer_pool->showFrames();
    }
};

#endif //BUFFERPOOLMANAGER_H
