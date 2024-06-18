#include<stdio.h>

#define MAX_DATA 100

typedef int List;

typedef struct __arr_list {
    List list[MAX_DATA];
    int cur_position;
    int numOfData;
}arr_list;

void init_arr_list(arr_list* myList) {
    myList->cur_position = 0;
    myList->numOfData = 0;
}

void insert_list(arr_list* myList, int data) {
    if(myList->numOfData == MAX_DATA) {
        printf("데이터 최대치를 넘어선다.\n");
        return;
    }
    
    (myList->list[myList->numOfData]) = data;
    (myList->numOfData) += 1;
}

void print_data(arr_list* myList){
    if(myList->numOfData == 0) {
        printf("do not have data\n");
        return;
    }
    myList->cur_position = 0;

    int max_index = myList->numOfData;
    int i;
    for (i=0; i< max_index; i++) {
        int data = myList->list[i];
        printf("%d ",data);       
    }
    printf("\n");
}

void first_data(arr_list* myList, int* data){
    if(myList->numOfData == 0) {
        printf("do not have data\n");
        return;
    }
    
    myList->cur_position = 0;
    *data = myList->list[myList->cur_position];
}
void Next_data(arr_list* myList, int* data){

    (myList->cur_position) += 1;
    *data = myList->list[myList->cur_position];
}


int Max_index(arr_list* mylist) {
    int num = mylist->numOfData;
    return num;
}

void remove_data(arr_list* myList, int data){
    if(myList->numOfData == 0) {
        printf("do not have data\n");
        return;
    }
    int i,j;

    int max_index = Max_index(myList);
    printf("데이터 %d를 삭제합니다.\n", data);

    for(i=0; i<max_index; i++) {
        if(myList->list[i] == data) {
            for(j = i ; j <= max_index; j++) {
                myList->list[j] = myList->list[j+1];
            }
            myList->numOfData -= 1;
            max_index -= 1;
        }
    }
}

int main(int argc, char** argv) {
    arr_list mylist;
    int data;

    init_arr_list(&mylist);

    insert_list(&mylist, 1);
    insert_list(&mylist, 2);
    insert_list(&mylist, 3);
    insert_list(&mylist, 4);
    insert_list(&mylist, 5);
    insert_list(&mylist, 3);

    int num = Max_index(&mylist);

    printf("현재 데이터의 수 = %d\n", num);

    for(int i=0; i<num; i++) {
        if(i == 0) {
            first_data(&mylist, &data);
            printf("%d ", data);
        } else {
            Next_data(&mylist, &data);
            printf("%d ", data);
        }
    }
    
    printf("\n");

    remove_data(&mylist, 3);

    num = Max_index(&mylist);

    printf("현재 데이터의 수 = %d\n", num);

    for(int i=0; i<num; i++) {
        if(i == 0) {
            first_data(&mylist, &data);
            printf("%d ", data);
        } else {
            Next_data(&mylist, &data);
            printf("%d ", data);
        }
    }

    printf("\n");

    printf("전체출력 메소드를 통한 데이터 출력\n");
    print_data(&mylist);

    return 0;
}