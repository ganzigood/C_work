/*
일반적인 배열을 이용한 queue이다.

문제는 dequeue 될 때마다 배열을 한칸씩 당겨오는 연산이 필요해진다. 일단 고~

*/

#include<stdio.h>

#define True 1
#define False 0

#define Max_Len 100

typedef struct __array_queue {
    int data[Max_Len];
    int front;
    int rare;
}queue;

void InitQueue(queue* myqueue) {
    myqueue->rare =-1;
    myqueue->front = 0;
}

int EnQueue(queue* myqueue, int data) {
    
   // printf("rare=%d\n", myqueue->rare);

    if(myqueue->rare == Max_Len-1) {
        printf("꽉참\n");
        return False;
    }
    myqueue->data[(myqueue->rare)+1] = data;
    (myqueue->rare)++;
    return True;
}

int DeQueue(queue* myqueue, int* ReturnData) {
    if(myqueue->rare < 0 ) return False;
    *ReturnData = myqueue->data[myqueue->front];
    
    for(int i = 0; i< myqueue->rare; i++) {
        myqueue->data[i] =myqueue->data[i+1];
    }
    (myqueue->rare)--;
    return True;
}

int PeekQueue(queue* myqueue, int* ReturnData) {
    if(myqueue->rare < 0 ) return False;

    *ReturnData = myqueue->data[myqueue->front];
    return True;
}

int main() {
    queue myqueue;
    int data;
    InitQueue(&myqueue);

    EnQueue(&myqueue, 46);
    EnQueue(&myqueue, 21);
    EnQueue(&myqueue, 6);
    EnQueue(&myqueue, 195);
    EnQueue(&myqueue, 96);
    EnQueue(&myqueue, 0);
    EnQueue(&myqueue, 89);
    EnQueue(&myqueue, 1895);


    PeekQueue(&myqueue,&data);

    printf("peek = %d\n\n",data);

    while(DeQueue(&myqueue, &data)) {
        printf("dequeue = %d\n", data);
    }

    return 0;

}