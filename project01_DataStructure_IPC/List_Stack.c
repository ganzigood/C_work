/*
연결 리스트 스택
*/

#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __stack_node {
    char* data;
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

void Push(ListStack* myliststack, char* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;

    newNode->down = myliststack->Top;
    myliststack->Top = newNode;
}

char* Peek(ListStack* myliststack) {
    if(myliststack->Top == NULL) {
        printf("데이타가 없다.\n");
        return False;
    }
    return myliststack->Top->data;
}

char* Pop(ListStack* myliststack) {
    if(myliststack->Top == NULL) {
        return False;
    }
    char* data = myliststack->Top->data;
    StackNode* delNode = myliststack->Top;
    myliststack->Top = myliststack->Top->down;
    free(delNode);
    return data;
}

/*
int main() {

    ListStack mystack;
    InitListStack(&mystack);

    Push(&mystack,"asdf");

    char* buf;
    buf = Peek(&mystack);

    printf("%s",buf);


}
*/