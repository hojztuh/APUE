#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {

    FILE* fp = fopen("tmp", "r");
    if (fp == NULL) {
        // 错误处理的三种方式
        fprintf(stderr, "ERROR: %d\n", errno);  // errno -> err message
        perror("fopen()");
        fprintf(stderr, "fopen(): %s\n", strerror(errno));
        exit(1);
    }

    fclose(fp);
    return 0;    
}