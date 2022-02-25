/*
功能：用fgetc和fputc实现一个简单的cpy
数据流向：文件->内存->文件
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    FILE* fr, *fw;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src_file> <dst_file>\n", argv[0]);
        exit(1);
    }

    fr = fopen(argv[1], "r");
    if (fr == NULL) {
        perror("fopen()");
        exit(1);
    }
    fw = fopen(argv[2], "w");
    if (fw == NULL) {
        perror("fopen()");
        exit(1);
    }

    while (1) {
        c = fgetc(fr);
        if (c == EOF) break;
        fputc(c, fw);
    }

    fclose(fw);
    fclose(fr);

    return 0;
}