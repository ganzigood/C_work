/*
나눗셈법을 사용한 HashTable.

노드의 key변수는 주소로 사용할 데이터이다. 이 값을 해쉬 함수에 넣어서 나온 값을 주소로 사용한다.
value값은  Key로 얻어낸 주소에 저장할 데이터이다.

쉬운 방법이지만. 충돌, 즉 해쉬 함수가 동일한 주소 값을 반환할 가능성이 높고 해시 테이블 내 일부 지역의 주소들을 집중적으로 반환함을쏘 데이터가 한 곳에 모이는 문제인 클러스터가 발생할 가능성이 높다.

*/

#include<stdio.h>
#include<stdlib.h>

typedef int keyType;
typedef int valueType;

typedef struct _node {
    keyType key;
    valueType value;
}Node;

typedef struct _shtable {
    Node* node;
    int tableSize;
}SHTable;

SHTable* Init_SHTable(int initTableSize) {
    SHTable* mySHTable = (SHTable*)malloc(sizeof(SHTable));
    mySHTable->tableSize = initTableSize;
    mySHTable->node = (Node*)malloc(sizeof(Node) * (mySHTable->tableSize));

    return mySHTable;
}

int Hash_Function(keyType key, int tableSize){
    return key % tableSize;
}

void Insert_SHTable(SHTable* mySHTable, keyType key, valueType value) {
    int index = Hash_Function(key, mySHTable->tableSize);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;

    mySHTable->node[index] = *newNode;
}

int GetValue(SHTable* mySHTable, keyType key) {
    int index = Hash_Function(key, mySHTable->tableSize);

    return mySHTable->node[index].value;
}

void Destroy_SHTable(SHTable* H) {
    free(H->node);
    free(H);
}

int main(void) {
    SHTable* mySHTable = Init_SHTable(193);

    Insert_SHTable(mySHTable, 418, 32114);
    Insert_SHTable(mySHTable, 9, 514);
    Insert_SHTable(mySHTable, 27, 8917);
    Insert_SHTable(mySHTable, 1031, 286);

    printf("Key: %d, Value: %d\n", 418, GetValue(mySHTable,418));
    printf("Key: %d, Value: %d\n", 1031, GetValue(mySHTable,1031));
    printf("Key: %d, Value: %d\n", 9, GetValue(mySHTable,9));


    Destroy_SHTable(mySHTable);
    return 0;
}