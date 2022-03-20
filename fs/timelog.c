/*
    功能:实现一个时间日志
    可以用$tail -f /tmp/out查看文件的动态变化
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FILENAME "/tmp/out"
#define SIZE 1024

int main() {
    time_t stamp;
    struct tm *t;
    char buf[SIZE];
    FILE *f = fopen(FILENAME, "a+");
    if (f == NULL) {
        perror("fopen()");
        exit(1);
    }

    int cnt = 0;

    while (fgets(buf, SIZE, f) != NULL) cnt++;

    while (1) {
        time(&stamp);
        t = localtime(&stamp);
        // 1 2022-3-11 3:00:21
        fprintf(f, "%-4d%d-%d-%d %d:%d:%d\n", ++cnt, t->tm_year + 1900, \
        t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        fflush(f);  // 这步非常重要!

        sleep(1);
    }

    fclose(f);

}