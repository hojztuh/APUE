#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;


    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror("fopen()");
        exit(1);
    }

    while ((nread = getline(&line, &len, fptr)) != -1) {
        printf("%zu\n", nread);
        printf("%lu\n", len);
        fwrite(line, nread, 1, stdout);
    }

    fclose(fptr);
}