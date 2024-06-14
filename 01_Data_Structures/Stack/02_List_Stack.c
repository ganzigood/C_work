/*
연결 리스트 스택
*/

#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __stack_node {
    int data;
    struct __stack_node* down;
}StackNode;


typedef struct __list_stack {
    StackNode* Top;
    int NumOfData;
}ListStack;

void InitListStack(ListStack* myliststack) {
    myliststack->NumOfData = 0;
    myliststack->Top = NULL;
}

void Push(ListStack* myliststack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;

    newNode->down = myliststack->Top;
    myliststack->Top = newNode;
}

int Peek(ListStack* myliststack) {
    if(myliststack->Top == NULL) {
        printf("데이타가 없다.\n");
        return False;
    }
    return myliststack->Top->data;
}

int Pop(ListStack* myliststack) {
    if(myliststack->Top == NULL) {
        return False;
    }
    int data = myliststack->Top->data;
    StackNode* delNode = myliststack->Top;
    myliststack->Top = myliststack->Top->down;
    free(delNode);
    return data;
}

int main() {
    ListStack myliststack;
    InitListStack(&myliststack);

    Push(&myliststack, 2);
    Push(&myliststack, 5);
    Push(&myliststack, 19);
    Push(&myliststack, 7);
    Push(&myliststack, 11);
    Push(&myliststack, 67);
    Push(&myliststack, 45);

    printf("제일 위의 데이타 : %d\n",Peek(&myliststack));

    while(1) {
        int data = Pop(&myliststack);
        if(!data) break;
        printf("%d\n",data);
    }

    return 0;
}