#pragma once
#include "Types.h"
#include "../huffman.h"

void Select(HuffmanTree* HT, int end, int* index1, int* index2);
HuffmanTree* CreateHuffmanTree(CharWeight* ChWeight, int n);
void CreateHuffmanCodes(HuffmanTree* HT, CharWeight* ChWeight, int freq);
void SaveHuffmanCodes(const CharWeight* ChWeight, size_t size, Paragraph* paragraph);