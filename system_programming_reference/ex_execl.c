#include<unistd.h>
#include<stdio.h>

/* execl() 시스템콜로 vi를 실행. */

int main(int argc, char** argv) {
    int ret;

    ret=execl("/usr/bin/vi","vi",NULL);
    if (ret == -1) {
        perror("execl");
        return -1;
    }
    return 0;
}