/*
C 라이브러리의 이진 탐색을 구현한 bsearch()를 사용.

*/

/*
이진 탐색

정렬된 데이터에서 사용할 수 있는 '고속' 탐색 알고리즘이다. 
sort 기능이 추가된 링크드 리스트에 이진 탐색 기능을 추가한다.

퀵 정렬 알고리즘에 이진탐색 기능을 추가해보겠다.

*/


#include<stdio.h>
#include<stdlib.h>

#define True 1;
#define False 0;

int Find_Partition(int* dataSet, int left, int right) {
    
    //기준 요소를 분할 영역의 가장 왼쪽 값으로 해보겠다.
    
    int factor = dataSet[left];
    int index;
    int temp;
    int i = left+1;
    int j = right;

    while(i<=j) {
        while(dataSet[i]<=factor && i<j) {
            ++i;
        }

        while(dataSet[j]>=factor && i<=j){
            --j;
        }

        if(i<j) {   
            temp = dataSet[i];
            dataSet[i] = dataSet[j];
            dataSet[j] = temp;
        } else {
            break;
        }
    }
    temp = dataSet[j];
    dataSet[j] = dataSet[left];
    dataSet[left] = temp;
    return j;
}

void QuickSort(int* dataSet, int left, int right) {
    if(left<right) {
        int index = Find_Partition(dataSet, left, right);
        QuickSort(dataSet,left,index-1);
        QuickSort(dataSet,index+1,right);
    }
}

int compare(void* n1, void* n2) {
    int* num1 = (int*)n1;
    int* num2 = (int*)n2;
    
    if(*num1 > *num2) {
        return 1;
    } else if (*num1 < *num2 ){
        return -1;
    } else {
        return 0;
    }
}


int main() {
    int dataSet[] = {871,1,672,7,139,11,67,12,23,14,759,3};
    int length = sizeof(dataSet)/sizeof(int);

    printf("정렬 전 dataSet : ");
    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    int left = 0; 
    int right = length-1;
    QuickSort(dataSet,left,right);

    printf("\n");
    printf("정렬 후 dataSet : ");
    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    printf("== 이진탐색 bsearch() 실행 ==\n");
    int data = 759;
    int* findData;
    findData = bsearch(&data ,dataSet,12,sizeof(int),compare);    
    printf("찾는 데이터는 : ... %d\n", *findData);

    return 0;
}