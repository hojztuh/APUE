#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#define PATH "/etc/"

int main() {
    DIR *p = opendir(PATH);
    struct  dirent *d;
    
    if (p == NULL) {
        perror("oepndir() error!");
        exit(1);
    }

    while ((d = readdir(p)) != NULL) puts(d->d_name);

    closedir(p);
}