/*
创建一个占极小磁盘空间的大文件
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (fd == -1) {
        perror("open()");
        exit(1);
    }

    off_t res = lseek(fd, 5LL*1024LL*1024LL*1024LL-1LL, SEEK_SET);
    if (res == -1) {
        perror("lseek()");
        exit(1);
    }

    if(write(fd, "", 1) == -1) {
        perror("write()");
        exit(1);
    }

    close(fd);
    return 0;
}
