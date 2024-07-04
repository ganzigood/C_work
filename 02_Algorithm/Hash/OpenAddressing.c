/*
개방주소법

링크드 리스트가 아닌 해쉬 테이블에 직접 데이터를 저장한다.(배열)

충돌이 일어났을 때는 이중 해싱으로 새 주소를 탐사. 

데이터가 해시 테이블 공간을 50% 이상 차지하면 재해싱하여 테이블의 크기를 늘리도록 조치한다.

*/

#include "OpenAddressing.h"

HTable* Init_HTable(int initTableSize) {
    HTable* myHTable = (HTable*)malloc(sizeof(HTable));
    myHTable->tableSize = initTableSize;
    myHTable->table = (Node*)malloc(sizeof(Node) * (myHTable->tableSize));
    myHTable->usedSize = 0;
    
    return myHTable;
}

int Hash_Function_1(keyType key, int len, int tableSize){
    int index = 0;

    for(int i = 0; i < len; i++) {
        index = (index <<3) + key[i];  // 비트 연산자로 3비트 왼쪽으로 이동 - 해시 테이블 주소의 최대 크기는 14bit이고 자릿수 접기를 통해 얻을 수 있는 해시값는 11bit이다 
    }
    
    return index % tableSize;
}

// 첫번째 해쉬 펑션의 주소가 점유된 상태인 경우 두번째 해쉬펑션을 불러서 첫번째 주소값 + 두번째 주소값만큼 거리를 둔다.
int Hash_Function_2(keyType key, int len, int tableSize){
    int index = 0;

    for(int i = 0; i < len; i++) {
        index = (index <<2) + key[i];  
    }
    
    return index % (tableSize-3);
}




void Insert_HTable(HTable** myHTable, keyType key, valueType value) {
    
    int index = Hash_Function_1(key, strlen(key), (*myHTable)->tableSize);

    Node newNode;
    newNode.key = key;
    newNode.value = value;
    newNode.status = Occupied;

    if((*myHTable)->table[index].status != Occupied) {
        (*myHTable)->table[index] = newNode;
    } else {
        while((*myHTable)->table[index].status == Occupied) {
            printf("(key : %s) 충돌 발생\n",key);
            index += Hash_Function_2(key, strlen(key), (*myHTable)->tableSize);
            if(index > (*myHTable)->tableSize){
                index = index - (*myHTable)->tableSize;
            }
        }
        (*myHTable)->table[index] = newNode;
    }
    (*myHTable)->usedSize += 1;

    printf("key(%s) entered at address(%d)\n", key, index);

    if((*myHTable)->usedSize > ((*myHTable)->tableSize)/2) {
        Re_Hashing(myHTable);
    }

}

void Re_Hashing(HTable** myHTable) {
    
    HTable* newH = (HTable*)malloc(sizeof(HTable));
    newH->tableSize = (*myHTable)->tableSize * 2;
    newH->table = (Node*)malloc(sizeof(Node) * newH->tableSize);
    newH->usedSize = 0;

    printf("\nRe Hasing~~ new tablesize = %d\n", newH->tableSize);

    for(int i=0; i < (*myHTable)->tableSize; i++) {
        if((*myHTable)->table[i].status == Occupied) {
            Insert_HTable(&newH, (*myHTable)->table[i].key, (*myHTable)->table[i].value);
        }
    }
    Destroy_HTable(*myHTable);
    *myHTable = newH;
}

char* GetValue(HTable* myHTable, keyType key) {
    int index = Hash_Function_1(key, strlen(key), myHTable->tableSize);

    if(myHTable->table[index].key != key) {
        while(myHTable->table[index].key != key) {
            index = index + Hash_Function_2(key, strlen(key), myHTable->tableSize);
        }
    }
    return myHTable->table[index].value; 
}

void Destroy_HTable(HTable* H) {
    free(H->table);
    free(H);
}

int main(void) {
    HTable* HT = Init_HTable(11);

    Insert_HTable( &HT, "MSFT",   "Microsoft Corporation");
    Insert_HTable( &HT, "JAVA",   "Sun Microsystems");
    Insert_HTable( &HT, "REDH",   "Red Hat Linux");
    Insert_HTable( &HT, "APAC",   "Apache Org");
    Insert_HTable( &HT, "ZYMZZ",  "Unisys Ops Check");
    Insert_HTable( &HT, "IBM",    "IBM Ltd.");
    Insert_HTable( &HT, "ORCL",   "Oracle Corporation");
    Insert_HTable( &HT, "CSCO",   "Cisco Systems, Inc.");
    Insert_HTable( &HT, "GOOG",   "Google Inc.");
    Insert_HTable( &HT, "YHOO",   "Yahoo! Inc.");
    Insert_HTable( &HT, "NOVL",   "Novell, Inc.");

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