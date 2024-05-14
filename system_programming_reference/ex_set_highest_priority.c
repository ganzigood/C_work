/*
set_highest_priority() - pid로 지정한 프로세스의 우선순위를
해당 스케줄링 정책에서 지원하는 가장 높은 우선순위로 결정한다.
sched_get_priority_min(), sched_get_priority_max(), sched_setparam(), 등 시스콜 예제

*/

/*

int set_highest_priority(pid_t pid) {
    struct sched_param sp;
    int policy, max, ret;

    policy = sched_getscheduler(pid);
    if(policy == -1) return -1;

    max = sched_get_priority_max(policy);
    if(max == -1) return -1;

    memset(&sp, 0, sizeof(struct sched_param));
    sp.sched_priority = max;
    ret = sched_setparam(pid, &sp);

    return ret;    
}


*/