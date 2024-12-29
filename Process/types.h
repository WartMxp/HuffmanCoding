#pragma once

#include <bemapiset.h>

#define TEXT_SIZE 4096
#define BUFFER_SIZE 2048
#define CODE_SIZE 2048
#define VARIABLE_SIZE 256

extern unsigned char code[CODE_SIZE];
extern int code_size;

typedef unsigned char Datatype;
typedef struct HTNode { //霍夫曼树节点
    Datatype character; //字符
    int weight; //权
    int parent; //父节点
    int left_child, right_child; //左孩子，右孩子
} HuffmanTreeNode;
typedef struct HTree {
    HuffmanTreeNode* data;
    size_t size;
} HuffmanTree;
typedef struct P {
    size_t textLength;
    char* text;
} Paragraph;
typedef struct CharFreq {
    char character;
    int weight;
    unsigned int code;
} CharWeight;
typedef struct KValue {
    BYTE key;
    BYTE value;
} KeyValue;

extern KeyValue* key_value;
extern char text[TEXT_SIZE];
extern int text_size;