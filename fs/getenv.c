#include <stdio.h>
#include <stdlib.h>

int main() {
    char *s = getenv("PATH");
    puts(s);
}