/*
동적메모리할당과 해제를 사용한 기본적인 연결 리스트이다.
head, tail, cur 포인터를 통해서 데이터를 삽입하고 탐색하고 삭제한다.
*/


#include <stdlib.h>
#include <stdio.h>

typedef struct _node
{
    int data;
    struct _node* next;
}Node;


int main() {
    Node* head=NULL;
    Node* tail=NULL;
    Node* cur=NULL;
    
    int readData;
    int readCount=0;

    while(1) {
        printf("자연수 입력 : ");
        scanf("%d", &readData);

        if(readData < 0) break;

        readCount++;

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = readData;
        newNode->next = NULL;

        if(head == NULL){
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    printf("데이터 출력 : ");
    if(head == NULL) printf("데이터가 없다.");
    
    cur = head;
    while(cur != NULL) {
        printf(" %d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
    
    printf("데이터삭제 및 메모리해제\n");

    Node* DelNode = head;
    Node* DelNextNode = head->next;
    while(1) {
        
        printf("%d 삭제\n", DelNode->data);
        free(DelNode);
        DelNode = DelNextNode;
        if(DelNode == NULL) break;
        DelNextNode = DelNode->next;
    }

    printf("\n");
    
    return 0;

}