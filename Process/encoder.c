#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // 添加此行以包含 INT_MAX 的定义
#include "../huffman.h"

void Select(HuffmanTree* HT, int end, int* index1, int* index2) {
    //检查点
    if (HT == NULL) {
      perror("Error: Failed to allocate memory for Huffman Tree");
      exit(EXIT_FAILURE);
    }
    //选出两个权值最小的点
    int min1 = INT_MAX, min2 = INT_MAX;
    *index1 = -1; *index2 = -1;
    for(int i = 0;i <= end;i ++) {
        if(HT -> data[i].parent == -1 && HT -> data[i].weight < min1) {
            min1 = HT -> data[i].weight;
            *index1 = i;
        }
    }
    for(int i = 0;i <= end;i ++) {
        if(i !=  *index1 && HT -> data[i].parent == -1 && HT -> data[i].weight < min2) {
            min2 = HT -> data[i].weight;
            *index2 = i;
        }
    }
}

HuffmanTree* CreateHuffmanTree(CharWeight* ChWeight, int n) {
    //初始化
    HuffmanTree* HT = malloc(sizeof(HuffmanTree));
    HT -> data = (HuffmanTreeNode*)malloc((2 * n - 1) * sizeof(HuffmanTreeNode)); // 修改此行
    HT -> size = 2 * n - 1;
    for(int i = 0;i < 2 * n - 1;i ++) {
        if(i < n) {
            HT -> data[i].weight = ChWeight[i].weight;
        }
        HT -> data[i].parent = -1;
        HT -> data[i].left_child = -1;
        HT -> data[i].right_child = -1;
    }
    //生长
    for(int i = n;i < 2 * n - 1;i ++) {
        int index1, index2;
        Select(HT, i - 1, &index1, &index2);
        //重置父节点
        HT -> data[index1].parent = i;
        HT -> data[index2].parent = i;
        //合并
        HT -> data[i].left_child = index1;
        HT -> data[i].right_child = index2;
        HT -> data[i].weight = HT -> data[index1].weight + HT -> data[index2].weight;
    }
    return HT;
}

void CreateHuffmanCodes(HuffmanTree* HT, CharWeight* ChWeight, int freq) {
    //生成霍夫曼编码
    for (int i = 0; i < freq; i ++) {
        int current = i;
        int parent = HT -> data[current].parent;
        unsigned int code = 0;
        int length = 0;

        while (parent != -1) {
            code <<= 1;
            if (HT -> data[parent].left_child == current) {
                code |= 0;
            } else {
                code |= 1;
            }
            current = parent;
            parent = HT -> data[current].parent;
            length++;
        }

        // 反转编码
        unsigned int reversed_code = 0;
        for (int j = 0; j < length; j ++) {
            reversed_code <<= 1;
            reversed_code |= (code & 1);
            code >>= 1;
        }

        ChWeight[i].code = reversed_code;
    }
}

unsigned char code[CODE_SIZE];
int code_size = 0;

void SaveHuffmanCodes(const CharWeight* ChWeight, size_t size, Paragraph* paragraph) {
    code[code_size ++] = size;

    for (int i = 0; i < size; i ++) {
        code[code_size ++] = ChWeight[i].character;
        code[code_size ++] = ChWeight[i].code;
    }
    for (int i = 0; i < paragraph -> textLength; i++) {
        for (int j = 0;j < size; j ++) {
            if (paragraph -> text[i] == ChWeight[j].character) {
                code[code_size ++] = ChWeight[j].code;
                break;
            }
        }
    }
}

