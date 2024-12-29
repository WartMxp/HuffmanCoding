#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../huffman.h"

static FILE* file = NULL;
void setOutputStream(FILE* stream) {
    file = stream;
}
void CompressPrint() {
    if (file == NULL) {
        perror("Error: No file specified\n");
        exit(EXIT_FAILURE);
    }
    if(code_size >= TEXT_SIZE) {
        perror("Error: Code array overflow\n");
        exit(EXIT_FAILURE);
    }
    fwrite(code, sizeof(char), code_size, file);
    memset(code, 0, sizeof(char) * CODE_SIZE);
    code_size = 0;
}
void DecompressPrint() {
    if (file == NULL) {
        perror("Error: No file specified\n");
        exit(EXIT_FAILURE);
    }
    if(code_size >= TEXT_SIZE) {
      perror("Error: Code array overflow\n");
      exit(EXIT_FAILURE);
    }
    fwrite(text, sizeof(char), text_size, file);
}
