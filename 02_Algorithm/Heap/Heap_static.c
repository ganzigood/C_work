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

#define Max_Size 100

typedef int Element;

typedef struct __heap {
    Element data[Max_Size];
    int count;
}heap;

void Init_Heap(heap* myHeap) {
    myHeap->count = -1;
}

void InsertHeap(heap* myHeap, Element data) {
    
    myHeap->data[(myHeap->count)+1] = data;
    myHeap->count += 1;

    int pNode;
    int k = myHeap->count;
    while(1) {
        if(k <= 0) break;

        pNode = (k-1) / 2;
        int tmp;
        if(data < myHeap->data[pNode]) {
            int tmp = myHeap->data[k];
            myHeap->data[k] = myHeap->data[pNode];
            myHeap->data[pNode] = tmp;
        } else{
            break;
        }
        k = pNode;
    }
}

int DeleteHeap(heap* myHeap) {
    int returnData = myHeap->data[0];

    myHeap->data[0] = myHeap->data[myHeap->count];
    myHeap->count -= 1;

    int k = 0;
    int lChild, rChild;
    while(1) {
        lChild = 2*k+1;
        rChild = 2*k+2;

        if(myHeap->count < lChild) {
            break;
        }
        int factor = myHeap->data[k];
        int lfactor = myHeap->data[lChild];
        int rfactor = myHeap->data[rChild];
        int tmp;
        if(lfactor < rfactor) {
            if(factor < lfactor) {
                break;
            } else {
                tmp = myHeap->data[k];
                myHeap->data[k] = myHeap->data[lChild];
                myHeap->data[lChild] = tmp;
                k = lChild;
            }
        } else if (rfactor < lfactor) {
            if(factor< rfactor) {
                break;
            } else {
                tmp = myHeap->data[k];
                myHeap->data[k] = myHeap->data[rChild];
                myHeap->data[rChild] = tmp;
                k = rChild;
            }
        }
    }
    return returnData;
}

void PrintHeap(heap* myHeap) {
    int len = myHeap->count;

    if(len <0 ) {
        printf("데이터가 없다.\n");
        return;
    }
    for(int i = 0; i <= len; i++){
        printf("%d ", myHeap->data[i]);
    }
    printf("\n");
}

int main() {
    heap myHeap;
    
    Init_Heap(&myHeap);

    InsertHeap(&myHeap, 12);
    InsertHeap(&myHeap, 87);
    InsertHeap(&myHeap, 111);
    InsertHeap(&myHeap, 34);
    InsertHeap(&myHeap, 16);
    InsertHeap(&myHeap, 75);

    PrintHeap(&myHeap);

    int delData;

    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);
    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);
    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);
    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);
    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);
    delData = DeleteHeap(&myHeap);
    PrintHeap(&myHeap);

    return 0;
}
