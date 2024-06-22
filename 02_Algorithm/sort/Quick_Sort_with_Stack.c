/*

연결 리스트 스택을 사용해서 

퀵 정렬의 재귀호출대신 순환문으로 작성해보자.

엄청 복잡하게 한 것 같지만 그래도 해냈다.... ㅜㅜ;


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
    (myliststack->NumOfData)++;
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
    (myliststack->NumOfData)--;
    free(delNode);
    return data;
}

int isEmpty(ListStack* myliststack) {
    if(myliststack->Top == NULL) {
        return True;
    } else {
        return False;
    }
}

void Quick_Sort(int* dataSet, int left, int right) {
    
    ListStack LStack;
    ListStack RStack;

    InitListStack(&LStack);
    InitListStack(&RStack);

    Push(&LStack, left);
    Push(&RStack, right);

    int index;
    int temp;

    left = Pop(&LStack);
    right = Pop(&RStack);
    int max = right;
    int i = left+1;
    int j = right;
    int factor = dataSet[left];
    
    while(1){
        
        if(i >= j-1) {
            if(isEmpty(&LStack)) return;
            
            left = Pop(&LStack);
            right = Pop(&RStack);

            i = left+1;
            j = right;
            factor = dataSet[left];
        }

        while (i >= max || i > j) {
            if(isEmpty(&LStack)) return;
            
            left = Pop(&LStack);
            right = Pop(&RStack);

            i = left+1;
            j = right;
            factor = dataSet[left];
        }

        

        while(dataSet[i]<factor) {
            i++;
            if(i>=j) break;
        }
        
        while(dataSet[j]>factor){
            if(i>=j) break;
            j--;
            
        }
        if(i>=j) {
            index=i-1;
            temp = dataSet[i-1];
            dataSet[i-1] = dataSet[left];
            dataSet[left] = temp;
            
            if(left<right) {
                if(left!=index-1) {
                    Push(&LStack, left);
                    Push(&RStack, index-1);
                }
                if(right != index+1) {
                    Push(&LStack, index+1);
                    Push(&RStack, right);
                }
                continue;
            }
        }
        temp = dataSet[i];
        dataSet[i] = dataSet[j];
        dataSet[j] = temp;
        if(i == j-1){
            index=i;
            temp = dataSet[i];
            dataSet[i] = dataSet[left];
            dataSet[left] = temp;
            if(left<right) {
                if(left!=index-1) {
                    Push(&LStack, left);
                    Push(&RStack, index-1);
                }
                if(right != index+1) {
                    Push(&LStack, index+1);
                    Push(&RStack, right);
                }
                continue;
            }
        }
        i++;
        j--;
    }

}


int main() {
    int dataSet[] = {5,1,6,4,8,3,7,9,2};
    int length = sizeof(dataSet)/sizeof(int);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    int left = 0;
    int right = length-1;
    Quick_Sort(dataSet,left,right);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    return 0;
}