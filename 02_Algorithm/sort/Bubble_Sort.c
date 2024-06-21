/*
버블 정렬 - 나쁜 알고리즘... 

너무 많은 시간 소요.
*/

#include<stdio.h>

void Bubble_Sort(int* dataset, int length) {
    int i,j, temp;


    // 배열이 정렬이 된 상태인 경우 불필요한 비교를 수행하지 않도록 한다.
    for(i=0; i<length-1; i++) {
        if(dataset[i]>dataset[i+1]) {
            break;
        } else {
            printf("이미 정렬된 상태\n");
            return;
        }
    }

    for(i = 0; i<length-1; i++) {
        for(j=0; j<length-(i+1); j++){
            if(dataset[j]>dataset[j+1]) {
                temp = dataset[j];
                dataset[j] = dataset[j+1];
                dataset[j+1] = temp;
            }
    
        }
    }
   
}


int main() {

    int dataset[] = {6,3,2,4,1,5};
    
    for(int i =0; i<=sizeof(dataset)/sizeof(int)-1; i++){
        printf("%d ",dataset[i]);
    }
    printf("\n");
    int length = sizeof(dataset)/sizeof(int);
    Bubble_Sort(dataset,length);

    for(int i =0; i<=sizeof(dataset)/sizeof(int)-1; i++){
        printf("%d ",dataset[i]);
    }
    
    return 0;

}