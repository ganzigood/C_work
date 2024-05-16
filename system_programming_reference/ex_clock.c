/* 리눅스가 지원하는 다섯 가지 시계의 해상도 출력하기 */

#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<sys/types.h>

int main(int argc, char** argv) {

    clockid_t clocks[] = {
    CLOCK_REALTIME,
    CLOCK_MONOTONIC,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID,
    CLOCK_MONOTONIC_RAW,
    (clockid_t)-1
    };

    int i;

    for (i=0; clocks[i] !=(clockid_t)-1; i++) {
        struct timespec res;
        int ret;

        ret = clock_getres(clocks[i], &res);
        if (ret) perror("clock_getrs");
        else printf("clock=%d, sec=%ld, nsec=%ld\n",
                    clocks[i], res.tv_sec,res.tv_nsec);
    
        /* 위 다섯 가지 표준 시계에서 현재 시각을 얻기*/

        ret = clock_gettime(clocks[i], &res);
        if(ret) perror("clock_gettime");
        else printf("clock=%d, sec=%ld nsec=%ld\n\n",
                    clocks[i], res.tv_sec, res.tv_nsec);
    }

    
    return 0;
}
