/*
체이닝을 이용한 해쉬 테이블

체이닝이란 해시 함수가 서로 다른 키에 대해 같은 주소값을 반환해서 충돌이 발생하면 각 데이터를 해당 주소에 있는 링크드 리스트에 삽입하여 문제를 해결하는 기법을 말한다.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char* keyType;
typedef char* valueType;

typedef struct _node {
    keyType key;
    valueType value;

    struct _node* next;
}Node;

typedef struct _htable {
    Node** nodeList;
    int tableSize;
}HTable;

HTable* Init_HTable(int initTableSize) {
    HTable* myHTable = (HTable*)malloc(sizeof(HTable));
    myHTable->tableSize = initTableSize;
    myHTable->nodeList = (Node**)malloc(sizeof(Node) * (myHTable->tableSize));
    memset(myHTable->nodeList, 0, sizeof(Node*)*initTableSize);

    return myHTable;
}

int Hash_Function(keyType key, int len, int tableSize){
    int index = 0;

    for(int i = 0; i < len; i++) {
        index = (index <<3) + key[i];  // 비트 연산자로 3비트 왼쪽으로 이동 - 해시 테이블 주소의 최대 크기는 14bit이고 자릿수 접기를 통해 얻을 수 있는 해시값는 11bit이다 
    }
    
    return index % tableSize;
}

void Insert_HTable(HTable* myHTable, keyType key, valueType value) {
    int index = Hash_Function(key, strlen(key), myHTable->tableSize);
    // printf("key = %s, address = %d\n", key, index);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if(myHTable->nodeList[index] == NULL) {
        myHTable->nodeList[index] = newNode;
    } else {
        printf("key=%s(address = %d) 충돌 발생 링크드 리스트에 삽입합니다.\n", key,index);
        newNode->next = myHTable->nodeList[index];
        myHTable->nodeList[index] = newNode;
    }

}

char* GetValue(HTable* myHTable, keyType key) {
    int index = Hash_Function(key, strlen(key), myHTable->tableSize);

 
    Node* cur = myHTable->nodeList[index];
    while(cur->key != key) {
        cur = cur->next;
    }
    return cur->value;
}

void Destroy_HTable(HTable* H) {
    free(H->nodeList);
    free(H);
}

int main(void) {
    HTable* HT = Init_HTable(12289);

    Insert_HTable( HT, "MSFT",   "Microsoft Corporation");
    Insert_HTable( HT, "JAVA",   "Sun Microsystems");
    Insert_HTable( HT, "REDH",   "Red Hat Linux");
    Insert_HTable( HT, "APAC",   "Apache Org");
    Insert_HTable( HT, "ZYMZZ",  "Unisys Ops Check"); //  APAC와 충돌 
    Insert_HTable( HT, "IBM",    "IBM Ltd.");
    Insert_HTable( HT, "ORCL",   "Oracle Corporation");
    Insert_HTable( HT, "CSCO",   "Cisco Systems, Inc.");
    Insert_HTable( HT, "GOOG",   "Google Inc.");
    Insert_HTable( HT, "YHOO",   "Yahoo! Inc.");
    Insert_HTable( HT, "NOVL",   "Novell, Inc.");

    printf("\n");
    printf("Key:%s, Value:%s\n", "MSFT",   GetValue( HT, "MSFT" ) );
    printf("Key:%s, Value:%s\n", "REDH",   GetValue( HT, "REDH" ) );
    printf("Key:%s, Value:%s\n", "APAC",   GetValue( HT, "APAC" ) );
    printf("Key:%s, Value:%s\n", "ZYMZZ",  GetValue( HT, "ZYMZZ" ) );
    printf("Key:%s, Value:%s\n", "JAVA",   GetValue( HT, "JAVA" ) );
    printf("Key:%s, Value:%s\n", "IBM",    GetValue( HT, "IBM" ) );
    printf("Key:%s, Value:%s\n", "ORCL",   GetValue( HT, "ORCL" ) );
    printf("Key:%s, Value:%s\n", "CSCO",   GetValue( HT, "CSCO" ) );
    printf("Key:%s, Value:%s\n", "GOOG",   GetValue( HT, "GOOG" ) );
    printf("Key:%s, Value:%s\n", "YHOO",   GetValue( HT, "YHOO" ) );
    printf("Key:%s, Value:%s\n", "NOVL",   GetValue( HT, "NOVL" ) );


    Destroy_HTable(HT);
    return 0;
}