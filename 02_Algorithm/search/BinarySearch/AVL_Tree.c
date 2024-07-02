// 미완이다.


#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0

typedef struct __avl_tree {
    int data;
    struct __avl_tree* lNode;
    struct __avl_tree* rNode;
    struct __avl_tree* pNode;
}AVLtree;

AVLtree* MakeNode(int data) {
    AVLtree* newNode =(AVLtree*)malloc(sizeof(AVLtree));
    newNode->data = data;
    newNode->lNode = NULL;
    newNode->rNode = NULL;
    newNode->pNode = NULL;
    return newNode;
}

AVLtree* ReturnLNode(AVLtree* Node) {
    if (Node->lNode == NULL) {
        return False;
    }
    return Node->lNode;
}

AVLtree* ReturnrNode(AVLtree* Node) {
    if(Node->rNode == NULL) {
        return False;
    }
    return Node->rNode;
}

int ReturnData(AVLtree* Node) {
    return Node->data;
}

void DestroyTree(AVLtree* Node) {
    if(Node->lNode != NULL) DestroyTree(Node->lNode);

    if(Node->rNode != NULL) DestroyTree(Node->rNode);

    printf(" %d ", Node->data);
    free(Node);
}

void DestroyNode(AVLtree* Node) {
    free(Node);
}

int BalanceFactor(AVLtree* rootNode) {
    int left=0;
    int right = 0;
    while(rootNode->lNode != NULL) {
        left++;
        rootNode = rootNode->lNode;
    }

    while(rootNode->rNode != NULL) {
        right++;
        rootNode = rootNode->rNode;
    }

    return left - right;
}

void Rebalance(AVLtree** rootNode) {
    if(BalanceFactor(*rootNode) < 2) {
        return;
    }

}

void InsertNode(AVLtree** rootNode, int data) {
    AVLtree* pNode = NULL;
    AVLtree* cNode = *rootNode;
    
    while(cNode != NULL) {
        if(cNode->data < data) {
            cNode = cNode->rNode;
        } else {
            cNode = cNode->lNode;
        }
        pNode = cNode;
    }

    AVLtree* newNode = MakeNode(data);
    newNode->pNode = pNode;

    if(pNode != NULL){
        if(data < pNode->data) {
            pNode->lNode = newNode;
        } else {
            pNode->rNode = newNode;
        }
    } else {
        *rootNode = newNode;
    }

    Rebalance(rootNode);
}



// 이진 탐색 // 
AVLtree* BinarySearch(AVLtree* Node, int data) {
    while(Node !=NULL) {
        if(data < Node->data) {
            Node = Node->lNode;
        } else if (data > Node->data) {
            Node = Node->rNode;
        } else if(data == Node->data) {
            return Node;
        }
    }
    return NULL;
}

AVLtree* FindMinNode(AVLtree* Node) {
    AVLtree* minNode = Node;
    while(minNode->lNode != NULL) {
        minNode=minNode->lNode;
    }
    return minNode;
}

AVLtree* DeleteNode(AVLtree* Node, AVLtree* PNode, int data) {
    AVLtree* delNode=NULL;
    
    if(Node == NULL) {
        return NULL;
    }

    if(data < Node->data) {
        delNode = DeleteNode(Node->lNode, Node, data);
    } else if(data > Node->data) {
        delNode = DeleteNode(Node->rNode, Node, data);
    } else {
        delNode = Node;

        if(Node->lNode == NULL && Node->rNode == NULL) {
            
            if(PNode->lNode == Node) {
                PNode->lNode = NULL;
            } else {
                PNode->rNode = NULL;
            }

        } else { 
            if(Node->lNode !=NULL && Node->rNode !=NULL) {
                AVLtree* minNode;
                minNode = FindMinNode(Node->rNode);
                delNode = DeleteNode(Node,NULL, minNode->data);
                Node->data=minNode->data;
            } else {
                AVLtree* temp=NULL;
                if(Node->lNode != NULL) {
                    temp = Node->lNode;
                } else{
                    temp = Node->rNode;
                }
                if(PNode->lNode == Node){
                    PNode->lNode = temp;
                } else {
                    PNode->rNode = temp;
                }
                
            }
        }
    }
    return delNode;
}


// === travers === //
//전위순회(Preorder)
void pre_travers(AVLtree* Node) {
    printf(" %d ", Node->data);
    
    if(Node->lNode != NULL) pre_travers(Node->lNode);

    if(Node->rNode != NULL) pre_travers(Node->rNode);
}
//중위순회(Inorder)
void mid_travers(AVLtree* Node) {
    if(Node->lNode != NULL) mid_travers(Node->lNode);

    printf(" %d ", Node->data);

    if(Node->rNode != NULL) mid_travers(Node->rNode);
}
//후위순회(Postorder)
void back_travers(AVLtree* Node) {
    if(Node->lNode != NULL) back_travers(Node->lNode);

    if(Node->rNode != NULL) back_travers(Node->rNode);

    printf(" %d ", Node->data);
}





int main() {
    AVLtree* rootNode = NULL;



    return 0;
}