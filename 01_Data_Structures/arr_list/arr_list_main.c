#include<stdio.h>

#include "arr_list.h"

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