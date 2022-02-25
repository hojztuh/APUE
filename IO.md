## I/O概述

+ I/O是一切实现的基础
+ I/O可以分为标准I/O(stdio)和系统调用I/O(sysio)
+ 优先使用标准I/O
+ stdio->sysio->kernel：比如fopen函数在Linux环境下依赖系统调用open，在Windows环境下依赖系统调用openfile

## 标准I/O

***stdio: FILE类型贯穿始终（其实是一个结构体）***

###打开和关闭

#### fopen()和fclose()

+ fopen();

`FILE *fopen(const char *pathname, const char *mode);`

const表明，传入的pathname和mode在函数fopen内部不会被改动

Upon successful completion fopen() returns a FILE pointer.  Otherwise, NULL  is  returned and **errno** is set to indicate the error.

errno可以理解为一个全局变量，一旦程序出错，errno就会被更新，进一步了解errno可以查看man手册，或查看`/usr/include/asm-generic`目录下的errno.h和errno-base.h文件。errno最开始是一个整型，现在被重构成了一个宏。

fopen返回的指针指向的空间在**堆**里（因为存在fclose这个**释放**操作）

**是资源就一定有上限: **测试在一个进程的空间里最多可以用fopen打开多少个文件

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {

    FILE* fp = NULL;
    int count = 0;
    
    while (1) {
        fp = fopen("tmp", "r");
        if (fp == NULL) {
            perror("fopen()");
            break;
        }
        count++;
    }
    printf("count:%d\n", count);
    return 0;    
}
```



fopen创建的文件都权限是`0666 & ~umask`其中`0666`表示八进制的`666`即二进制的`110110110`

+ fclose();

本质上是用free函数回收堆里的空间

### 读写

#### fgetc()和fputc()

```c
// 使用fgetc()和fputc()可以实现一个简单的cpy命令
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    FILE* fr, *fw;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src_file> <dst_file>\n", argv[0]);
        exit(1);
    }

    fr = fopen(argv[1], "r");
    if (fr == NULL) {
        perror("fopen()");
        exit(1);
    }
    fw = fopen(argv[2], "w");
    if (fw == NULL) {
        perror("fopen()");
        exit(1);
    }

    while (1) {
        c = fgetc(fr);
        if (c == EOF) break;
        fputc(c, fw);
    }

    fclose(fw);
    fclose(fr);

    return 0;
}
```

#### fgets()和fputs()

`fgets(*, SIZE, stream)`最多读SIZE-1个字符，正常退出有2种情况

（1）已经读了SIZE-1个字符

（2）读到了'\n'

如果SIZE = 5，则一个文件的内容如果是abcd的话，用fgets会读2次

（1）a b c d '\0'

（2）'\n' '\0'

#### fread()和fwrite()

`size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`

从stream读到ptr处，读size*nmemb个字节，nmemb是对象的数量，size是每个对象的大小

返回值：On  success,  fread() and fwrite() return **the number of  items** read or written.  This number equals the number of
       bytes transferred only when size is 1.  If an error occurs, or the end of the file is reached, the return  value
       is **a short item count (or zero)**.

以一次读10个字节为例，比较下列两个函数调用的区别

+ A: fread(buf, 1, 10, fp)：一次读10个对象，一个对象1个字节
+ B: fread(buf, 10, 1, fp)：一次读1个对象，一个对象10个字节

1. 文件中数据量足够：A返回10，B返回1
2. 文件中只有5个字节：A返回5，B返回0

fread和fwrite适合数据非常工整的情况



### 输入输出

#### printf()和scanf()

fprintf()

sprintf()

### 文件位置指针

#### fseek(), ftell()和rewind()

<img src="https://gitee.com/hojztuh/My_Img/raw/master/Img/image-20220222215614707.png" alt="image-20220222215614707" style="zoom:50%;" />

+ fseek()：用来移动文件位置指针

+ ftell()：用来返回文件位置指针的当前位置

+ rewind(stream) 等价于 (void) fseek(stream, 0L, SEEK_SET);

fseek和stell存在的**BUG**

```c
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
```

long 类型定义，最多支持大约2G大小的文件

如何解决？可以考虑用fseeko和ftello

defining **_FILE_OFFSET_BITS** with  the  value  64 (before including any header files) will turn off_t into a 64-bit type

`gcc test.c -o test -D _FILE_OFFSET_BITS=64`

或者使用makefile

```makefile
CFLAGS+= -D _FILE_OFFSET_BITS=64
```

### 合并系统调用

#### fflush()

+ 行缓冲
+ 全缓冲
+ 无缓冲

这部分需要系统研究一下**C语言的缓冲区**

可以参考博客：https://zhuanlan.zhihu.com/p/54990226

https://blog.csdn.net/qq_36532097/article/details/70197061

### 获取一行的内容

#### getline()

```c
// 指针也是一种变量，只不过它的内存单元中保存的是一个标识其他位置的地址。由于地址也是整数，在32位平台下，指针默认为32位。
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

// 调用getline之前line初始为NULL，n初始为0
char* line = NULL;
int n = 0;
getline(&line, &n, stream);

```



<img src="https://gitee.com/hojztuh/My_Img/raw/master/Img/image-20220223134534628.png" alt="image-20220223134534628" style="zoom:50%;" />

### 临时文件

1. 如何不冲突：使用**匿名文件**
2. 及时销毁

临时文件是指需要临时创建、使用，但不需要长久保存的文件，临时文件可以放到`/tmp`目录下

#### tmpnam()和tmpfile()



## 系统调用I/O

***sysio:文件描述符fd贯穿始终***

### 文件描述符

+ 文件描述符fd本质上是一个整形数字（数组下标）

+ 文件描述符fd优先使用当前可用范围内**最小的一个**

<img src="https://gitee.com/hojztuh/My_Img/raw/master/Img/image-20220223160549256.png" alt="image-20220223160549256" style="zoom:50%;" />

### 文件I/O操作

文件I/O操作：open, close, read, write, lseek

#### open()和close()

`       int open(const char *pathname, int flags);`

`int open(const char *pathname, int flags, mode_t mode);`

open是一个变参函数

flags本质上是一个**位图(bitmap)->位的映射**

flags一定要包含`O_RDONLY, O_WRONLY, O_RDWR`三个中的一个，除此之外，还可以选择性地包含**file craetion flags**和**file status flags**

```c
// 标准I/O的mode和系统I/O的flags之间的映射关系
r -> O_RDONLY
r+ -> ORDWR
w -> O_WRONLY | O_CREATE | O_TRUNC
w+ -> O_RDWR | O_CREATE | O_TRUNC
```

`int close(int fd);`

#### read(), write()和lseek()

```c
ssize_t read(int fd, void *buf, size_t count);	// 成功返回读取的字节数，读取的字节数可能<count或者等于0；失败返回-1
ssize_t write(int fd, const void *buf, size_t count); // 成功返回写入的字节数；失败返回-1
off_t lseek(int fd, off_t offset, int whence); // lseek的返回值是文件指针移动后的位置
```

### 文件I/O与标准I/O的区别

区别：响应速度&吞吐量

fwrite是写入进程的**写缓冲区**，满足一定条件才会整合**写缓冲区**的内容，一并调用write，写进真实的流/文件。（**合并系统调用**）

write则是实打实地由用户态切换为内核态，将内容写进真实的流/文件。（注意，内核也有缓冲区）

因此，fwrite吞吐量更大，响应速度慢，而write响应速度快，吞吐量小。

提醒：标准I/O和文件I/O不可混用（由于标准I/O进程中缓冲区的存在，FILE*对应的结构体中的pos与fd对应的结构体中的pos往往是不一样的！）

```c
// 标准I/O与文件I/O的转换
int fileno(FILE *stream);	// FILE* -> fd
FILE *fdopen(int fd, const char *mode); // fd -> FILE*
```

### I/O效率问题

习题：修改mycpy.c程序，将SIZE的值进行放大（每次放大2倍），用time测试程序运行时间，记录性能最佳拐点出现时的BUFSIZE值，以及程序何时会出问题。

### 文件共享

多个任务共同操作一个文件或者协同完成任务

例：写程序删除一个文件的第10行。

```c
/**********************************/
1->open r ->fd1 ->lseek 11
2->open r+ ->fd2 ->lseek 10
  
while () {
  fd1->read
  fe2->write
}
/**********************************/
process1->open->r
process2->open->r+
p1->read -> p2->write
/**********************************/

```

补充函数：truncate/ftruncate.

### 其他

+ 原子操作

+ dup和dup2: 复制文件描述符
+ 同步：sync, fsync, fdatasync
+ fcntl(): 文件描述符所变的魔术几乎都来源于该函数
+ ioctl(): 设备相关的内容
+ /dev/fd目录: 虚目录，记录**当前**进程的文件描述符的信息

