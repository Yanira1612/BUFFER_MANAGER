#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

// Clase BufferPool
#include "Frame.h"
#include "Page.h"
#include <vector>
#include <unordered_map>
#include <list>
#include <ctime>

#include "BufferPool.h"

class BufferManager {
private:

    static const int LRU = 1;
    static const int MRU = 2;
    static const int CLOCK = 3;


    BufferPool* bufferManager;

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

    BufferManager(int size);

    // Destructor de BufferPool
    ~BufferManager() ;

    void writePageToDisk(Page* page) ;

    // pinPage() busca una página y la fija, si no está en memoria la carga
    Frame* pinPage(int block_id,int policy) ;

    // realiza la consulta
    Frame* requestPage(int block_id,int policy) ;

    // remueve el Pin de la página y se puede marcar como sucia si dirty = true
    void unpinPage(int page_id, int policy, bool dirty = false) ;

    void releasePage(int page_id, int policy) ;

    bool pinned(int page_id) ;

    bool unpinned(int page_id) ;

    // carga una página en el buffer pool
    // con un page_id y un bloque de datos
    Frame* loadPage(int block_id,int policy) ;

    // obtiene la página con el page_id
    Page* getPage(int page_id);

    Frame* getFrame(int page_id);

    // imprime cada frame y el id de la página que contiene
    void showFrames(int policy) ;

    // guardar la página
    void savePage(int page_id) {
        Page* pageNew = getPage(page_id);
        if(getFrame(page_id)->dirty==true){
            writePageToDisk(pageNew);
        }
        else{
            std::cout << "La pagina no ha sido modificada" << std::endl;
        }

    }

};
#endif //BUFFERMANAGER_H
