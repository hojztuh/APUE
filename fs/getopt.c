/*
1. 支持如下可选项
    -y: year
    -m: month
    -d: day
    -H: hour
    -M: minute
    -S: second
2. 支持选项传参: -y和-H
3. 支持非选项传惨
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

int main(int argc, char *argv[]) {
    FILE *fp = stdout;
    char buf[SIZE];
    char c;
    char fmstr[SIZE];
    fmstr[0] = '\0';


    time_t stamp;
    stamp = time(NULL);

    struct tm* t;
    t = localtime(&stamp);

    while (1) {
        c = getopt(argc, argv, "-y:mdH:MS");
        if (c == -1) break;

        switch (c)
        {
            case 1: // 实现非选项的传参
                fp = fopen(argv[optind-1], "w");
                if (fp == NULL) {
                    perror("fopen()");
                    fp = stdout;
                } 
                break;
            case 'y':
                if (strcmp(optarg, "2") == 0)
                    strcat(fmstr, "%y ");
                else if (strcmp(optarg, "4") == 0)
                    strcat(fmstr, "%Y ");
                else {
                    fprintf(stderr, "Invalid argument of y!\n");
                    exit(1);
                }
                break;
            case 'm':
                strcat(fmstr, "%m ");
                break;
            case 'd':
                strcat(fmstr, "%d ");
                break;
            case 'H':
                if (strcmp(optarg, "12") == 0)
                    strcat(fmstr, "%I(%P) ");
                else if (strcmp(optarg, "24") == 0)
                    strcat(fmstr, "%H ");
                else {
                    fprintf(stderr, "Invalid argument of H!\n");
                    exit(1);
                } 
                break;
            case 'M':
                strcat(fmstr, "%M ");
                break;
            case 'S':
                strcat(fmstr, "%S ");
                break;
            default:
                break;
        }
    }
    
    strcat(fmstr, "\n");
    strftime(buf, SIZE, fmstr, t);
    fputs(buf, fp);

    if (fp != stdout) fclose(fp);
    return 0;
}