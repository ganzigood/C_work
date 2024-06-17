/*
기본적인 Tree 자료구조 형태이다.

노드가 데이터를 저장하는 변수 외에 두개의 포인터를 갖는다.
한개는 자식 노드의 포인터를 저장하고, 다른 하나는 형제 노드의 포인터를 저장한다.
부모 노드는 자식노드 중 하나의 포인터만 알면 옆으로 이동하면서 다른 자식 노드를 다 알 수 있다.

*/

#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __tree_node {
    char data;
    struct __tree_node* childNode;
    struct __tree_node* siblingNode;
}Node;

Node* MakeNode(char data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->childNode = NULL;
    newNode->siblingNode = NULL;
}

void MakeChildNode(Node* pNode, Node* cNode) {
    pNode->childNode = cNode;
}

int MakeSiblingNode(Node* oldNode, Node* youngNode) {
    oldNode->siblingNode = youngNode;
}

void PrintTree(Node* node, int depth, int startdepth){

    
    if(depth >= startdepth) {
        if(depth==1) printf("+--");
        if(depth==2) printf("   +--");
        if(depth==3) printf("      +--");
        printf("%c\n", node->data);
    }

    if(node->childNode != NULL) {
        PrintTree(node->childNode, depth+1, startdepth);
    }

    if(node->siblingNode != NULL) {
        PrintTree(node->siblingNode, depth, startdepth);
    }
    
}

int DelNode(Node* node, Node* prevNode){
    if(node->childNode != NULL) {
        printf("노드 %c는 자식 노드가 있습니다. 삭제 불가.\n", node->data);
        return False;
    }
    if(prevNode->childNode == node && node->siblingNode !=NULL) {
        prevNode->childNode = node->siblingNode;
    }else if(prevNode->siblingNode == node && node->siblingNode !=NULL) {
        prevNode->siblingNode = node->siblingNode;
    }else if(prevNode->childNode == node && node->siblingNode == NULL) {
        prevNode->childNode=NULL;
    }else if(prevNode->siblingNode ==node && node->siblingNode == NULL) {
        prevNode->siblingNode=NULL;
    }
    free(node);
}

int DelTree(Node* rootNode) {
    Node* delNode;
    
    delNode= rootNode;
    printf("%c  ", delNode->data);

    if(rootNode->childNode != NULL){
        DelTree(rootNode->childNode);
    }

    if(rootNode->siblingNode != NULL) {
        DelTree(rootNode->siblingNode);
    }

}

int main() {
    Node* A = MakeNode('A');
    Node* B = MakeNode('B');
    Node* C = MakeNode('C');
    Node* D = MakeNode('D');
    Node* E = MakeNode('E');
    Node* F = MakeNode('F');
    Node* G = MakeNode('G');
    Node* H = MakeNode('H');
    Node* I = MakeNode('I');
    Node* J = MakeNode('J');
    Node* K = MakeNode('K');

    MakeChildNode(A,B);
    MakeSiblingNode(B,G);
    MakeSiblingNode(G,I);
    MakeChildNode(B,C);
    MakeSiblingNode(C,D);
    MakeChildNode(D,E);
    MakeSiblingNode(E,F);
    MakeChildNode(G,H);
    MakeChildNode(I,J);
    MakeChildNode(J,K);

    PrintTree(A,0,0);  // (rootNode, 초기값은 무조건 0, 시작 레벨)
    printf("\n");

    printf("노드 E삭제\n");
    DelNode(E,D);
    printf("\n");

    printf("노드 D삭제\n");
    DelNode(D,C);
    printf("\n");

    PrintTree(A,0,0);
    printf("\n");

    return 0;
}