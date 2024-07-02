/*
우선순위 큐와 힙(Heap)
일반적인 큐는 먼저 들어간 데이터가 먼저 나온다. 우선순위 큐는 새 요소에 우선순위를 부여해서 삽입하고 
우선순위가 높은 순서부터 빠져나온다.(정렬이 된다는 의미이다.)
=> 새 요소를 삽입하기 위해서 순차탐색을 해야된다. 이것을 극복하기 위한 힙 자료구조가 등장.

** 우선순위 큐..
힙을 큐의 형태로 변형한다.

    - 노드 구조체에 Priority 필드 추가.
    - 노드 구조체에 Data 필드 자료형을 void*로 변경
    - 삽입과 삭제 함수의 이름을 PQ_Enqueue(), PQ_Dequeue()로 변경

*/

#include <stdio.h>
#include <stdlib.h>

typedef int PriorityType;

typedef struct __heapNode {
    void* data;
    PriorityType priority;
}PQNode;

typedef struct __heap {
    PQNode* node;
    int maxSize;
    int usedSize;
}PQueue;

PQueue* Init_Heap() {
    PQueue* myPQ = (PQueue*)malloc(sizeof(PQueue));
    myPQ->maxSize = 50;
    myPQ->node = (PQNode*)malloc(sizeof(PQNode)*(myPQ->maxSize));
    myPQ->usedSize = -1;

    return myPQ;
}

void PQ_Destroy(PQueue* myPQ) {
    free(myPQ->node);
    free(myPQ);
}

void InsertHeap(PQueue* myPQ, PriorityType pri, void* data) {
    
    myPQ->node[myPQ->usedSize + 1].data = data;
    myPQ->node[myPQ->usedSize + 1].priority = pri;
    myPQ->usedSize += 1;

    if(myPQ->maxSize == myPQ->usedSize) {
        myPQ->maxSize *= 2;
        myPQ->node=(PQNode*)realloc(myPQ->node,sizeof(PQNode) * myPQ->maxSize);
    }

    int pNode;
    int k = myPQ->usedSize;
    while(1) {
        if(k <= 0) break;

        pNode = (k-1) / 2;
        PQNode tmp;
        if(pri < myPQ->node[pNode].priority) {
            tmp = myPQ->node[k];
            myPQ->node[k] = myPQ->node[pNode];
            myPQ->node[pNode] = tmp;
        } else{
            break;
        }
        k = pNode;
    }
}

PQNode DeleteHeap(PQueue* myPQ) {
    PQNode returnNode = myPQ->node[0];

    myPQ->node[0] = myPQ->node[myPQ->usedSize];
    myPQ->usedSize -= 1;

    int k = 0;
    int lChild, rChild;
    while(1) {
        lChild = 2*k+1;
        rChild = 2*k+2;

        if(myPQ->usedSize < lChild) {
            break;
        }
        int factor = myPQ->node[k].priority;
        int lfactor = myPQ->node[lChild].priority;
        int rfactor = myPQ->node[rChild].priority;
        PQNode tmp;
        if(lfactor < rfactor) {
            if(factor < lfactor) {
                break;
            } else {
                tmp = myPQ->node[k];
                myPQ->node[k] = myPQ->node[lChild];
                myPQ->node[lChild] = tmp;
                k = lChild;
            }
        } else if (rfactor < lfactor) {
            if(factor< rfactor) {
                break;
            } else {
                tmp = myPQ->node[k];
                myPQ->node[k] = myPQ->node[rChild];
                myPQ->node[rChild] = tmp;
                k = rChild;
            }
        }
    }
    printf("완료된 작업 : %s(%d)\n", (char*)returnNode.data, returnNode.priority);
    return returnNode;
}

void PrintPQ(PQueue* myPQ) {
    int len = myPQ->usedSize;

    if(len <0 ) {
        printf("데이터가 없다.\n");
        return;
    }
    for(int i = 0; i <= len; i++){
        printf("작업명 : %s / 우선순위(%d) \n", (char*)myPQ->node[i].data, myPQ->node[i].priority);
    }
    printf("\n");
}

int main() {
    PQueue* myPQ = Init_Heap();

    InsertHeap(myPQ, 34 , (void*)"코딩");
    InsertHeap(myPQ, 12, (void*)"고객미팅");
    InsertHeap(myPQ, 87, (void*)"커피내리기");
    InsertHeap(myPQ, 45, (void*)"문서작성");
    InsertHeap(myPQ, 35, (void*)"디버깅");
    InsertHeap(myPQ, 66, (void*)"목욕");

    printf("큐에 남아 있는 작업의 수 : %d\n",myPQ->usedSize+1);
    
    PrintPQ(myPQ);

    PQNode delData;

    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);
    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);
    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);
    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);
    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);
    delData = DeleteHeap(myPQ);
    PrintPQ(myPQ);

    PQ_Destroy(myPQ);

    return 0;
}
