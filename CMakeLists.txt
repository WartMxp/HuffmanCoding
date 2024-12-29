cmake_minimum_required(VERSION 3.30)
project(HuffmanCoding C)

set(CMAKE_C_STANDARD 11)

add_library(huffman
        huffman.h
        Process/encoder.c
        Process/encoder.h
        Process/input.c
        Process/input.h
        Process/output.c
        Process/output.h
        Process/types.h
)

add_executable(HuffmanCoding
        main.c
)

target_link_libraries(HuffmanCoding huffman)