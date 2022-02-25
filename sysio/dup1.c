/*
    功能:将puts的内容重定向到FILE_NAME里
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "/tmp/out"

int main() {
    int fd;

    close(1);

    fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open()");
        exit(1);
    } 



    /************************************/
    puts("Hello");

    return 0;
}