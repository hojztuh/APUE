/*
    功能: 命令行输入用户名，接下来对该用户进行密码校验
    编译: $gcc chkpass.c -o chkpass -lcrypt
    运行: 需要用root用户运行
*/
#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <user_name>\n", argv[0]);
        exit(1);
    }

    char *input = getpass("Input password:");

    struct spwd *sd;
    sd = getspnam(argv[1]);

    char *output = crypt(input, sd->sp_pwdp); // 第二个参数只截取$id$salt$这部分，后面的都被忽略了

    if (strcmp(sd->sp_pwdp, output) == 0) puts("Ok!");
    else puts("No!");

    return 0;
}