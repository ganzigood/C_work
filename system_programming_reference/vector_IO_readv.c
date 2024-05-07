/*
벡터 입출력
readv() 예제

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

int main(int argc, char** argv) {
    char foo[45], bar[45], baz[45];
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    fd=open("vector_ex", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    } 

    /* iovec 구조체를 초기화한다. */
    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    /* 단 한 번의 호출로 iov로 데이터를 읽어온다. */
    nr = readv(fd, iov, 3);
    if (nr == -1) {
        perror("readv");
        return 1;
    }

    for (i=0; i<3 ; i++){
        printf("%d: %s",i,(char*)iov[i].iov_base);
    }

    if (close(fd)) {
        perror("close");
        return 1;
    }

    return 0;
}