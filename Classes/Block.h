#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <fstream>
class Block {
public:
    std::string pathDisk; // path del archivo en disco
    int blockId;          // id del bloque
    Block(){}
    Block(int _blockId) {
        blockId = _blockId;
        pathDisk = "Disk/Block" + std::to_string(blockId) + ".txt";
    }
};
#endif //BLOCK_H
