/*
    功能:实现du命令，使用stat获取文件属性，glob进行目录解析
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define SIZE 1000000

int legal(const char *pathname) {
    char *pos;
    if ((pos = strrchr(pathname, '/')) == NULL) {
        fprintf(stderr, "strrchr() ERROR!\n");
        exit(1);
    }

    if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0) {
        return 0;
    }

    return 1;

}

static int64_t mydup(const char *pathname) {
    struct stat st;
    glob_t g;
    char path[SIZE];
    int64_t sum = 0;

    if (lstat(pathname, &st) == -1) {
        perror("lstat()");
        exit(1);
    }

    if (!S_ISDIR(st.st_mode)) {
        return st.st_blocks;
    }

    strncpy(path, pathname, SIZE);
    strcat(path, "/*");
    glob(path, 0, NULL, &g);

    strncpy(path, pathname, SIZE);
    strcat(path, "/.*");
    glob(path, GLOB_APPEND, NULL, &g);

    sum = st.st_blocks;
    for (int i = 0; i < g.gl_pathc; i++) {
        if (legal(g.gl_pathv[i])) {
            sum += mydup(g.gl_pathv[i]);
        }
    }

    globfree(&g);

    return sum;
    
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    int64_t res = mydup(argv[1]);

    printf("%ld\n", res / 2);

    return 0;

}