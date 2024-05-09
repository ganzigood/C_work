#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

/* 
자식 프로세스에 어떤 일이 발생했는지 파악하기 위한 wait(&status)을 사용한 예제
*/

int main(int argc, char** argv) {
    int status;
    pid_t pid;


    if(!fork()) return 1;  // 자식 프로세스 즉시 종료

    pid = wait(&status);
    if (pid == -1) {
        perror("wait");
        return 2;
    }

    printf("pid=%d\n", pid);

    if(WIFEXITED(status)) {
        printf("Normal termination with exit status=%d\n", WEXITSTATUS(status));
    }

    if(WIFSIGNALED(status)) {
        printf("killed by signal=%d %s\n",WTERMSIG(status),WCOREDUMP(status) ? " (dumped core)" : "");
    }

    if(WIFSTOPPED(status)) {
        printf("Stopped by signal=%d\n",WSTOPSIG(status));
    }

    if(WIFCONTINUED(status)) {
        printf("continued\n");
    }

    return 0;
}