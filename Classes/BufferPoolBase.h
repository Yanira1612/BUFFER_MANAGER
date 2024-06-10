//
// Created by alonso on 6/10/24.
//

#ifndef BUFFERPOOLBASE_H
#define BUFFERPOOLBASE_H

#include <vector>
#include  <unordered_map>
#include <list>
#include <ctime>
#include "Frame.h"


class BufferPoolBase {
private:

    static const int LRU = 1;
    static const int MRU = 2;
    static const int CLOCK = 3;

    int size; // Tamaño del buffer pool en número de frames
    std::vector<Frame*> frames; // Vector de frames
    std::unordered_map<int, Frame*> page_table; // Tabla de páginas para mapear page_id a frames
    std::list<Frame*> replacement_queue; // Lista enlazada para el algoritmo LRU
    int clock_hand;
    friend class BufferPool;
public:
    BufferPoolBase(int size, const std::vector<Frame *> &frames, const std::unordered_map<int, Frame *> &page_table,
        const std::list<Frame *> &replacement_queue, int clock_hand)
        : size(size),
          frames(frames),
          page_table(page_table),
          replacement_queue(replacement_queue),
          clock_hand(clock_hand) {
    }
    BufferPoolBase(int size) : size(size), clock_hand(0) {
        for (int i = 0; i < size; ++i) {
            frames.push_back(new Frame(i));
        }
    }

    // Destructor de BufferPool
    ~BufferPoolBase() {
        for (auto& frame : frames) {
            delete frame;
        }
    }

    int getSize() const;

    void setSize(int size);

    std::vector<Frame *> getFrames() const;

    void setFrames(const std::vector<Frame *> &frames);

    std::unordered_map<int, Frame *> getPageTable() const;

    void sePageTable(const std::unordered_map<int, Frame *> &page_table);

    std::list<Frame *> getReplacementQueue() const;

    void setReplacementQueue(const std::list<Frame *> &replacement_queue);

    int getClockHand() const;

    void setClockHand(int clock_hand);
};



#endif //BUFFERPOOLBASE_H
