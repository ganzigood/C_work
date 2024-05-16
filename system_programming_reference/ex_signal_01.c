#define _GNU_SOURCE    // strsignal 을 사용하기 위해서

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>      // strsignal 사용을 위한 헤더



/* SIGINT 용 핸들러 */
static void sigint_handler(int signo){
    /* 
    기술적으로, 시그널 핸들러에서 printf()를 사용해서는 안된다.
    하지만 사용한다고 세상이 끝나는 것도 아니다.
    그 이유에 대해서는 '재진입성'과 관련이 있다.
    */
   char* sigstr;
   sigstr = strsignal(signo);  // signo로 지정한 시그널의 설명을 가리키는 포인터 반환
   printf("\ncaught SIGINT\n");
   printf("caught %s\n",sigstr);
   exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    /* sigint_handler를 SIGINT용 시그널 핸들러로 등록 */
    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr,"cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    for(;;) pause();

    return 0;
}