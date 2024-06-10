//
// Created by alonso on 6/10/24.
//

#include "BufferPoolBase.h"

int BufferPoolBase::getSize() const {
    return size;
}

void BufferPoolBase::setSize(int size) {
    this->size = size;
}

std::vector<Frame *> BufferPoolBase::getFrames() const {
    return frames;
}

void BufferPoolBase::setFrames(const std::vector<Frame *> &frames) {
    this->frames = frames;
}

std::unordered_map<int, Frame *> BufferPoolBase::getPageTable() const {
    return page_table;
}

void BufferPoolBase::sePageTable(const std::unordered_map<int, Frame *> &page_table) {
    this->page_table = page_table;
}

std::list<Frame *> BufferPoolBase::getReplacementQueue() const {
    return replacement_queue;
}

void BufferPoolBase::setReplacementQueue(const std::list<Frame *> &replacement_queue) {
    this->replacement_queue = replacement_queue;
}

int BufferPoolBase::getClockHand() const {
    return clock_hand;
}

void BufferPoolBase::setClockHand(int clock_hand) {
    this->clock_hand = clock_hand;
}
