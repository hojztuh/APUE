/*
    功能: 输入user id，输出user name
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <user_id>\n", argv[0]);
        exit(1);
    }

    struct passwd *p;
    p = getpwuid(atoi(argv[1]));

    puts(p->pw_name);
    // puts(p->pw_passwd);

    return 0;
}