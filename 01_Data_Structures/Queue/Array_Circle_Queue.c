/*
배열을 이용한 원형 queue이다.

일반 queue는 dequeue 될 때마다 배열을 한칸씩 당겨오는 연산이 필요해지는 단점을 보완한다.

배열이 꽉찬 상태 r바로 앞에 f가 있다.
배열이 텅빈 상태 r과 f의 위치가 같다.

r과 f가 배열의 끝에 도달했을 때는 인덱스를 다시 0으로 조정해준다

0에서 시작해서 한칸 이동한뒤 enqueue를 한다. 첫 인덱스를 비워둔다. 큐가 꽉찬상태와 텅빈 상태를 구분한다.

*/

#include<stdio.h>

#define True 1
#define False 0

#define Max_Len 100  // 이 길이를 수정해서 원형 큐에 대한 검증을 할 수 있겟다.

typedef struct __array_queue {
    int data[Max_Len];
    int front;
    int rare;
}queue;

void InitQueue(queue* myqueue) {
    myqueue->rare =0;
    myqueue->front = 0;
}

int EnQueue(queue* myqueue, int data) {
    if((myqueue->front == 0 && myqueue->rare == Max_Len-1) || 
                                (myqueue->front == (myqueue->rare)+1)) {
        printf("큐가 꽉참, 넣을 공간 없음\n\n");
        return False;
    } else if(myqueue->rare == Max_Len-1 && myqueue->front != 0) {
        myqueue->rare = 0;
        myqueue->data[myqueue->rare] =data;
    } else {
        (myqueue->rare)++;
        myqueue->data[myqueue->rare] =data;
    }
    return True;
}

int DeQueue(queue* myqueue, int* ReturnData) {
    if(myqueue->front == myqueue->rare ) {
        printf("큐가 텅빔 꺼낼 데이터 없음\n\n");
        return False;
    }
    if(myqueue->front == Max_Len-1){
        myqueue->front = 0;
        *ReturnData = myqueue->data[myqueue->front];
        return True;
    }
    (myqueue->front)++;
    *ReturnData = myqueue->data[myqueue->front];
    return True;
}

int PeekQueue(queue* myqueue, int* ReturnData) {
    if(myqueue->rare == myqueue->front ) {
        printf("데이터 없다. peek 데이터 없음.\n\n");
        return False;
    }
    if(myqueue->front == Max_Len-1){
        *ReturnData = myqueue->data[0];
        return True;
    }
    *ReturnData = myqueue->data[myqueue->front+1];
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
    
 
    if(PeekQueue(&myqueue, &data)) {
        printf("peek = %d\n\n", data);
    }

    while(DeQueue(&myqueue, &data)) {
        printf("dequeue = %d\n", data);
    }


    // 다시 enqueue
    if(PeekQueue(&myqueue, &data)) {
        printf("peek = %d\n", data);
    }


    EnQueue(&myqueue, 11);
    EnQueue(&myqueue, 22);
    EnQueue(&myqueue, 33);
    EnQueue(&myqueue, 44);

    if(PeekQueue(&myqueue, &data)) {
        printf("peek = %d\n", data);
    }

    while(DeQueue(&myqueue, &data)) {
        printf("dequeue = %d\n", data);
    }

    return 0;

}