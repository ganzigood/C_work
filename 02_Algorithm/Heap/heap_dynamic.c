/*
우선순위 큐와 힙(Heap)
일반적인 큐는 먼저 들어간 데이터가 먼저 나온다. 우선순위 큐는 새 요소에 우선순위를 부여해서 삽입하고 
우선순위가 높은 순서부터 빠져나온다.(정렬이 된다는 의미이다.)
=> 새 요소를 삽입하기 위해서 순차탐색을 해야된다. 이것을 극복하기 위한 힙 자료구조가 등장.

** 힙
힙 순서 속성을 만족하는 완전 이진 트리
    - 힙 순서 속성 : 트리내의 모든 노드가 부모 노드보다 커야 한다.
    - 한 가지 조건만을 만족한다. 힙에서 가장 작은 데이터를 갖는 노드는 뿌리 노드이다.
    - 위 조건을 만족하기 위한 삽입 연산과 삭제 연산이 존재한다.
    - 연산을 위해서 가장 마지막 노드, 최고 깊이 가장 우측 노드를 찾기 위해서 링크드 리스트로는 어렵다. 
    따라서 배열을 사용한다.
        k번 인덱스에 위치한 노드의 약쪽 자식 노드들의 인덱스
            왼쪽 : 2k + 1
            오른쪽 : 2k + 2
        k번 인덱스의 보모 노드의 인덱스 (k-1)/2의 몫
*/

#include <stdio.h>
#include <stdlib.h>



typedef int Element;

typedef struct __heapNode {
    Element data;
}heapNode;

typedef struct __heap {
    heapNode* node;
    int maxSize;
    int usedSize;
}heap;

heap* Init_Heap() {
    heap* myHeap = (heap*)malloc(sizeof(heap));
    myHeap->maxSize = 50;
    myHeap->node = (heapNode*)malloc(sizeof(heapNode)*(myHeap->maxSize));
    myHeap->usedSize = -1;

    return myHeap;
}

void Heap_Destroy(heap* myHeap) {
    free(myHeap->node);
    free(myHeap);
}

void InsertHeap(heap* myHeap, Element data) {
    
    myHeap->node[myHeap->usedSize + 1].data = data;
    myHeap->usedSize += 1;

    if(myHeap->maxSize == myHeap->usedSize) {
        myHeap->maxSize *= 2;
        myHeap->node=(heapNode*)realloc(myHeap->node,sizeof(heapNode) * myHeap->maxSize);
    }

    int pNode;
    int k = myHeap->usedSize;
    while(1) {
        if(k <= 0) break;

        pNode = (k-1) / 2;
        int tmp;
        if(data < myHeap->node[pNode].data) {
            int tmp = myHeap->node[k].data;
            myHeap->node[k].data = myHeap->node[pNode].data;
            myHeap->node[pNode].data = tmp;
        } else{
            break;
        }
        k = pNode;
    }
}

int DeleteHeap(heap* myHeap) {
    int returnData = myHeap->node[0].data;

    myHeap->node[0].data = myHeap->node[myHeap->usedSize].data;
    myHeap->usedSize -= 1;

    int k = 0;
    int lChild, rChild;
    while(1) {
        lChild = 2*k+1;
        rChild = 2*k+2;

        if(myHeap->usedSize < lChild) {
            break;
        }
        int factor = myHeap->node[k].data;
        int lfactor = myHeap->node[lChild].data;
        int rfactor = myHeap->node[rChild].data;
        int tmp;
        if(lfactor < rfactor) {
            if(factor < lfactor) {
                break;
            } else {
                tmp = myHeap->node[k].data;
                myHeap->node[k].data = myHeap->node[lChild].data;
                myHeap->node[lChild].data = tmp;
                k = lChild;
            }
        } else if (rfactor < lfactor) {
            if(factor< rfactor) {
                break;
            } else {
                tmp = myHeap->node[k].data;
                myHeap->node[k].data = myHeap->node[rChild].data;
                myHeap->node[rChild].data = tmp;
                k = rChild;
            }
        }
    }
    return returnData;
}

void PrintHeap(heap* myHeap) {
    int len = myHeap->usedSize;

    if(len <0 ) {
        printf("데이터가 없다.\n");
        return;
    }
    for(int i = 0; i <= len; i++){
        printf("%d ", myHeap->node[i].data);
    }
    printf("\n");
}

int main() {
    heap* myHeap = Init_Heap();

    InsertHeap(myHeap, 12);
    InsertHeap(myHeap, 87);
    InsertHeap(myHeap, 111);
    InsertHeap(myHeap, 34);
    InsertHeap(myHeap, 16);
    InsertHeap(myHeap, 75);

    PrintHeap(myHeap);

    int delData;

    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);
    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);
    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);
    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);
    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);
    delData = DeleteHeap(myHeap);
    PrintHeap(myHeap);

    return 0;
}
