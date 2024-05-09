/*
fork(), exec 함수군을 사용해서 - int system(const char *command) - 인터페이스애 상응하는 소스코드이다. 

my_system - 동기 식으로 명령을 실행하고 기다린다.

어떤 종류의 에러라도 발생할 경우 -1을 반환하며 그렇지 않을 경우
새로 실행된 프로세스의 종료 코드를 반환한다.
블록되거나 시그널을 무시하지 않는다.

*/

/*

int my_system(const char *cmd) {
    int status;
    pid_t pid;

    pid = fork();
    if (pid == -1) return -1;
    else if(pid == 0) {
        const char *argv[4];

        argv[0] = "bash";
        argv[1] = "-c";
        argv[2] = cmd;
        argv[3] = NULL;

        exec("/bin/bash", argv);

        exit(-1);
    }

    if(waitpid(pid,&status, 0) == -1) return -1;
    else if(WIFEXITED(status)) return WEXITSTATUS(status);

    return -1;
}

*/