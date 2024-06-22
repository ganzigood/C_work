/*
자기 구성 순차 탐색 

전위법(Transpose)

순차 탐색에서 전위법은 탐색된 항목을 바로 이전 항목과 교환하는 전략을 취하는 알고리즘

전진 이동법(Move to Front Method)는 검색된 항목을 무조건 앞으로 옮기는 것에 비해, 전위법은 자주 탐색된 항목을 조금씩 앞으로 옮긴다.
*/


/*
링크드 리스트 설명

head에 데이터를 추가한다.

리스트의 맨 앞에 Dummy Node를 추가하고, 두 번째 노드부터 유효한 데이터가 되도록 하겠다.
ex) head -> dummy -> data1 -> data2 -> data3

cur는 data1, before는 dummy를 기본으로 가르킨다.
*/

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

typedef struct __node
{
    int data;
    struct __node *next;
} Node;

typedef struct __linked_list
{
    Node *head;
    Node *before;
    Node *transposeCur;  // 전위법을 구현하기 위해서 추가. 탐색 대상의 위치를 바꾸기 전에   before - cur / 상태에서 transposeCur - before -cur 순으로 포인터를 배치한다.
    Node *cur;
    int NumOfData;
    //int (*comp)(int d1, int d2);
} linked_list;

void ListInit(linked_list *mylist){
    mylist->head = (Node*)malloc(sizeof(Node));
    
    mylist->head->next = NULL;
    mylist->NumOfData = 0;
}

void ListInsert(linked_list *mylist, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = mylist->head->next;
    mylist->head->next= newNode;

    (mylist->NumOfData)++;
}

int LFirst(linked_list *mylist, int* data){
    if(mylist->head->next == NULL) {
        printf("nothing data\n");
        return False;
    }
    mylist->before = mylist->head;
    mylist->cur = mylist->head->next;
    *data = mylist->cur->data;
    return True;
}

int LNext(linked_list *mylist, int* data) {
    mylist->before = mylist->cur;
    mylist->cur = mylist->before->next;
    if(mylist->cur == NULL) {
        return False;
    }
    *data = mylist->cur->data;
    return True;
}

int LRemove(linked_list *mylist) {
    Node* delNode;
    int i;
    printf("삭제한 데이터 : ");
    for(i=0; i<(mylist->NumOfData); i++) {
        mylist->before = mylist->head;
        mylist->cur = mylist->head->next;

        delNode=mylist->cur;
        
        printf("%d ", delNode->data);
        mylist->head->next=mylist->cur->next;
        free(delNode);

    }
    return True;
}

// 순차탐색 기능 추가 - 데이터가 있으면 해당 데이터를 가진 노드를 반환
Node* SequentialSearch(linked_list *mylist, int findData) {
    int data;
    if(LFirst(mylist, &data)) {
        if(findData==data) {
            return mylist->cur;
        } 
    } 
    while(LNext(mylist, &data)){
        if(findData==data) {
            return mylist->cur;
        }
    }

    return False;
}

// 전진이동탐색 - 순차탐색 이후 맨 앞으로 이동.
Node* MovetoFrontMethod(linked_list *mylist, int findData) {
    Node* findNode;

    if(findNode = SequentialSearch(mylist, findData)) {
        mylist->before->next = mylist->cur->next;
        mylist->cur = mylist->head->next;
        mylist->before = mylist->head;

        mylist->before->next = findNode;
        findNode->next=mylist->cur;
        mylist->cur = mylist->before->next;

        return findNode;
    } else {
        return False;
    }
}


// 전위법 탐색 기능 추가 - 순차 탐색 후 해당 데이터를 앞으로 한칸 이동.
Node* TransposeSearch(linked_list *mylist, int findData) {
    Node* findNode;

    if(findNode = SequentialSearch(mylist, findData)) {
        if(mylist->cur == mylist->head->next) {
            return findNode;
        } else {
            mylist->transposeCur = mylist->head;
            while(mylist->transposeCur->next != mylist->before) {
                mylist->transposeCur = mylist->transposeCur->next;
            }
            mylist->before->next = mylist->cur->next;
            mylist->cur->next= mylist->before;
            mylist->transposeCur->next = mylist->cur;
            return findNode;
        }
    }
    return False;
}

int LCount(linked_list *mylist) {
    return mylist->NumOfData;
}

int main() {
    int data=0;

    linked_list mylist;

    ListInit(&mylist);

    ListInsert(&mylist, 3);
    ListInsert(&mylist, 5);
    ListInsert(&mylist, 1);
    ListInsert(&mylist, 2);
    ListInsert(&mylist, 7);
    ListInsert(&mylist, 6);
   
    printf("입력된 데이터 출력 : ");

    if(LFirst(&mylist, &data)) printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf("%d ",data);
    }
    printf("\n\n");
    
    // 순차 탐색

    printf("== 순차 탐색 실행 ==\n");
    Node* findNode;
    if (findNode = SequentialSearch(&mylist, 12)) {
        printf("순차 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("순차 탐색 : 찾는 노드가 없다.\n");
    }

    if (findNode = SequentialSearch(&mylist, 2)) {
        printf("순차 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("순차 탐색 : 찾는 노드가 없다.\n");
    }

    printf("\n");

    // 전진 이동 탐색 실행
    printf("== 전진 이동 탐색 실행(Move to Front Method) ==\n");
    if (findNode = MovetoFrontMethod(&mylist, 123)) {
        printf("전진 이동 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("순차 탐색 : 찾는 노드가 없다.\n");
    }

    if (findNode = MovetoFrontMethod(&mylist, 7)) {
        printf("전진 이동 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("순차 탐색 : 찾는 노드가 없다.\n");
    }
    
    printf("\n");
    printf("전진 이동 탐색 이후 데이터 출력 : ");

    if(LFirst(&mylist, &data)) printf("%d ",data);
    while(LNext(&mylist, &data)) {
        printf("%d ",data);
    }
    
    printf("\n\n");

    // 전위법 실행
    printf("== 전위법 실행(Transpose) ==\n");
    if (findNode = TransposeSearch(&mylist, 123)) {
        printf("전위법 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("전위법 탐색 : 찾는 노드가 없다.\n");
    }

    if (findNode = TransposeSearch(&mylist, 5)) {
        printf("전위법 탐색 : 찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("전위법 탐색 : 찾는 노드가 없다.\n");
    }
    
    printf("\n");
    printf("전위법 탐색 이후 데이터 출력 : ");

    if(LFirst(&mylist, &data)) printf("%d ",data);
    while(LNext(&mylist, &data)) {
        printf("%d ",data);
    }

    printf("\n\n");
    printf("== 메모리 해제 ==\n");
    LRemove(&mylist);


    printf("\n");

    return 0;
}