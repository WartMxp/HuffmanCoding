#ifndef TYPES_H
#define TYPES_H

typedef char Datatype;
typedef struct HTNode { //霍夫曼树节点
    int weight; //权
    int parent; //父节点
    int left_child, right_child; //左孩子，右孩子
} HuffmanTreeNode;
typedef struct HTree {
    HuffmanTreeNode* data;
    int size;
} HuffmanTree;
typedef struct CLArguments {
    FILE* input;
    FILE* output;
} CommandLineArgs;

#endif
