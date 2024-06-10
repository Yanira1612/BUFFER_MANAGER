#include "BufferPool.h"

#include <iomanip>

// Yanira

// Obtiene un frame libre cuando el frame no tiene una página cargada en el puntero page
Frame* BufferPool::getFreeFrame() {
    auto& frames = bufferPool->frames;
    for (auto& frame : frames) {
        if (frame->page == nullptr) {
            return frame;
        }
    }
    return nullptr;
}


// obtiene la página con el page_id
Page* BufferPool::getPage(int page_id) {
    auto& page_table = bufferPool->page_table;
    if (page_table.find(page_id) != page_table.end()) {
        return page_table[page_id]->page;
    } else {
        std::cout << "La página " << page_id << " no está en el buffer pool." << std::endl;
        return nullptr;
    }
}

Frame* BufferPool::getFrame(int page_id) {
    auto& page_table = bufferPool->page_table;
    if (page_table.find(page_id) != page_table.end()) {
        return page_table[page_id];
    } else {
        std::cout << "El frame para la página " << page_id << " no está en el buffer pool." << std::endl;
        return nullptr;
    }
}

// evictPage() elige una página para reemplazarla en el buffer pool
// y la elimina de la tabla de páginas sin no antes escribirla en disco si es necesario
Frame* BufferPool::evictPage(int policy) {
    auto& page_table = bufferPool->page_table;

    Frame* victim = chooseVictimFrame(policy);
    if(victim == nullptr) {
        std::cerr<<("El BufferPool está lleno y no se puede cargar más páginas.\n");
        return nullptr;
    }
    if (victim->dirty) {
        writePageToDisk(victim->page);
    }

    page_table.erase(victim->page->page_id);
    delete victim->page;
    victim->page = nullptr;
    return victim;
}

// chooseVictimFrame() elige la página a reemplazar en el buffer pool
//LRU
/*
Frame* BufferPool::chooseVictimFrame() {
    // usando una función lambda para ordenar la lista de frames por last_used
    replacement_queue.sort([](Frame* a, Frame* b) { return a->page->last_used < b->page->last_used; });
    for (auto it = replacement_queue.begin(); it != replacement_queue.end(); ++it) {
        if ((*it)->page->pin_count == 0) {
            Frame* victim = *it;
            replacement_queue.erase(it);
            return victim;
        }
    }
    return nullptr;
}*/
Frame* BufferPool::chooseVictimFrame(int policy) {
    auto& frames = bufferPool->frames;
    int& clock_hand = bufferPool->clock_hand;
    int size = bufferPool->size;
    auto& replacement_queue = bufferPool->replacement_queue;

    if (policy == CLOCK) {
        while (true) {
            Frame* frame = frames[clock_hand];

            // Considerar solo frames que no están pinneados
            if (frame->page && frame->pin_count == 0) {
                if (frame->reference_bit) {
                    frame->reference_bit = false;
                } else {
                    clock_hand = (clock_hand + 1) % size;
                    return frame;
                }
            }

            clock_hand = (clock_hand + 1) % size;

                        if (clock_hand == 0) {
                    bool all_pinned = true;
                    for (const auto& f : frames) {
                        if (f->page && f->pin_count == 0) {
                            all_pinned = false;
                            break;
                        }
                    }
                    if (all_pinned) {
                        return nullptr;
                    }
                }
        }
    }

    else{
        // usando una función lambda para ordenar la lista de frames por last_used en orden descendente
        if (policy == LRU) {
            // Ordenar por last_used en orden ascendente para LRU
            replacement_queue.sort([](Frame* a, Frame* b) { return a->last_used < b->last_used; });
        } else if (policy == MRU) {
            // Ordenar por last_used en orden descendente para MRU
            replacement_queue.sort([](Frame* a, Frame* b) { return a->last_used > b->last_used; });
        }

        for (auto it = replacement_queue.begin(); it != replacement_queue.end(); ++it) {
            if ((*it)->pin_count == 0) {
                Frame* victim = *it;
                replacement_queue.erase(it);
                return victim;
            }
        }
    }

    return nullptr;
}


// actualiza la página en disco con la nueva información
void BufferPool::writePageToDisk(Page* page) {
    // Lógica para escribir la página en disco
    std::cout << "Escribiendo página " << page->page_id << " al disco." << std::endl;

    // Ejemplo de escritura en un archivo:
    std::ofstream file(page->block->pathDisk);
    if (file.is_open()) {
        file << page->data;
        file.close();
    }
    getFrame(page->page_id)->dirty = false;// Una vez escrita, la página ya no está sucia
}

// obtiene la hora actual en formato std::time_t para last_used
std::time_t BufferPool::getCurrentTime() {
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}


// CONSTRUCTOR
// Alonso

// Constructor de BufferPool
//BufferPool::BufferPool(int pool_size) : size(pool_size) {
  //  for (int i = 0; i < size; ++i) {
   //     frames.push_back(new Frame(i+1000));
    //}
//}

BufferPool::BufferPool(int size) {
    auto bufferPool = new BufferPoolBase(size);
    this->bufferPool = bufferPool;

}


// Destructor de BufferPool
BufferPool::~BufferPool() {
    delete bufferPool;
}

// pinPage() busca una página y la fija, si no está en el buffer pool, la carga
Frame* BufferPool::pinPage(int block_id,int policy) {
    auto& page_table = bufferPool->page_table;
    // compara si la página está en el buffer pool
    if (page_table.find(block_id) != page_table.end()) {
        Frame* frame = page_table[block_id];
        frame->pin_count++;
        frame->last_used = getCurrentTime();
        frame->reference_bit = true; // Set reference bit
        std::cout << "Pinned página " << block_id << " en el frame " << frame->frame_id << ". Pin count: " << frame->pin_count << std::endl;
        return frame;
    } else {
        return loadPage(block_id,policy);
    }
}

// remueve el Pin de la página y se puede marcar como sucia si dirty = true
void BufferPool::unpinPage(int page_id, int policy,  bool dirty ) {
    auto page_table = bufferPool->page_table;
    auto& replacement_queue = bufferPool->replacement_queue;
    if (page_table.find(page_id) != page_table.end()) {
        Frame* frame = page_table[page_id];
        if(frame->pin_count > 0) {
            frame->pin_count--;
        }else {
            std::cout << "esta página ya está liberada" << std::endl;
        }
        frame->dirty = dirty;
        std::cout << "Unpinned página " << page_id << " en el frame " << frame->frame_id << ". Pin count: " << frame->pin_count << ". Dirty: " << frame->dirty << std::endl;
        if (frame->pin_count == 0) {
            replacement_queue.push_back(frame);
            if (policy == LRU) {
                // Ordenar por last_used en orden ascendente para LRU
                replacement_queue.sort([](Frame* a, Frame* b) { return a->last_used < b->last_used; });
            } else if (policy == MRU) {
                // Ordenar por last_used en orden descendente para MRU
                replacement_queue.sort([](Frame* a, Frame* b) { return a->last_used > b->last_used; });
            }
        }
    }
}

// carga una página en el buffer pool
// con un page_id y un bloque de datos
Frame* BufferPool::loadPage(int block_id,int policy) {
    auto& page_table = bufferPool->page_table;
    Frame* frame = getFreeFrame();

    // si no hay frames libres, se elige una página para reemplazar
    if (frame == nullptr) {
        frame = evictPage(policy);
    }
    if (frame == nullptr) {
        std::cout << "No hay frames disponibles para cargar la página " << block_id << std::endl;
        return nullptr;
    }
    // se designa al frame la nueva página
    frame->page = new Page(block_id);
    page_table[block_id] = frame;
    frame->pin_count = 1;
    frame->last_used = getCurrentTime();
    frame->reference_bit = true; // Inicializa el bit de referencia
    page_table[block_id] = frame;
    std::cout << "Se cargó la página " << block_id << " en el frame " << frame->frame_id << ". Pin count: " << frame->pin_count << std::endl;
    return frame;
}

// imprime cada frame y el id de la página que contiene
void BufferPool::showFrames(int policy) {
    auto frames = bufferPool->frames;
    int clock_hand = bufferPool->clock_hand;
    // imprime cada frame y el id de la página que contiene
    std::cout << "############################################\n";
    for (auto& frame : frames) {
        std::cout << "#  Frame: " ;
        std::cout << std::setw(5)<< frame->frame_id << "   ";
        std::cout << "Page: " ;
        if (frame->page != nullptr) {
            std::cout << std::setw(4)<< frame->page->page_id ;
            std::cout << "     Pin count: " ;
            std::cout << std::setw(4)<< frame->pin_count << "  ";
            std::cout << "Dirty: " ;
            std::cout << std::setw(4)<< frame->dirty << "  ";
            if(policy==1||policy==2){
                std::cout << "Last Used: " ;
                auto replacement_queue = bufferPool->replacement_queue;
                int pos = 0;
                for(auto it = replacement_queue.begin(); it != replacement_queue.end(); ++it, ++pos){
                    if((*it)->frame_id == frame->frame_id){
                        std::cout << std::setw(4) << pos+1 ;
                        break;
                    }
                }
                std::cout << std::endl;
            }
            if(policy==3){
            std::cout << "Bit Reference: " ;
            std::cout << std::setw(4)<< frame->reference_bit << std::endl;}
        } else {
            std::cout << std::setw(4)<< 'X'<< std::endl;
        }
    }
    if(policy==3){
    std::cout << "Clock hand: " ;
    std::cout << std::setw(4)<< clock_hand << std::endl;}
    std::cout << "############################################\n";
}
