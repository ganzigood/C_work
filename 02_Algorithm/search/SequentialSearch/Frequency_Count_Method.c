/*
순차탐색(선형탐색)

빈도 계수법(계수법, Frequency Count Method)

각 요소가 탐색된 횟수를 별도의 공간에 저장해두고, 탐색된 횟수가 높은 순으로 데이터를 재구성하는 전략의 알고리즘이다. 

전위법보다 민주적인 방법이다. 전위법은 처음부터 앞쪽에 있던 데이터는 계속 앞에 있을 가능성이 높고 
탐색 횟수는 많지만 데이터의 뒤쪽에 위치해 있다면 계속해서 뒤에만 있을 수 있기 때문이다.

단점으로는 계수 결과를 저장하는 별도의 공간과 계수 결과에 따라 데이터를 재배치해야 하는 등의 비용이 소모가 된다.

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
    int frequencyCount;
    struct __node *next;
} Node;

typedef struct __linked_list
{
    Node *head;
    Node *before;
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
    newNode->frequencyCount = 0;
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

// 빈도 계수법 기능 추가. 순차 탐색으로 탐색하고 빈도수를 증가시키고 빈도가 높은 순으로 데이타를 배치한다.
Node* FCSearch(linked_list* mylist, int findData) {
    Node* findNode;

    if(findNode = SequentialSearch(mylist, findData)) {
        (findNode->frequencyCount)++;
        mylist->before->next = mylist->cur->next;

        mylist->before = mylist->head;
        mylist->cur=mylist->head->next;

        while(mylist->cur->frequencyCount > findNode->frequencyCount) {
            mylist->cur=mylist->cur->next;
            mylist->before=mylist->before->next;
        }
        mylist->before->next = findNode;
        findNode->next = mylist->cur;

        return findNode;
    } else {
        return False;
    }
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
    ListInsert(&mylist, 9);
    ListInsert(&mylist, 4);
    ListInsert(&mylist, 10);
    ListInsert(&mylist, 8);

    printf("입력된 데이터 출력 : ");

    
    if(LFirst(&mylist, &data)) printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf("%d ",data);
    }
    printf("\n");

    // 빈도 계수법!
    printf("\n");
    printf("== 빈도 계수법으로 탐색 실행 ==\n");
    Node* findNode;
    if (findNode = FCSearch(&mylist, 12)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d\n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }

    if (findNode = FCSearch(&mylist, 2)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
    if (findNode = FCSearch(&mylist, 8)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
    if (findNode = FCSearch(&mylist, 2)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
    if (findNode = FCSearch(&mylist, 1)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
        if (findNode = FCSearch(&mylist, 7)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
        if (findNode = FCSearch(&mylist, 7)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }
        if (findNode = FCSearch(&mylist, 7)) {
        printf("찾는 노드가 있다. 노드의 데이터 : %d \n", findNode->data);
    } else {
        printf("찾는 노드가 없다.\n");
    }

    printf("\n");
    printf("계수법 이후 데이터 출력 : ");
    if(LFirst(&mylist, &data)) printf("%d ",data);
    while(LNext(&mylist, &data)) {
        printf("%d ",data);
    }
    printf("\n");   

    printf("메모리 해제\n");
    LRemove(&mylist);

    printf("\n");

    return 0;
}