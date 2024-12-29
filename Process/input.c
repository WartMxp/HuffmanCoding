#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../huffman.h"

static FILE* file = NULL;

int CharCmp(const void* a, const void* b) {
    return ((CharWeight*)a) -> weight - ((CharWeight*)b) -> weight;
}

void setInputStream(FILE* stream) {
  	file = stream;
}

void StreamCheck() {
    if (file == NULL) {
        perror("No file specified\n");
        exit(EXIT_FAILURE);
    }
}

void Encode() {
    StreamCheck();

    int weight[257] = { 0 };
    Paragraph paragraph;
    char* txt = malloc(BUFFER_SIZE * sizeof(char));
    while (fgets(txt, BUFFER_SIZE, file)) { //以一段或BUFFER_SIZE为基准读取字符
        //在每段的开始初始化权重
        memset(weight, 0, 257 * sizeof(int));
        //没有什么必要的段落结构体
        paragraph.text = txt;
        paragraph.textLength = strlen(txt);

        if (paragraph.textLength > 1 && txt[0] != '\n') {

            int freq = 0; //记录字符出现的种类的数量
            for (int p = 0; p < paragraph.textLength; p++) {
                if (weight[(unsigned char)paragraph.text[p]] == 0) {
                    freq++;
                }
                weight[(unsigned char)paragraph.text[p]]++;
            }
            int point = 0;
            CharWeight* ChWeight = malloc((freq + 1) * sizeof(CharWeight));

            for (int ch = 0; ch < 257; ch ++) {
                if (weight[ch] != 0) {
                    ChWeight[point].character = (char)ch;
                    ChWeight[point ++].weight = weight[ch];
                }
            }
            qsort(ChWeight, freq, sizeof(CharWeight), CharCmp);//为字符按照权重排序
            //构建霍夫曼树并编码
            HuffmanTree* tree = CreateHuffmanTree(ChWeight, freq);
            CreateHuffmanCodes(tree, ChWeight, freq);
            SaveHuffmanCodes(ChWeight, freq, &paragraph);
            free(ChWeight);
            memset(txt, 0, BUFFER_SIZE * sizeof(char));
        }
    }
    free(txt);
    //终于结束了
    fclose(file);
}

KeyValue* key_value;
int text_size = 0;
char text[TEXT_SIZE];

void Decode() {
    StreamCheck();

    unsigned int char_freq = 0;
    fread(&char_freq, sizeof(char), 1, file);
    if (char_freq < 1) {
        perror("Error: Wrong format\n");
        exit(EXIT_FAILURE);
    }
    key_value = (KeyValue*)malloc((char_freq + 1) * sizeof(KeyValue));
    for (size_t i = 0; i < char_freq; i ++) {
        fread(&key_value[i].key, sizeof(BYTE), 1, file);
        fread(&key_value[i].value, sizeof(BYTE), 1, file);
    }
    BYTE code;
    while (fread(&code, sizeof(BYTE), 1, file)) {
        for (size_t p = 0; p < char_freq; p ++) {
            if (code == key_value[p].value) {
                if (text_size >= TEXT_SIZE) {
                    perror("Error: text array overflow\n");
                    exit(EXIT_FAILURE);
                }
                text[text_size++] = (char)key_value[p].key;
                break;
            }
        }
    }
    text[text_size] = '\0';
    //又要结束了
    free(key_value);
    fclose(file);
}
