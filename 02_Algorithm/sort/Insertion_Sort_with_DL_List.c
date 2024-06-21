/*
dummy를 사용한 양방향 연결 리스트

앞 뒤로 데이터 조회가 가능하다. 

insertion_sort를 추가했다.

*/

#include <stdio.h>
#include <stdlib.h>

#define True 1;
#define False 0;

typedef struct __node {
    int data;
    struct __node* next;
    struct __node* before;
} Node;

typedef struct __double_link_list {
    Node* head;
    Node* cur;
    Node* sorting;
    int NumOfData;
}dlinklist;

void ListInit(dlinklist *mylist){
    mylist->head =(Node*)malloc(sizeof(Node));
    mylist->head->before = NULL;
    mylist->sorting = NULL;
    mylist->NumOfData = 0;
}    

void ListInsert(dlinklist *mylist, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if(mylist->NumOfData == 0) {
        mylist->head->next = newNode;
        newNode->before = mylist->head;
        newNode->next= NULL;
    } else {
        newNode->before = mylist->head;
        newNode->next = mylist->head->next;
        mylist->head->next->before = newNode;
        mylist->head->next=newNode;
    }
    (mylist->NumOfData)++;
}


int LFirst(dlinklist *mylist, int* data){
    if(mylist->head->next == NULL) {
        printf("nothing data\n");
        return False;
    }
    mylist->cur = mylist->head->next;
    *data = mylist->cur->data;
    return True;
}

int LNext(dlinklist *mylist, int* data) {
    mylist->cur = mylist->cur->next;
    if(mylist->cur == NULL) {
        return False;
    }
    *data = mylist->cur->data;
    
    return True;
}

int RemoveAll(dlinklist *mylist) {
    Node* delNode;
    int i;
    printf("삭제한 데이터 : ");
    for(i=0; i<(mylist->NumOfData); i++) {
        mylist->cur = mylist->head->next;
        delNode=mylist->cur;
        
        printf("%d ", delNode->data);
        
        if(mylist->cur->next == NULL) break;
        mylist->head->next=mylist->cur->next;
        mylist->cur->next->before = mylist->head;
        free(delNode);
    }
    mylist->NumOfData=0;
    return True;
}

int LCount(dlinklist *mylist) {
    return mylist->NumOfData;
}


// 삽입정렬 기능 추가.
void Insertion_Sort(dlinklist* mylist, int count) {

    Node* tmpNode;
    mylist->sorting = mylist->head->next;
    mylist->cur = mylist->sorting->next;
    
    for(int i = 1 ; i< count; i++) {
        mylist->sorting = mylist->head->next;
        for(int j = 0 ; j < i ; j++) {
            if(mylist->sorting->data > mylist->cur->data) {
                tmpNode = mylist->cur->before;

                mylist->cur->before->next = mylist->cur->next;
                if(mylist->cur->next != NULL) mylist->cur->next->before = mylist->cur->before;

                mylist->cur->before= mylist->sorting->before;
                mylist->sorting->before->next=mylist->cur;
                mylist->cur->next=mylist->sorting;
                mylist->sorting->before=mylist->cur;

                mylist->cur = tmpNode;
            }
            mylist->sorting=mylist->sorting->next;
        }
        mylist->cur=mylist->cur->next;
        
    }
}

int main() {
    int data=0;

    dlinklist mylist;

    ListInit(&mylist);

    ListInsert(&mylist, 3);
    ListInsert(&mylist, 5);
    ListInsert(&mylist, 1);
    ListInsert(&mylist, 2);
    ListInsert(&mylist, 7);
    ListInsert(&mylist, 6);
   
    printf("입력된 데이터 갯수 : %d\n",LCount(&mylist));
    printf("입력된 데이터 출력 : ");


    if(LFirst(&mylist, &data)) printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf(" %d ",data);
    }

    // Insertion_Sort() 정렬.
    Insertion_Sort(&mylist, LCount(&mylist));
    
    printf("\n 정렬된 데이터 출력 : ");

    if(LFirst(&mylist, &data)) printf(" %d ",data);
    while(LNext(&mylist, &data)) {
        printf(" %d ",data);
    }

    printf("\n\n");

    RemoveAll(&mylist);

    printf("\n");

    return 0;
}