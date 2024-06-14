#include <stdio.h>

#define True 1
#define False 0

#define Max 100

typedef struct __arraystack {
    int data[Max];
    int topIndex;
}ArrayStack;

void InitStack(ArrayStack* mystack) {
    mystack->topIndex = -1;
}

int IsEmpty(ArrayStack* mystack) {
    if(mystack->topIndex < 0) return False;
    else return True;
}

void Push(ArrayStack* mystack, int data) {
    mystack->data[(mystack->topIndex)+1] = data;
    (mystack->topIndex)++;
}

int Pop(ArrayStack* mystack) {
    if(mystack->topIndex < 0) {
        printf("데이타가 없다.\n");
        return False;
    }
    int top = mystack->topIndex;
    (mystack->topIndex)--;
    return mystack->data[top];
}

int Peek(ArrayStack* mystack) {
    if(mystack->topIndex < 0) {
        printf("데이타가 없다.\n");
        return False;
    }
    return mystack->data[mystack->topIndex];
}

int DataCount(ArrayStack* mystack) {
    return (mystack->topIndex)+1;
}

int main() {
    ArrayStack mystack;
    InitStack(&mystack);

    Push(&mystack, 2);
    Push(&mystack, 5);
    Push(&mystack, 19);
    Push(&mystack, 7);
    Push(&mystack, 11);
    Push(&mystack, 67);
    Push(&mystack, 45);

    printf("현재 데이터의 갯수 : %d\n", DataCount(&mystack));

    //가장 위에 데이터 확인만
    printf("%d\n", Peek(&mystack));

    for(int i = DataCount(&mystack) - 1; i >= 0; i--) {
        printf("mystack[%d] = %d\n", i, Pop(&mystack));
    }
    
}

