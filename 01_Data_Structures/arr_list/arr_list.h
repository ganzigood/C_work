#define MAX_DATA 100

typedef int List;

typedef struct __arr_list {
    List list[MAX_DATA];
    int cur_position;
    int numOfData;
}arr_list;

void init_arr_list(arr_list* myList);
void insert_list(arr_list* myList, int data);
void print_data(arr_list* myList);
void first_data(arr_list* myList, int* data);
void Next_data(arr_list* myList, int* data);
int Max_index(arr_list* mylist);
void remove_data(arr_list* myList, int data);
