#include<stdio.h>

#define MAX_DATA 100
#define List int

struct arr_list {
    List list[MAX_DATA];
    int cur_position;
    int numOfData;
};

struct arr_list* init_arr_list(struct arr_list* myList) {
    myList->cur_position = 0;
    myList->numOfData = 0;
}

void insert_list(struct arr_list* myList, int data) {
    (myList->list[myList->numOfData]) = data;
    (myList->numOfData) += 1;
}

void first_data(struct arr_list* myList, int* data){
    if(myList->numOfData == 0) {
        printf("do not have data\n");
        return;
    }
    
    myList->cur_position = 0;
    *data = myList->list[myList->cur_position];
}

void Next_data(struct arr_list* myList, int* data){

    (myList->cur_position) += 1;
    *data = myList->list[myList->cur_position];
}

int remove_data(struct arr_list* myList, int* data){
    if(myList->numOfData == 0) {
        printf("do not have data\n");
        return;
    }
    
    int temp;
    int min_index, max_index;
    
    min_index = myList->cur_position;
    max_index = myList->numOfData;

    temp = myList->list[myList->cur_position];

    for(int i = min_index; i <= max_index; i++) {
        myList->list[i] = myList->list[i+1];
    }
    myList->numOfData -= 1;

    *data = temp;
}

int Max_index(struct arr_list* mylist) {
    return mylist->numOfData;
}


int main(int argc, char** argv) {
    struct arr_list mylist;
    int data;

    init_arr_list(&mylist);

    insert_list(&mylist, 1);
    insert_list(&mylist, 2);
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

    return 0;
}