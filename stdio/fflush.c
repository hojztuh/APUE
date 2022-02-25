/*
    当在stdin里输入足够多的字符的时候，标准输入缓冲区就满了，会自动清空缓冲区，紧接着执行下一句printf语句
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    c = getchar();

    printf("*****END!!!****%c\n", c);
    return 0;
}
