#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/user.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("start\n");
    printf("Hello World\n");
    __off_t a;
   
    int b;
    size_t c;
    off_t gg;
    gg = 12;

    char* buf[] = {"aaaaaa","bbbbbb"};

    printf("buf size : %ld\n", strlen(buf[0]));
    printf("__off_t size : %ld\n",sizeof(off_t));
    printf("off_t : %ld,  gg = %ld\n",sizeof(off_t), gg);
    printf("fpos_t : %ld\n", sizeof(fpos_t));
    printf("size_t : %ld\n", sizeof(size_t));
    printf("ssize_t : %ld\n", sizeof(ssize_t));
    printf("long long : %ld\n", sizeof(long long));
    printf("long long int : %ld\n", sizeof(long long int));
    printf("float : %ld\n", sizeof(float));
    printf("double : %ld\n", sizeof(double));
    printf("long : %ld\n", sizeof(long));
    printf("page size(long type, sysconf function) : %ld\n", sysconf(_SC_PAGESIZE));
    printf("page size(int type, getpagesize function) : %d\n", getpagesize());
    printf("page size(int type, use PAGE_SIZE macro) : %ld\n\n", PAGE_SIZE);

    return 0;
}