/*
SIGTERM과 SIGINT용으로 동일한 핸들러를 등록한다. 
또한, SIGPROF에 대한 동작은 기본값(해당 프로세스를 종료시킴)으로 재설정하고, 
SIGHUP은 무시하도록 설정한다.(원래는 프로세스를 종료시킴)
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

/* SIGINT, SIGTERM 용 시그널 핸들러 */
static void sigint_handler(int signo){
    
    if(signo == SIGINT) printf("\ncaught SIGINT\n");
    else if(signo == SIGTERM) printf("\ncaught SIGTERM\n");
    else {
        /* 아래 코드는 절대 실행되지 않는다. */
        fprintf(stderr, "Unexpected signal!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    /* sigint_handler를 SIGINT용 시그널 핸들러로 등록 */
    if(signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr,"cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    /* sigint_handler를 SIGTERM용 시그널 핸들러로 등록 */
    if(signal(SIGTERM, sigint_handler) == SIG_ERR) {
        fprintf(stderr,"cannot handle SIGTERM\n");
        exit(EXIT_FAILURE);
    }

    /* SIGPROF의 동작을 기본값으로 재설정 */
    if(signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf(stderr,"cannot reset SIGPROF!\n");
        exit(EXIT_FAILURE);
    }
    
    /* SIGHUP의 동작을 무시 */
    if(signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        fprintf(stderr,"cannot ignore SIGHUP!\n");
        exit(EXIT_FAILURE);
    }

    for(;;) pause();

    return 0;
}