/* sched_getaffitinity() 프로세스의 CPU친화도를 조회한다. */

#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>

int main(int argc, char** argv) {
    cpu_set_t set;
    int ret, i;

    CPU_ZERO(&set);
    ret = sched_getaffinity(0, sizeof(cpu_set_t), &set);
    if(ret == -1) perror("sched_getaffitinity");

    for(i=0; i<10; i++) {   // CPU_SETSIZE 는 1024.. 너무 많음...
        int cpu;
        cpu = CPU_ISSET(i, &set);
        printf("cpu=%d is %s \n\n",i, cpu ? "set" : "unset");
    }
    return 0;
}