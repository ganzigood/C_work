/*
벡터 입출력 
writev() 예제
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

int main(int argc, char** argv) {
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;

    char* buf[] = {
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.\n",
      "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb.\n",
      "cccccccccccccccccccccccccccccccccccccccccc.\n"};

    fd = open("vector_ex", O_WRONLY | O_CREAT | O_TRUNC);
    if(fd == -1) {
        perror("open");
        return 1;
    }

    /* 세 iovec 구조체에 값을 채운다. */
    for(i=0; i<3; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }
    
    /* 단 한 번의 호출로 세 iovec 내용을 모두 쓴다.*/
    nr = writev(fd, iov, 3);
    if (nr == -1) {
        perror("writev");
        return 1;
    }
    printf("wrote %ld bytes\n", nr);

    if (close(fd)) {
        perror("close");
        return 1;
    }

    return 0;
}