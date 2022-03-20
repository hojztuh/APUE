/*
    功能: 输入gid，输出group name
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <group_id>\n", argv[0]);
        exit(1);
    }

    struct group *p;
    p = getgrgid(atoi(argv[1]));

    puts(p->gr_name);
    return 0;
}