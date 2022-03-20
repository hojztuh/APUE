/*
    功能: 演示钩子函数
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f1(void) {
    puts("f1");
}

void f2(void) {
    puts("f2");
}

void f3(void) {
    puts("f3");
}

int main() {
    puts("Begin!");

    atexit(f1);
    atexit(f2);
    atexit(f3);

    puts("End!");
    /*使用_exit则不会调用钩子函数*/
    // _exit(0); 
    exit(0);
}