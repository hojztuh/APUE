#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// dcb-lsp
static int ftype(const char *fname) {
    struct stat st;
    if (stat(fname, &st) == -1) {
        perror("stat()");
        exit(1);
    }
    if (S_ISDIR(st.st_mode)) return 'd';
    else if (S_ISCHR(st.st_mode)) return 'c';
    else if (S_ISBLK(st.st_mode)) return 'b';
    else if (S_ISREG(st.st_mode)) return '-';
    else if (S_ISLNK(st.st_mode)) return 'l';
    else if (S_ISSOCK(st.st_mode)) return 's';
    else if (S_ISFIFO(st.st_mode)) return 'p';
    else return '?';
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    printf("%c\n", ftype(argv[1]));

    return 0;
}