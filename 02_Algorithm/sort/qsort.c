/* 
C 표준 라이브러리의 qsort()를 사용해서 퀵정렬을 해보자. 

*/


#include<stdio.h>
#include<stdlib.h>

int compare(void* num1, void* num2){
    int* n1 = (int*)num1;
    int* n2 = (int*)num2;
    
    if(*n1 > *n2) {
        return 1;
    } else if(*n1 < *n2) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    int dataSet[] = {5,1,6,4,8,3,7,9,2};
    int length = sizeof(dataSet)/sizeof(int);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    qsort(dataSet, length, sizeof(int), compare);
    
    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

}