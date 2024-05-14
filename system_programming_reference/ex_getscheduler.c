#include<stdio.h>
#include<sched.h>

int main(int argc, char** argv) {
    int policy;

    policy= sched_getscheduler(0);

    switch(policy) {
        case SCHED_OTHER:
            printf("normal\n");
            break;
        case SCHED_RR:
            printf("RR\n");
            break;
        case SCHED_FIFO:
            printf("FIFO\n");
            break;
        case -1:
            perror("sched_getscheduler");
            break;
        default:
            fprintf(stderr,"Unknown policy");
    }
    return 0;
}