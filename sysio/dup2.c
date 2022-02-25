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

    fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open()");
        exit(1);
    } 

    // 问题:close和dup不是原子操作！
    /*
    close(1); // 这样1号坑位空了
    dup(fd);  // 1号坑位指向fd指向到结构体
    */
    // 解决:使用dup2
    // 问题: 如果fd本身是1会造成什么问题? 会fd=1会被关掉。故需要对close进行判断
    dup2(fd, 1);
    if (fd != 1) close(fd); // 释放fd

    /************************************/
    puts("Hello");

    // 需要还原现场，让fd=1处指向stdout

    return 0;
}