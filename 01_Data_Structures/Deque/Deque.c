/*
덱(deque)는 앞으로도 뒤로도 넣을 수 있고, 앞으로도 뒤로도 뺄 수 있는 구조다.

double link 형식으로 구현한다.
*/

#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __node {
    int data;
    struct __node* next;
    struct __node* prev;
} Node;

typedef struct linked_deque {
    Node* head;
    Node* tail;
} Deque;

void InitDeque(Deque* myDeque) {
    myDeque->head = NULL;
    myDeque->tail = NULL;
}

int IsEmpty(Deque* myDeque) {
    if(myDeque->head == NULL) {
        return True;
    } else {
        return False;
    }
}

void HeadInsert(Deque* myDeque, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;

    if(IsEmpty(myDeque)) {
        newNode->next = NULL;
        myDeque->tail = newNode;
    } else {
        newNode->next = myDeque->head;
        myDeque->head->prev = newNode;
    }
    myDeque->head = newNode;

}

void TailInsert(Deque* myDeque, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(IsEmpty(myDeque)) {
        newNode->prev = NULL;
        myDeque->head = newNode;
    } else {
        newNode->prev = myDeque->tail;
        myDeque->tail->next = newNode;
    }
    myDeque-> tail = newNode;
}

int GetHead(Deque* myDeque, int* data) {
    if(IsEmpty(myDeque)) {
        return False;
    } else {
        *data = myDeque->head->data;
        return True;
    }
}

int GetTail(Deque* myDeque, int* data) {
    if(IsEmpty(myDeque)) {
        return False;
    } else {
        *data = myDeque->tail->data;
        return True;
    }
}

int RemoveHead(Deque* myDeque, int* data) {
    Node* delNode;
    if(IsEmpty(myDeque)) {
        return False;
    } else {
        *data = myDeque->head->data;
        delNode = myDeque->head;
        myDeque->head = myDeque->head->next;
        free(delNode);
        return True;
    }
}

int RemoveTail(Deque* myDeque, int* data) {
    Node* delNode;
    if(IsEmpty(myDeque)) {
        return False;
    } else {
        *data = myDeque->tail->data;
        delNode = myDeque->tail;
        myDeque->head = myDeque->tail->prev;
        free(delNode);
        return True;
    }
}

void RemoveAll(Deque* myDeque){
    while(myDeque->head == NULL) {
        Node* delNode;
        delNode = myDeque->head;
        myDeque->head= myDeque->head->next;
        free(delNode);          
    }
}

int main() {
    Deque myDeque;
    int data;

    InitDeque(&myDeque);

    HeadInsert(&myDeque, 5);
    HeadInsert(&myDeque, 4);
    HeadInsert(&myDeque, 3);
    HeadInsert(&myDeque, 2);
    HeadInsert(&myDeque, 1);

    GetHead(&myDeque, &data);
    printf("gethead = %d\n", data);
    GetTail(&myDeque, &data);
    printf("gettail = %d\n", data);

    TailInsert(&myDeque, 6);
    TailInsert(&myDeque, 7);
    TailInsert(&myDeque, 8);
    TailInsert(&myDeque, 9);
    TailInsert(&myDeque, 10);

    GetHead(&myDeque, &data);
    printf("gethead = %d\n", data);
    GetTail(&myDeque, &data);
    printf("gettail = %d\n", data);

    printf("remove from head = ");
    while(RemoveHead(&myDeque, &data)) {
        printf(" %d ", data);
    }

    return 0;
}
