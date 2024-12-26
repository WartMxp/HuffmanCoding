#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "huffman.h"

typedef struct CLArguments {
    FILE* input;
    FILE* output;
    int compress;
    int decompress;
} CommandLineArgs;

CommandLineArgs parseCommandArgs(int argc, char* argv[]);

int main(const int argc, char* argv[]) {
    CommandLineArgs args = parseCommandArgs(argc, argv);

    setInputStream(args.input);
    setOutputStream(args.output);

    if (args.compress) { //已经写完的编码
        Encode();
        CompressPrint();
    } else if (args.decompress) { //假装会写的解码
        fputs("少女祈祷中...\n", stdout);
        exit(EXIT_SUCCESS);
    }
    if (args.input != stdin) {
        fclose(args.input);
    }
    if (args.output != stdout) {
        fclose(args.output);
    }
    return 0;
}

CommandLineArgs parseCommandArgs(int argc, char* argv[]) {
    CommandLineArgs args;
    args.input = stdin;
    args.output = stdout;
    args.compress = 1;
    args.decompress = 0;

    int compressSeen = 0;
    int decompressSeen = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-of") == 0) {
            if (i + 1 < argc) {
                fputs("Output:", stdout);
                fputs(argv[i + 1], stdout);
                fputs("\n", stdout);
                if (args.compress || args.decompress) {
                  args.output = fopen(argv[i + 1], "wb");

                }
                if (args.output == NULL) {
                  perror("Error opening output file");
                  exit(EXIT_FAILURE);
                }
                i++;
                } else {
                    fputs("Error: --output option requires a file path.\n", stderr);
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(argv[i], "--input") == 0 || strcmp(argv[i], "-if") == 0) {
                if (i + 1 < argc) {
                    if (args.compress || args.decompress) {
                        args.input = fopen(argv[i + 1], "rb");
                    }
                    if (args.input == NULL) {
                        perror("Error opening input file");
                        exit(EXIT_FAILURE);
                    }
                    i++;
                } else {
                    fputs("Error: --input option requires a file path.\n", stderr);
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(argv[i], "--compress") == 0 ||
                strcmp(argv[i], "-c") == 0) {
                if (compressSeen) {
                  fputs("Error: --compress option requires a file path.\n", stderr);
                  exit(EXIT_FAILURE);
                }
                compressSeen = 1;
            } else if (strcmp(argv[i], "--decompress") == 0 ||
                strcmp(argv[i], "-dc") == 0) {
                if (decompressSeen) {
                  fputs("Error: --decompress option requires a file path.\n", stderr);
                  exit(EXIT_FAILURE);
                }
                args.decompress = 1;
                args.compress = 0;
                decompressSeen = 1;
            } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                setlocale(LC_ALL, "zh_CN.UTF-8");
                puts("\n用法: HuffmanCoding [选项]...\n");
                puts("对指定的由ASCII字符集进行霍夫曼编码，可选择压缩或解压缩。\n\n");

                puts("     -if, --input 指定输入文件（默认为标准输入）\n");
                puts("     -of, --output 指定输出文件（默认为标准输出）\n");
                puts("     -c, --compress 输出压缩后的文本至.z压缩文件中\n");
                puts("     -dc, --decompress 输出解压后的.z压缩文件至文本文档中\n");
                puts("     -h, --help 显示此帮助并退出\n\n");

                puts("实例：\n");
                puts("     HuffmanCoding -if text.txt -of code.z --compress\n");
                puts("     HuffmanCoding --input=text.txt --output=code.z --decompress\n\n");

                puts(
                    "注意：一、如果未指定输入或者输出文件，则程序将默认使用标准输入或标准"
                    "输出。\n");
                puts("     二、 --compress 与 --decompress 选项不能同时使用。\n");
                puts("     三、不支持宽字符与utf-8字符集。\n\n");
                exit(EXIT_SUCCESS);
            } else {
                fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
        if (args.input == NULL || args.output == NULL) {
            fputs("Error: input file is required.\n", stderr);
            exit(EXIT_FAILURE);
        }

      return args;
}
