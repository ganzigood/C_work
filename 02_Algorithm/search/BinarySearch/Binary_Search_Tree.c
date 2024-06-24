/* 
이진 탐색 트리(Binary Search Tree) - '이진 탐색'을 위한 트리이자 탐색을 위한 '이진 트리'

이진 탐색 트리가 필요한 이유는 이진 탐색은 배열에만 사용 가능한 알고리즘이기 때문이다.
이진 탐색을 사용하려면 데이터의 처음과 끝을 알아야 하고 순식간에 데이터의 중앙 요소를 계산할 수 있어야 한며, 계산된 중앙 요소에 즉시 접근할 수 있어야 한다.
링크드 리스트는 위와 같은 작업들이 불가능한 자료구조이다. 처음과 끝(헤드, 테일)은 알 수 있으나 '중앙 요소'는 알 수 없다.

링크드 리스트처럼 동적으로 노드를 추가하거나 제거할 수 있으면서 이진 탐색 알고리즘도 사용할 수 있는 자료구자가 바로 **** 이진 탐색 트리 *** 이다.

규칙. 왼쪽 자식 노드는 나보다 작고 오른쪽 자식 노드는 나보다 크다.

=====

이진 탐색 트리를 만들어보고 전위, 중위, 후위 순회도 다시한번 만들어보자.

*/


#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __binarysearchtree {
    int data;
    struct __binarysearchtree* LNode;
    struct __binarysearchtree* RNode;
}BSTree;

BSTree* MakeNode(int data) {
    BSTree* newNode =(BSTree*)malloc(sizeof(BSTree));
    newNode->data = data;
    newNode->LNode = NULL;
    newNode->RNode = NULL;
    return newNode;
}

BSTree* MakeSubTree(BSTree* Node, int data) {
    
    if(data < Node->data) {
        if(Node->LNode == NULL){
            Node->LNode = MakeNode(data);
        } else {
            MakeSubTree(Node->LNode, data);
        }
    } else if (data > Node->data) {
        if(Node->RNode == NULL) {
            Node->RNode = MakeNode(data);
        } else {
            MakeSubTree(Node->RNode, data);
        }
    }
}

int ReturnData(BSTree* Node) {
    return Node->data;
}

BSTree* ReturnLNode(BSTree* Node) {
    if (Node->LNode == NULL) {
        return False;
    }
    return Node->LNode;
}

BSTree* ReturnRNode(BSTree* Node) {
    if(Node->RNode == NULL) {
        return False;
    }
    return Node->RNode;
}

// 이진 탐색 // 
BSTree* BinarySearch(BSTree* Node, int data) {
    while(Node !=NULL) {
        if(data < Node->data) {
            Node = Node->LNode;
        } else if (data > Node->data) {
            Node = Node->RNode;
        } else if(data == Node->data) {
            return Node;
        }
    }
    return NULL;
}

BSTree* FindMinNode(BSTree* Node) {
    BSTree* minNode = Node;
    while(minNode->LNode != NULL) {
        minNode=minNode->LNode;
    }
    return minNode;
}

BSTree* DeleteNode(BSTree* Node, BSTree* PNode, int data) {
    BSTree* delNode=NULL;
    BSTree* temp=NULL;
    BSTree* minNode=NULL;

    if(Node == NULL) {
        return NULL;
    }

    if(data < Node->data) {
        DeleteNode(Node->LNode, Node, data);
    } else if(data > Node->data) {
        DeleteNode(Node->RNode, Node, data);
    } else {
        delNode = Node;

        if(delNode->LNode == NULL && delNode->RNode == NULL) {
            free(delNode);
        } else { 
            if(delNode->LNode !=NULL && delNode->RNode !=NULL) {
                minNode = FindMinNode(delNode->RNode);
                DeleteNode(delNode,NULL, minNode->data);
                Node->data=minNode->data;
            } else {
                if(delNode->LNode != NULL) {
                    temp = delNode->LNode;
                } else{
                    temp = delNode->RNode;
                }
                if(PNode->LNode == delNode){
                    PNode->LNode = temp;
                } else {
                    PNode->RNode = temp;
                }
            }
        }

    }
    
}


// === travers === //
//전위순회
void pre_travers(BSTree* Node) {
    printf(" %d ", Node->data);
    
    if(Node->LNode != NULL) pre_travers(Node->LNode);

    if(Node->RNode != NULL) pre_travers(Node->RNode);
}
//중위순회
void mid_travers(BSTree* Node) {
    if(Node->LNode != NULL) mid_travers(Node->LNode);

    printf(" %d ", Node->data);

    if(Node->RNode != NULL) mid_travers(Node->RNode);
}
//후위순회
void back_travers(BSTree* Node) {
    if(Node->LNode != NULL) back_travers(Node->LNode);

    if(Node->RNode != NULL) back_travers(Node->RNode);

    printf(" %d ", Node->data);
}




int main() {
    BSTree* rootNode = MakeNode(23);
    printf("rootNode의 데이타 : %d\n", rootNode->data);
    MakeSubTree(rootNode, 11);
    MakeSubTree(rootNode, 1);
    MakeSubTree(rootNode, 139);
    MakeSubTree(rootNode, 67);

    printf("\n전위순회 : ");
    pre_travers(rootNode);
    printf("\n중위순회 : ");
    mid_travers(rootNode);
    printf("\n후위순회 : ");
    back_travers(rootNode);

    printf("\n\n노드 추가(+16,13,20,15)\n");
    MakeSubTree(rootNode, 16);
    MakeSubTree(rootNode, 13);
    MakeSubTree(rootNode, 20);
    MakeSubTree(rootNode, 15);

    printf("\n전위순회 : ");
    pre_travers(rootNode);
    printf("\n중위순회 : ");
    mid_travers(rootNode);
    printf("\n후위순회 : ");
    back_travers(rootNode);



    printf("\n=== binary search ===\n");
    BSTree* findNode;
    if((findNode = BinarySearch(rootNode, 11)) != NULL) {
        printf("찾는 노드의 데이터 : %d\n",findNode->data);
    } else {
        printf("찾는 데이터가 없다.\n");
    }
    
    if((findNode = BinarySearch(rootNode, 1111)) != NULL) {
        printf("찾는 노드의 데이터 : %d\n",findNode->data);
    } else {
        printf("찾는 데이터가 없다.\n");
    }



    printf("\n=== 이진 탐색 트리의 노드 삭제 ===\n");
    int data =1111;
    if(DeleteNode(rootNode, NULL, data) == NULL) {
        printf("%d - 해당 노드가 존재하지 않는다.\n", data);
    } else {
        printf("%d 노드 삭제",data);
    }
    
    data =11;
    if(DeleteNode(rootNode, NULL, data) == NULL) {
        printf("%d - 해당 노드가 존재하지 않는다.\n", data);
    } else {
        printf("%d 노드 삭제",data);
    }

    printf("\n후위순회 : ");
    back_travers(rootNode);

    return 0;
}