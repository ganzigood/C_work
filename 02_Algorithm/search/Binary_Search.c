/*
이진 탐색

*** 배열에만 사용가능한 알고리즘이다.

정렬된 데이터에서 사용할 수 있는 '고속' 탐색 알고리즘이다. 
sort 기능이 추가된 링크드 리스트에 이진 탐색 기능을 추가한다.

퀵 정렬 알고리즘에 이진탐색 기능을 추가해보겠다.

*/


#include<stdio.h>

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

int BinarySearch(int* dataSet, int length, int findData) {
    
    int center, left, right;
    left =0;
    right = length;

    while(left <= right) {

        center = (left+right) /2;
        
        if(dataSet[center] == findData) return center;
        else if(dataSet[center] > findData) right=center-1;
        else left = center+1;
    }
    
    return -1;

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

    printf("== 이진탐색 실행 ==\n");
    int findIndex;
    if((findIndex = BinarySearch(dataSet, length-1, 1211)) >= 0) {
        printf("이진탐색 ... 데이타가 있다. %d\n", dataSet[findIndex]);
    } else {
        printf("이진탐색 ... 찾는 데이터가 없다.\n");
    }
    

    return 0;
}