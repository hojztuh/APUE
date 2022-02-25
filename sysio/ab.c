/*
功能：证明标准I/O和系统I/O不适合混用
$strace ./ab
write(1, "b", 1b)                        = 1
write(1, "b", 1b)                        = 1
write(1, "b", 1b)                        = 1
write(1, "aaa", 3aaa)                      = 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    putchar('a');
    write(1, "b", 1);

    putchar('a');
    write(1, "b", 1);

    putchar('a');
    write(1, "b", 1);
}