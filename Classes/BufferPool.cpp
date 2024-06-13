#include "BufferPool.h"

int BufferPool::getSize() const {
    return size;
}

void BufferPool::setSize(int size) {
    this->size = size;
}

std::vector<Frame *> BufferPool::getFrames() const {
    return frames;
}

void BufferPool::setFrames(const std::vector<Frame *> &frames) {
    this->frames = frames;
}

std::unordered_map<int, Frame *> BufferPool::getPageTable() const {
    return page_table;
}

void BufferPool::sePageTable(const std::unordered_map<int, Frame *> &page_table) {
    this->page_table = page_table;
}

std::list<Frame *> BufferPool::getReplacementQueue() const {
    return replacement_queue;
}

void BufferPool::setReplacementQueue(const std::list<Frame *> &replacement_queue) {
    this->replacement_queue = replacement_queue;
}

int BufferPool::getClockHand() const {
    return clock_hand;
}

void BufferPool::setClockHand(int clock_hand) {
    this->clock_hand = clock_hand;
}
