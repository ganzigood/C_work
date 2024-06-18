/*
수식트리 - Expression_Tree

중위 포기식을 후위 표기식으로 변환한 후, 수식트리로 변환한다.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "03_01_Calculator.c"

#define True 1
#define False 0

typedef struct __expression_tree {
    int data;

    struct __expression_tree* LNode;
    struct __expression_tree* RNode;
}ExpressTree;

ExpressTree* MakeNode(char data){
    ExpressTree* newNode = (ExpressTree*)malloc(sizeof(ExpressTree));
    newNode->data = data;
    newNode->LNode = NULL;
    newNode->RNode = NULL;
}

int DelNode(ExpressTree* node) {
    if(node->LNode !=NULL || node->RNode != NULL) {
        printf("%c 노드는 자식 노드가 있습니다. 삭제할 수 없다.\n", node->data);
        return False;
    }
    free(node);

    return True;
}

void LinkLeftSide(ExpressTree* pNode, ExpressTree* cNode) {
    if(pNode->LNode != NULL) {
        ExpressTree* delNode;
        delNode = pNode->LNode;
        DelNode(delNode);
    }
    pNode->LNode = cNode;

}

void LinkRightSide(ExpressTree* pNode, ExpressTree* cNode) {
    if(pNode->RNode != NULL) {
        ExpressTree* delNode;
        delNode = pNode->RNode;
        DelNode(delNode);
    }
    pNode->RNode = cNode;
}

ExpressTree* GetRightNode(ExpressTree* pNode) {
    if (pNode->RNode == NULL) {
        return False;
    } else {
        return pNode->RNode;
    }
}

ExpressTree* GetLeftNode(ExpressTree* pNode) {
    if (pNode->LNode == NULL) {
        return False;
    } else {
        return pNode->LNode;
    }
}

int GetData(ExpressTree* node) {
    return node->data;
}

//전위 순회
void FrontPrintTree(ExpressTree* rootNode) {
    // 구조체 data 변수의 자료형에 따라 형식 지정자를 다르게..
    if(GetLeftNode(rootNode) == NULL && GetRightNode(rootNode) ==NULL) {
        printf("%d ",rootNode->data);
    } else {
        printf("%c ",rootNode->data);
    }

    if(rootNode->LNode !=NULL){
        FrontPrintTree(rootNode->LNode);
    }
    if(rootNode->RNode !=NULL) {
        FrontPrintTree(rootNode->RNode);
    }

}

// 중위 순회
void MidPrintTree(ExpressTree* rootNode) {
    
    if(rootNode->LNode !=NULL){
        MidPrintTree(rootNode->LNode);
    }

    // 구조체 data 변수의 자료형에 따라 형식 지정자를 다르게..
    if(GetLeftNode(rootNode) == NULL && GetRightNode(rootNode) ==NULL) {
        printf("%d ",rootNode->data);
    } else {
        printf("%c ",rootNode->data);
    }

    if(rootNode->RNode !=NULL) {
        MidPrintTree(rootNode->RNode);
    }

}

// 후위 순회
void RearPrintTree(ExpressTree* rootNode) {
    if(rootNode->LNode !=NULL){
        RearPrintTree(rootNode->LNode);
    }
    if(rootNode->RNode !=NULL) {
        RearPrintTree(rootNode->RNode);
    }
    
    // 구조체 data 변수의 자료형에 따라 형식 지정자를 다르게..
    if(GetLeftNode(rootNode) == NULL && GetRightNode(rootNode) ==NULL) {
        printf("%d ",rootNode->data);
    } else {
        printf("%c ",rootNode->data);
    }
}

//후위 순회를 이용한 트리의 제거
void DeleteTree(ExpressTree* rootNode) {
    if(rootNode->LNode !=NULL){
        DeleteTree(rootNode->LNode);
    }
    if(rootNode->RNode !=NULL) {
        DeleteTree(rootNode->RNode);
    }
    // 구조체 data 변수의 자료형에 따라 형식 지정자를 다르게..
    if(GetLeftNode(rootNode) == NULL && GetRightNode(rootNode) ==NULL) {
        printf("삭제할 노드 : %d\n",rootNode->data);
    } else {
        printf("삭제할 노드 : %c\n",rootNode->data);
    }
    free(rootNode);
}

void MakeExpressTree(char* express, ExpressTree** node) {
    int length = strlen(express);
    
    // 메모리의 동적할당 과정에서 express의 주소가 변경되면서 데이타가 깨진다. 
    // 정적 변수인 formula에 express의 값을 복사해서 사용한다.
    char formula[30];
    strcpy(formula,express);
    
    char tokken = formula[length-1];
    express[length-1] = '\0';
    
    switch(tokken) {
        case '+': case '-': case '*': case '/' :
            *node = MakeNode(tokken);
            MakeExpressTree(express, &(*node)->RNode);
            MakeExpressTree(express, &(*node)->LNode);
            break;
        default :
            *node = MakeNode(tokken-'0');
            break;
    }

}


int Calcu_Tree(ExpressTree* rootNode) {
    int lNum;
    int rNum;

    if(GetLeftNode(rootNode) == NULL && GetRightNode(rootNode)==NULL) {
        return GetData(rootNode);
    }

    lNum = Calcu_Tree(GetLeftNode(rootNode));
    rNum = Calcu_Tree(GetRightNode(rootNode));

    switch(GetData(rootNode)){
        case '+' :
            return lNum+rNum;
            break;
        case '-' :
            return lNum-rNum;
            break;
        case '/' :
            return lNum/rNum;
            break;
        case '*' :
            return lNum*rNum;
            break;
    }

    return 0;

}




int main() {
    Stack mystack;
    InitStack(&mystack);

    ExpressTree* myExpressTree = MakeNode('r'); // 임의의 데이타 'r'로 초기화

    char origin_formula[] = "1+2*7";  // 중위 수식으로 입력
    char* changed_formula;

    formula_change(&mystack, origin_formula, &changed_formula);
    printf("입력된 수식 : %s\n",origin_formula);
    printf("변환된 수식 : %s\n",changed_formula);
    printf("\n");

    MakeExpressTree(changed_formula, &myExpressTree);  // 입력된 수식을 후위수식? 으로 변환

    
    printf("수식 트리의 전위순회\n");
    FrontPrintTree(myExpressTree);
    printf("\n");
    printf("수식 트리의 중위순회\n");
    MidPrintTree(myExpressTree);
    printf("\n");
    printf("수식 트리의 후위순회\n");
    RearPrintTree(myExpressTree);
    printf("\n");
    
    int result;
    result = Calcu_Tree(myExpressTree);
    printf("\n");
    printf("계산결과 : %d\n",result);

    printf("\n");
    printf("트리 제거\n");
    DeleteTree(myExpressTree);

    return 0;
}