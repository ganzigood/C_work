/*
- 퀵 정렬 -

분할 정복에 바탕을 둔 알고리즘
퀵 정렬의 알고리즘을 한마디로 요약하면 기준 요소 선정 및 분할의 반복이다.
'좋은' 기준 요소를 선정하는 것이 성능개선에 도움이 된다. 분할영역의 왼쪽 끝 값을 기준 요소로 정렬하겠다.

*/



#include<stdio.h>


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

    

int main() {
    int dataSet[] = {5,1,6,4,8,3,7,9,2};
    int length = sizeof(dataSet)/sizeof(int);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    int left = 0;
    int right = length-1;
    QuickSort(dataSet,left,right);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    return 0;
}