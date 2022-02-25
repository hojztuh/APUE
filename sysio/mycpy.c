#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// 128B -> 16M 
#define SIZE 1024

int main(int argc, char *argv[]) {
    int sfd, dfd;
    char buf[SIZE];
    int len, ret, pos;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src_file> <dst_file>\n", argv[0]);
        exit(1);
    }

    sfd = open(argv[1], O_RDONLY);
    if (sfd < 0) {
        perror("open()");
        exit(1);
    }
    
    dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600); // 如果flags用到了O_CREAT，最后一定要填mode
    if (dfd < 0) {
        perror("open()");
        exit(1);
    }

    // 在循环中加入计数器
    while (1) {
        len = read(sfd, buf, SIZE);
        if (len < 0) {
            perror("read()");
            break;
        } 
        if (len == 0) break;

        // 写的时候要循环地写
        pos = 0;
        while (len > 0) {
            ret = write(dfd, buf+pos, len);
            if (ret < 0) {
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;
        }
        if (write(dfd, buf, len) < 0) {
            perror("write()");
            break;
        }
    }

    close(dfd);
    close(sfd);

    return 0;
}