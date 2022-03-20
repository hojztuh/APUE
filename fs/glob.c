/*
实现 "ls /etc/l*.conf和 ls /etc/*"

注意: "ls -a == ls ./* + ls ./.*"
*/
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

#define PATTERN "/etc/l*.conf"
#define ETC "/etc/*"

#if 0
static int errfunc_(const char *epath, int eerrno) {
    puts(epath);
    fprintf(stderr, "ERROR MSG:%s\n", strerror(eerrno));
    return 0;
}
#endif

int main() {

    glob_t g;
    int res = glob(ETC, 0, NULL, &g);
    if (res) {
        printf("Error code = %d\n", res);
        exit(1);
    }

    for (int i = 0; i < g.gl_pathc; i++) {
        puts(g.gl_pathv[i]);
    }

    globfree(&g);
    return 0;
}