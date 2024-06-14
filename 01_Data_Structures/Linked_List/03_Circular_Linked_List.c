/*
원형 연결 리스트

데이터를 앞으로도 넣을 수 있고 뒤로도 넣을 수 잇다.

*/

#include <stdio.h>
#include <stdlib.h>

#define True 1;
#define False 0;

typedef struct __node {
    int data;
    struct __node* next;
}Node;

typedef struct __clinkedlist {
    Node* head;
    Node* tail;
    Node* cur;
    int NumOfData;
}CLinkList;

void ListInit(CLinkList *mylist){
    mylist->NumOfData = 0;
    mylist->head =NULL;
}

void HeadInsert(CLinkList *mylist, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    if(mylist->NumOfData == 0) {
        mylist->head = newNode;
        mylist->tail = mylist->head;
    } else {
        newNode->next = mylist->head;
        mylist->head = newNode;
        mylist->tail->next=mylist->head;
    }
    (mylist->NumOfData)++;
}

void TailInsert(CLinkList *mylist, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
     if(mylist->NumOfData == 0) {
        mylist->head = newNode;
        mylist->tail = mylist->head;
    } else {
        newNode->next = mylist->head;
        mylist->tail->next = newNode;
        mylist->tail=newNode;
    }
    (mylist->NumOfData)++;
}

int LFirst(CLinkList *mylist, int* data){
    if(mylist->head == NULL) {
        printf("nothing data\n");
        return False;
    }
    mylist->cur = mylist->head;
    *data = mylist->cur->data;
    return True;
}

int LNext(CLinkList *mylist, int* data) {
    mylist->cur = mylist->cur->next;
    if(mylist->cur == mylist->head) {
        return False;
    }
    *data = mylist->cur->data;
    
    return True;
}

int LRemoveAll(CLinkList *mylist) {
    Node* delNode;
    int i;
    printf("삭제한 데이터 : ");
    for(i=0; i<(mylist->NumOfData); i++) {
        mylist->cur = mylist->head;

        delNode=mylist->cur;
    
        printf("%d ", delNode->data);
        mylist->head=mylist->cur->next;
        mylist->tail->next=mylist->head;
        free(delNode);
    }
    mylist->NumOfData=0;
    return True;
}

int LCount(CLinkList *mylist) {
    return mylist->NumOfData;
}

int main() {
    int data=0;

    CLinkList mylist;

    ListInit(&mylist);

    HeadInsert(&mylist, 3);
    HeadInsert(&mylist, 5);
    HeadInsert(&mylist, 1);
    HeadInsert(&mylist, 2);
    HeadInsert(&mylist, 7);
    HeadInsert(&mylist, 6);

    //head에 데이터를 추가하면 데이터가 앞에 추가됨
    HeadInsert(&mylist, 1111);

    //tail에 데이터를 추가하면 데이터가 뒤에 추가됨
    TailInsert(&mylist, 11);
    TailInsert(&mylist, 9999);
    
    printf("입력된 데이터 출력 : ");


    LFirst(&mylist, &data);
    printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf(" %d ",data);
    }

    printf("\n");

    LRemoveAll(&mylist);

    printf("\n");

    return 0;
}