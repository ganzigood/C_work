#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Empty 0
#define Occupied 1

typedef char* keyType;
typedef char* valueType;
typedef int statusType;

typedef struct _node {
    keyType key;
    valueType value;

    statusType status;
}Node;

typedef struct _htable {
    Node* table;

    int tableSize;
    int usedSize;
}HTable;

HTable* Init_HTable(int initTableSize);
int Hash_Function_1(keyType key, int len, int tableSize);
int Hash_Function_2(keyType key, int len, int tableSize);
void Insert_HTable(HTable** myHTable, keyType key, valueType value);
void Re_Hashing(HTable** myHTable);
char* GetValue(HTable* myHTable, keyType key);
void Destroy_HTable(HTable* H);