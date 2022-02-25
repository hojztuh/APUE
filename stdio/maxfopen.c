#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {

    FILE* fp = NULL;
    int count = 0;
    
    while (1) {
        fp = fopen("tt", "w");
        if (fp == NULL) {
            perror("fopen()");
            break;
        }
        printf("%d\n", fileno(fp)); // shows each fd number
        count++;
    }
    printf("count:%d\n", count);
    getchar(); // just to keep it running
    return 0;    
}