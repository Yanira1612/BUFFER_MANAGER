cmake_minimum_required(VERSION 3.10)
project(BUFFER_MANAGER)

set(CMAKE_CXX_STANDARD 14)

add_executable(BUFFER_MANAGER main.cpp
        Classes/Block.h
        Classes/BufferManager.h
        Classes/BufferPool.h
        Classes/Frame.h
        Classes/Page.h
        Classes/BufferPoolBase.cpp
        Classes/BufferPoolBase.h)