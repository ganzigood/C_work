/*
삽입 정렬 - 버블 정렬과 구현은 비슷하지만 성능이 조금 더 좋다
비교적 크기가 작은 자료구조에서는 버블정렬 보다는 삽입정렬을 사용한다.

*/


#include<stdio.h>
#include<string.h>

void Insertion_Sort(int* dataSet, int length) {
    int i,j,temp;

    for(i=1; i<length; i++) {
        if(dataSet[i-1]<=dataSet[i]) continue;

        temp = dataSet[i];

        for(j=0; j<i; j++) {
            if(dataSet[j]>dataSet[i]){
                memmove(&dataSet[j+1],&dataSet[j],sizeof(int)*(i-j));
                dataSet[j] = temp;
            }
        }
    
    }

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");
}

int main() {
    int dataSet[] = {1,5,6,4,2,3};
    int length = sizeof(dataSet)/sizeof(int);
    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    Insertion_Sort(dataSet, length);

    return 0;
}