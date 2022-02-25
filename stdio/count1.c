/*
功能：使用fgetc函数计算一个文件的字节数
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int cnt = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror("fopen()");
        exit(1);
    }

    while (fgetc(fptr) != EOF) {
        cnt++;
    }

    printf("cnt:%d\n", cnt);

    return 0;
}