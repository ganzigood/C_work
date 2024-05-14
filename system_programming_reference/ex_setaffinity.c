/* 
사용 가능한 CPU가 CPU #0, CPU #1 두개 라고 할때 CPU #0 에서만 실행되고 싶은 경우
sched_setaffitinity()를 이용한다. 
*/

/*
#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>

int main(int argc, char** argv) {
    cpu_set_t set;
    int ret, i;

    CPU_ZERO(&set);    // 모든 CPU 비트를 0으로 채운다.
    CPU_SET(0, &set);  // CPU #0은 허용한다.
    CPU_CLR(1, &set);  // CPU #1은 허용하지 않는다.

    ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
    if(ret == -1) perror("sched_setaffinity");

    for(i=0; i<10; i++) {   // CPU_SETSIZE 는 1024.. 너무 많음...
        int cpu;
        cpu = CPU_ISSET(i, &set);
        printf("cpu=%d is %s \n\n",i, cpu ? "set" : "unset");
    }
    return 0;
}
*/