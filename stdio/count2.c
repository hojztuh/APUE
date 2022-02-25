/*
功能：使用fseek()和ftell()函数计算一个文件的字节数
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror("fopen()");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    printf("cnt:%ld\n", ftell(fptr));

    return 0;
}