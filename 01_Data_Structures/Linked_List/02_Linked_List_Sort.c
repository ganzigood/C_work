/*
head에 데이터를 추가한다.
리스트의 맨 앞에 Dummy Node를 추가하고, 두 번째 노드부터 유효한 데이터가 되도록 하겠다.
head -> dummy -> data1 -> data2 -> data3

cur는 data1, before는 dummy를 기본으로 가르킨다.
*/

#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __node {
    int data;
    struct __node* next;
}Node;

typedef struct __linked_list {
    Node* head;
    Node* before;
    Node* cur;
    int NumOfData;
    int (*comp)(int d1, int d2);
} linked_list;

void ListInit(linked_list* mylist) {

}

void ListInsert(linked_list* mylist, int data){

}



