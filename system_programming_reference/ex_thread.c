#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void *start_thread(void *message){
    printf("%s\n", (const char*) message);
    return message;
}

int main(int argc, char** argv) {
    pthread_t t1, t2;
    const char *message1 = "T1";
    const char *message2 = "T2";
    //각각 다른 message를 받는 스레드 두 개를 만든다.
    pthread_create(&t1, NULL, start_thread, (void*)message1);
    pthread_create(&t2, NULL, start_thread, (void*)message2);

    /*
    스레드가 종료되기를 기다린다. 여기서 조인하지 않으면 다른 두 스레드가
    끝나기 전에 메인 스레드가 종료될 위험이 있다.
    */

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);

   return 0;
} 