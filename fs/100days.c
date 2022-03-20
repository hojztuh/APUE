/*
    功能: 输出100天之后的日期
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024

int main() {
    char buf[SIZE];
    time_t stamp;
    stamp = time(NULL);

    struct tm* t;
    t = localtime(&stamp);
    
    strftime(buf, SIZE, "%Y-%m-%d", t);
    printf("Today is %s\n", buf);


    t->tm_mday += 100;
    mktime(t); // t会被重新格式化
    strftime(buf, SIZE, "%Y-%m-%d", t);
    printf("100 days later is %s\n", buf);

    return 0;
}