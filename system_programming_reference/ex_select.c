/*
다중입출력
select() 사용 예제
*/



#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5
#define BUF_LEN 1024

int main(int argc, char** argv) {
    struct timeval tv;
    fd_set readfs;
    int ret;

    /* 표준 입력에서 입력을 기다릭 위한 준비 */
    FD_ZERO(&readfs);
    FD_SET(STDIN_FILENO, &readfs);

    /* select가 5초동안 기다리도록 timeval 구조체 설정 */
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    /* 입력을 기다림 */
    ret = select(STDIN_FILENO + 1, &readfs, NULL, NULL, &tv);
    if(ret == -1) {
        perror("select");
        return 1;
    } else if(!ret) {
        printf("%d seconds elapsed.\n",TIMEOUT);
        return 0;
    }

    /* 여기까지 오면 select가 0이 아닌 양수를 반환했다는 의미이다.
    파일 디스트립터에서 즉시 읽기가 가능하다.*/

    if(FD_ISSET(STDIN_FILENO, &readfs)) {
        char buf[BUF_LEN+1];
        int len;

        len = read(STDIN_FILENO, buf, BUF_LEN);
        if(len == -1) {
            perror("read");
            return 1;
        }

        if(len) {
            buf[len] = '\0';
            printf("read : %s\n", buf);
        }

        return 0;
    }

    fprintf(stderr, "this should not happen!\n");
    return 1;
}