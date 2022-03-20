#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

// static表示禁止函数向外扩展
static off_t flen(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("stat()");
        exit(1);
    }   
    return st.st_size;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    /*
    可以用tags工具查看off_t的定义
    $vim -t FILE
    $vim -t off_t
    */

    off_t len = flen(argv[1]);

    printf("%lld\n", len); 

    return 0;
}