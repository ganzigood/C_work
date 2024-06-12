#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100
#define NAME_LEN 30
#define PHONE_LEN 30

#define TRUE 1
#define FALSE 0

typedef struct __namecard
{
    char name[NAME_LEN];
    char phone[PHONE_LEN];
} namecard;

typedef struct __arr_list {
    namecard* list[MAX_DATA];
    int cur_position;
    int numOfData;
}arr_list;

void init_arr_list(arr_list* myList){
    myList->cur_position = 0;
    myList->numOfData = 0;
}

void insert_list(arr_list* myList, namecard* ncData){
    myList->list[myList->numOfData] = ncData;
    (myList->numOfData)++;
}

int Max_index(arr_list* mylist){
    return mylist->numOfData;
}

void print_data(arr_list* myList){
    int max_index = Max_index(myList)-1;
    int i;
    for (i=0; i<=max_index; i++) {
        printf("이름 : %s  전화번호 : %s\n",myList->list[i]->name,
                                            myList->list[i]->phone);
    }
}

int First_data(arr_list* myList, namecard** newcard) {
    if(myList->numOfData == 0) {
        return FALSE;
    }
    (myList->cur_position) = 0;
    
    //printf("%p\n",*newcard);
    //printf("%p\n",&newcard);

    *newcard = myList->list[0];

    (myList->cur_position)++;
    return TRUE;
}

int Next_data(arr_list* myList, namecard** newcard) {
    if(myList->cur_position >= myList->numOfData){
        return FALSE;
    }
    
    *newcard = myList->list[myList->cur_position];
    (myList->cur_position)++;

    return TRUE;
}

void remove_data(arr_list* myList, char* name){
    int max_index = myList->numOfData - 1;
    int i,j;
    namecard* deldata;
    for (i=0; i<= max_index; i++){
        if(!strcmp(myList->list[i]->name, name)) {
            for(j=i; j < max_index; j++) {
                deldata = myList->list[j];
                myList->list[j] = myList->list[j+1];
                free(deldata);
            }
            max_index--;
            (myList->numOfData)--;
        }
    }
}

namecard* MakeNameCard(char* name, char* phone){
    namecard* newNC = (namecard*)malloc(sizeof(namecard));
    strcpy(newNC->name, name);
    strcpy(newNC->phone, phone);

    return newNC;
}
void ShowNameCard(namecard* pcard){
    printf("이름 : %s\n", pcard->name);
    printf("전화번호 : %s\n", pcard->phone);
}
int NameCompare(namecard* pcard, char* name){
    if(strcmp(pcard->name, name)) {
        return TRUE;
    }
    return FALSE;
}
void ChanePhoneNum(namecard* pcard, char* phone){
    strcpy(pcard->phone, phone);
}

int main(void) {
    namecard* newcard;
    //printf("%p\n",newcard);
    //printf("%p\n",&newcard);   // **newcard가 가리키는 값은 포인터 변수를 저장하기 위한 저장공간이다.

    arr_list mylist;

    init_arr_list(&mylist);

    newcard = MakeNameCard("이진헌","111-1111-1111");
    insert_list(&mylist, newcard);
    newcard = MakeNameCard("이유채","222-2222-2222");
    insert_list(&mylist, newcard);
    newcard = MakeNameCard("이소담","333-3333-3333");
    insert_list(&mylist, newcard);
    newcard = MakeNameCard("이해든","444-4444-4444");
    insert_list(&mylist, newcard);

    print_data(&mylist);
  
    First_data(&mylist, &newcard);
    printf("\n");

    if(!NameCompare(newcard, "이소담")) {
        ShowNameCard(newcard);
    } else {
        while(Next_data(&mylist, &newcard)) {
            if(!NameCompare(newcard,"이소담")) {
                ShowNameCard(newcard);
                break;
            }
        }
    }

    printf("\n");
    
    remove_data(&mylist, "이소담");

    print_data(&mylist);
    int i;
    for(i=0; i<Max_index(&mylist); i++) {
        free(mylist.list[i]);
    }

    return 0;    
}