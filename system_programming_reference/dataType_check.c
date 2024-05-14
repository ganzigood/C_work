/*
test 용 코드

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/user.h>
#include <string.h>

int main(int argc, char** argv) {

    size_t c;
    off_t offset;
    char* buf[] = {"aaaaaa","bbbbbb"};

    printf("size of pid_t : %ld\n", sizeof(pid_t));
    printf("buf size : %ld\n", strlen(buf[0]));
    printf("off_t : %ld,  gg = %ld\n",sizeof(off_t), offset);
    printf("fpos_t : %ld\n", sizeof(fpos_t));
    printf("size_t : %ld\n", sizeof(size_t));
    printf("ssize_t : %ld\n\n", sizeof(ssize_t));
    
    printf("long long : %ld\n", sizeof(long long));
    printf("long long int : %ld\n", sizeof(long long int));
    printf("float : %ld\n", sizeof(float));
    printf("double : %ld\n", sizeof(double));
    printf("long : %ld\n\n", sizeof(long));

    printf("page size(long type, sysconf function) : %ld\n", sysconf(_SC_PAGESIZE));
    printf("page size(int type, getpagesize function) : %d\n", getpagesize());
    printf("page size(int type, use PAGE_SIZE macro) : %ld\n", PAGE_SIZE);

    printf("My pid = %d\n", getpid());
    printf("Parent's pid = %d\n\n",getppid());    

    printf("저장된 사용자 ID : %d\n\n", _POSIX_SAVED_IDS);
    printf("uid : %d\n\n", getuid());

    printf("nice value = %d \n\n", nice(0));

    return 0;


}