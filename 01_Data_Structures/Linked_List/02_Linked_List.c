/*
head에 데이터를 추가한다.
리스트의 맨 앞에 Dummy Node를 추가하고, 두 번째 노드부터 유효한 데이터가 되도록 하겠다.
head -> dummy -> data1 -> data2 -> data3

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


    LFirst(&mylist, &data);
    printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf(" %d ",data);
    }

    printf("\n");

    LRemove(&mylist);

    printf("\n");

    return 0;
}