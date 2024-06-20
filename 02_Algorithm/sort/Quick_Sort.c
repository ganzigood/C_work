/*
'좋은' 기준 요소를 선정하는 것이 성능개선에 도움이 된다. 분할영역의 왼쪽 끝 값을 기준 요소로 정렬하겠다.

*/


#include<stdio.h>

void Quick_Sort(int* dataSet, int left, int right) {
    
    //기준 요소를 분할 영역의 가장 왼쪽 값으로 해보겠다.
    
    int factor = dataSet[left];
    int index;
    int temp;
    int i = left+1;
    int j = right;

    while(i<=j) {
        while(dataSet[i]<factor) {
            i++;
            if(i==j) break;
        }

        while(dataSet[j]>factor){
            j--;
            if(i==j) break;
        }
        if(i>=j) {
            index=i-1;
            temp = dataSet[i-1];
            dataSet[i-1] = dataSet[left];
            dataSet[left] = temp;
            break;
        }
        temp = dataSet[i];
        dataSet[i] = dataSet[j];
        dataSet[j] = temp;
        if(i == j-1){
            index=i;
            temp = dataSet[i];
            dataSet[i] = dataSet[left];
            dataSet[left] = temp;
            break;
        }
        i++;
        j--;
    }
    

    if(left<right) {
        Quick_Sort(dataSet,left,index-1);
        Quick_Sort(dataSet,index+1,right);
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
    Quick_Sort(dataSet,left,right);

    for(int i=0; i<length; i++) {
        printf("%d ",dataSet[i]);
    }
    printf("\n");

    return 0;
}