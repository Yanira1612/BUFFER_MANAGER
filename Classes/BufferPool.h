#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

// Clase BufferPool
#include "Frame.h"
#include "Page.h"
#include <vector>
#include <unordered_map>
#include <list>
#include <ctime>

class BufferPool {
private:

    static const int LRU = 1;
    static const int MRU = 2;
    static const int CLOCK = 3;

    int size; // Tamaño del buffer pool en número de frames
    std::vector<Frame*> frames; // Vector de frames
    std::unordered_map<int, Frame*> page_table; // Tabla de páginas para mapear page_id a frames
    std::list<Frame*> replacement_queue; // Lista enlazada para el algoritmo LRU
    int clock_hand;

    // Obtiene un frame libre cuando el frame no tiene una página cargada en el puntero page
    Frame* getFreeFrame() ;

    // evictPage() elige una página para reemplazarla en el buffer pool
    // y la elimina de la tabla de páginas sin no antes escribirla en disco si es necesario
    Frame* evictPage(int policy) ;

    // chooseVictimFrame() elige la página a reemplazar en el buffer pool
    Frame* chooseVictimFrame(int policy) ;

    // actualiza la página en disco con la nueva información
   

    // obtiene la hora actual en formato std::time_t para last_used
    std::time_t getCurrentTime() ;

public:
    // Constructor de BufferPool
  //  BufferPool(int buffer_pool_size) ;

    BufferPool(int size);

    // Destructor de BufferPool
    ~BufferPool() ;

    void writePageToDisk(Page* page) ;

    // pinPage() busca una página y la fija, si no está en memoria la carga
    Frame* pinPage(int block_id,int policy) ;

    // remueve el Pin de la página y se puede marcar como sucia si dirty = true
    void unpinPage(int page_id, bool dirty = false) ;

    // carga una página en el buffer pool
    // con un page_id y un bloque de datos
    Frame* loadPage(int block_id,int policy) ;

    // obtiene la página con el page_id
    Page* getPage(int page_id);

    // imprime cada frame y el id de la página que contiene
    void showFrames(int policy) ;

};
#endif //BUFFERPOOL_H
