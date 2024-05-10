/* 규칙에 따라서 스스로 데몬이 되는 예제 코드 */


#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/fs.h>

#define NR_OPEN 1024  // 리눅스에서 한 프로세스에서 열 수 있는 최대 파일 수?

int main(int argc, char** argv) {
    pid_t pid;
    int i;

    /* 새로운 프로세스 생성 */
    pid =fork();
    if(pid ==-1) {
        perror("fork");
        return -1;
    } else if(pid != 0) {
        exit(EXIT_SUCCESS);   // 부모 프로셋 종료
    }

    /* 새로운 세션과 프로세스 그룹을 생성한다. */
    if(setsid() == -1) return -1;

    /* 작업 디렉터리를 루트 디렉터리로 변경한다. */
    if(chdir("/") == -1) return -1;

    /* 모든 파일 디스크립터를 닫는다. 
            NR_OPEN 값은 실제 필요한 값보다 크지만 동작은 한다. */
    for(i=0; i < NR_OPEN ; i++) {
        close(i);
    }

    /* 파일 디스크립터 0,1,2 를 /dev/null로 리다이렉트 한다. */
    open("/dev/null", O_RDWR);  // 표준 입력
    dup(0);                     // 표준 출력
    dup(0);                     // 표준 에러

    /* 데몬에서 수행할 작업 */

    return 0;

}