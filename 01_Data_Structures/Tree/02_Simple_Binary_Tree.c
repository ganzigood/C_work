/*
단순한 이진 트리이다. 

이진 트리의 경우 수식이진트리, 빠른 데이터 검색을 가능하게 하는 이진 탐색 트리 알고리즘에 사용한다.

이진 트리는 일반 트리처럼 나무 모양의 자료(조직도 같은)를 담기 위한 자료구조가 아니다. 컴파일러나 검색과 같은 알고리즘의 뼈대가 되는 특별한 자료구조이다.

재귀를 이용한 전위, 중위, 후위 순회를 구현한다. 
*/


#include<stdio.h>
#include<stdlib.h>

#define True 1;
#define False 0;

typedef struct __sbtree {
    char data;

    struct __sbtree* LNode;
    struct __sbtree* RNode;
} SBTree;

SBTree* MakeNode(char data){
    SBTree* newNode = (SBTree*)malloc(sizeof(SBTree));
    newNode->data = data;
    newNode->LNode = NULL;
    newNode->RNode = NULL;
}

void LinkLeftSide(SBTree* pNode, SBTree* cNode) {
    if(pNode->LNode != NULL) {
        SBTree* delNode;
        delNode = pNode->LNode;
        DelNode(delNode);
    }
    pNode->LNode = cNode;

}

void LinkRightSide(SBTree* pNode, SBTree* cNode) {
    if(pNode->RNode != NULL) {
        SBTree* delNode;
        delNode = pNode->RNode;
        DelNode(delNode);
    }
    pNode->RNode = cNode;
}

//전위 순회
void FrontPrintTree(SBTree* rootNode) {
    printf("%c ",rootNode->data);

    if(rootNode->LNode !=NULL){
        FrontPrintTree(rootNode->LNode);
    }
    if(rootNode->RNode !=NULL) {
        FrontPrintTree(rootNode->RNode);
    }

}

// 중위 순회
void MidPrintTree(SBTree* rootNode) {
    
    if(rootNode->LNode !=NULL){
        MidPrintTree(rootNode->LNode);
    }

    printf("%c ",rootNode->data);

    if(rootNode->RNode !=NULL) {
        MidPrintTree(rootNode->RNode);
    }

}

// 후위 순회
void RearPrintTree(SBTree* rootNode) {
    if(rootNode->LNode !=NULL){
        RearPrintTree(rootNode->LNode);
    }
    if(rootNode->RNode !=NULL) {
        RearPrintTree(rootNode->RNode);
    }
    printf("%c ",rootNode->data);

}

int DelNode(SBTree* node) {
    if(node->LNode !=NULL || node->RNode != NULL) {
        printf("%c 노드는 자식 노드가 있습니다. 삭제할 수 없다.\n", node->data);
        return False;
    }
    free(node);

    return True;
}

int main() {
    SBTree* A = MakeNode('A');
    SBTree* B = MakeNode('B');
    SBTree* C = MakeNode('C');
    SBTree* D = MakeNode('D');
    SBTree* E = MakeNode('E');
    SBTree* F = MakeNode('F');
    SBTree* G = MakeNode('G');

    LinkLeftSide(A,B);
    LinkLeftSide(B,C);
    LinkRightSide(B,D);
    LinkRightSide(A,E);
    LinkRightSide(E,G);
    LinkLeftSide(E,F);

    printf("전위 순회\n");
    FrontPrintTree(A);
    printf("\n");
    printf("중위 순회\n");
    MidPrintTree(A);
    printf("\n");
    printf("후위 순회\n");
    RearPrintTree(A);
    printf("\n");

    printf("노드삭제\n");
    DelNode(B);

    return 0;
}