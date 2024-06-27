/*
이진 탐색 트리는 트리가 기형적으로 성장하면 검색 효율이 극단적으로 떨어진다.
데이터가 아무리 많이 입력되어도 이진 탐색 트리가 균형 있게 성장해서 그 높이가 최소한으로 유지 될 수 있도록 하는 자료구조가 레드 블랙 트리이다.

자료구조 측면에서 레드 블랙 트리와 이진 탐색 트리의 차이점은 노드를 블랙과 레드로 표시한다는 정도(+부모 노드의 포인터를 갖고 있다)이지만, 그 차이점이 트리 전체의 균형을 유지하도록 도와준다.

규칙
1. 모든 노드는 빨간색, 검정색이다.
2. 뿌리 노드는 검정색이다.
3. 잎 노드는 검정색이다.
4. 빨간색 노드의 자식은 모두 검정색이다.(검정색 노드는 빨강, 검정 모두 자식으로 가질 수 있다.)
5. 뿌리 노드와 모든 잎 노드 사이에 있는 검색 노드의 수는 모두 동일하다.

** NIL 노드 : 레드 블랙 트리의 잎노드에는 모두 NIL 노드가 붙어있다. 
                아무 데이터도 갖고 있지 않지만 색깔만 검정색인 더미 노드이다. 센티널(Sentinel) 노드라고도 한다. 
                아무 데이터도 갖고 있지 않은 이 노드에 굳이 저장공간을 할애하는 이유는 구현을 용이하게 만들기 위해서이다. 
                원래의 잎 노드들에 검정색이든 빨간색이든 NIL 노드를 양쪽 자식으로 연결하면 '모든 잎 노드는 검은색'이라는 규칙 하나를 항상 지킬 수 있기 때문이다.
                => NIL노드는 전역으로 한 개만 생성해서 새 노드를 생성할 때마다 이 노드에 연결한다.

기본연산
1. 회전
우회전 : 왼쪽 자식 노드의 오른쪽 자식 노드를 부모 노드의 왼쪽 자식으로 연결
좌회전 : 오른쪽 자식 노드의 왼쪽 자식 노드를 부모 노드의 오르쪽 자식으로 연결

2. 노드 삽입
삽입할 장소를 찾고 연결하는 기본 개념은 이전 탐색 트리와 비슷. 하지만 노드 삽입 때문에 무너졌을지도 모르는 규칙들을 살펴봐야 됨.

레드 블랙 트리에 새 노드를 삽입하면 이 노드를 빨간색으로 표시하고 NIL노드를 이 노드의 양쪽 자식으로 연결

1~5의 규칙중 노드를 삽입 할때 무너질 수 있는 규칙은 4번이다. 이에 따른 대처법을 마련해야한다.
삽입한 노드의 부모노드가 할아버지 노드의 왼쪽(오른쪽) 자식일 때 다음 세 가지 상황 중 하나에 해당하면 4번 규칙을 위반하게 된다.

1. 삼촌도 빨간색 : 부모 노드와 삼촌 노드를 검은색으로 칠하고 할아버지 노드를 빨간색으로 칠한다. 그러나 할아버지 노드를 빨간색으로 칠함으로 다시 4번 규칙이 무너질 수 있게 된다.
                    결국 이 규칙은 계속 올라가서 부모 노드가 검은색이거나 뿌리노드까지 올라가야지 확인이 끝난다.
2. 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 오른쪽(왼쪽) 자식인 경우 : 부모 노드를 좌회전시켜 이 상황을 다음(3번)의 경우와 같은 케이스로 바꿈. 문제의 유형을 바꾼 것이지 문제를 해결한 것은 아니다.
                                                                    새로 삽입한 노드가 부모가 되고 이전의 부모는 자식이 됐다.
3. 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 왼쪽(오른쪽) 자식인 경우 : 부모 노드를 검은색, 할아버지 노드를 빨간색으로 칠한 다음 할아버지 노드를 우회전한다.


3. 노드 삭제 연산 : 기본은 이진 탐색 트리의 삭제와 같다. 거기에 규칙이 무너지는 경우에만 뒤처리를 하면 된다.
    - 빨간색 노드의 삭제에 관해서는 문제될 것이 없다.(빨간색 노드의 삭제가 다섯가지 규칙을 무너뜨리지 않는다.)
    - 검은색 노드의 삭제가 문제다.
        - 가장먼저 5번 규칙이 무너진다.
        - 삭제된 노드의 부모와 자식이 모두 빨간색이면 4번도 무너진다. -> 삭제된 노드를 대체하는 노드를 검은색으로 칠하면 된다.
        - 삭제된 노드의 부모는 빨강, 자식이 검정색이면 -> 대체하는 자식노드에 검정색을 덧입힌다. '이중 흑색'노드를 만든다. 개념적으로 이렇게 하면 5번 규칙은 지키게되고, 1번 규칙이 무너지게 된다. 
                                                    문제를 5번에서 1번으로 바꾼다.
        
    - 이중 흑색노드가 부모의 왼쪽 자식인 경우.
        - 형제가 빨간색인 경우
            - 형제를 검은색, 부모를 빨간색으로 칠한다. 부모를 기준으로 자식 노드를 좌회전한다. 이제 이어서 설명한 경우에 따라 문제를 해결한다.
        - 형제가 검은색이고 형제의 양쪽 자식이 모두 검은색인 경우
            - 형제만 빨간색으로 칠한 후 이중 흑색 노드가 갖고 있던 2개의 검은색 중 하나를 부모 노드에게 넘겨준다. 부모 노드도 그 형제의 상황에 따라 대처한다.
                검은색을 받은 부모가 빨간색이면 그냥 검은색으로 칠하면 된다.
        - 형제가 검은색이고 형제의 왼쪽 자식은 빨간색, 오른쪽 자식은 검은색인 경우
            - 형제 노드를 빨간색으로 칠하고 왼쪽 자식을 검은색으로 칠한 다음 형제 노드를 기준으로 우회전한다.
                이렇게 하면 형제가 검은색이고 형제의 오른쪽 자식이 빨간색인 경우로 바뀌었다.
        - 형제가 검은색이고 형제의 오른쪽 자식이 빨간색인 경우
            - 이중 흑색 노드의 부모 노드가 갖고 있는 색을 형제 노드에 칠한다. 부모 노드와 형제 노드의 오른쪽 자식 노드를 검은색으로 칠하고 부모 노드를 기준으로 좌회전한다.
                이중 흑색 노드의 검은색 하나를 뿌리 노드로 넘긴다. 뿌리 노드가 이중 흑색인 경우는 검은색으로 칠하면 끝이다.
                                    
*/



#include<stdio.h>
#include<stdlib.h>

typedef int Element;

typedef struct __rbtnode {
    struct __rbtode* Parent;
    struct __rbtode* Left;
    struct __rbtode* Right;
    
    enum{Red, Black} Color;

    Element data;
}rbtnode;

rbtnode* NIL;       // sentinel 노드의 전역 선언

rbtnode* Create_Node(Element data) {
    rbtnode* newNode = (rbtnode*)malloc(sizeof(rbtnode));
    newNode->data = data;
    newNode->Color = Black;
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->Parent = NULL;

    return newNode;
}

void Free_Node(rbtnode* node) {
    free(node);
}

void Free_Tree(rbtnode* rootNode) {
    if(rootNode->Left != NIL) {
        LeftNode(rootNode);
    }
    if(rootNode->Right != NIL) {
        RightNode(rootNode);
    }

    Free_Node(rootNode);  // NIL 노드는 free 안됨.
}

rbtnode* LeftNode(rbtnode* node) {
        return node->Left;
}
rbtnode* RightNode(rbtnode* node) {
        return node->Right;
}

rbtnode* FindNode(rbtnode* rootNode, Element searchData) {
    if(searchData < rootNode->data) {
        FindNode(rootNode->Left, searchData);
    } else if(searchData > rootNode->data) {
        FindNode(rootNode->Right, searchData);
    } else if(searchData == rootNode->data){
        return rootNode;
    } else {
        return NULL;
    }
}


/*
========= 회전 ===========
우회전 : 왼쪽 자식 노드의 오른쪽 자식 노드를 회전하는 노드의 왼쪽 자식으로 연결
*/
void Right_Rotate(rbtnode** rootNode, rbtnode* node) {
    
    rbtnode* CNode = node->Left;
    if(node == *rootNode){
        CNode->Right = node->Left;
        *rootNode = CNode;
        return;
    }

    rbtnode* Pnode = node->Parent;
    if(node == Pnode->Left) {
        Pnode->Left = node->Left;
        if(CNode->Right !=NIL) CNode->Right = node->Left;
    } else {
        Pnode->Right = node->Left;
        if(CNode->Right !=NIL) CNode->Right = node->Left;
    }
}
/*
좌회전 : 오른쪽 자식 노드의 왼쪽 자식 노드를 회전하는 노드의 오르쪽 자식으로 연결
*/
void Left_Rotate(rbtnode** rootNode, rbtnode* node) {
    rbtnode* CNode = node->Right;

    if(node == *rootNode){
        CNode->Left = node->Right;
        *rootNode = CNode;
        return;
    }

    rbtnode* Pnode = node->Parent;
    if(node == Pnode->Left) {
        Pnode->Left = node->Right;
        if(CNode->Left != NIL) CNode->Left = node->Right;
    } else {
        Pnode->Right = node->Right;
        if(CNode->Left !=NIL) CNode->Left = node->Right;
    }
}


// 이진 탐색 트리의 기본적인 삽입 과정
void Insert_Node_Helper(rbtnode** rootNode, rbtnode* newNode) {
    
    if(*rootNode == NULL) {
        *rootNode = newNode;
    }

    if(newNode->data < (*rootNode)->data) {
        if((*rootNode)->Left == NIL) {
            (*rootNode)->Left = newNode;
            newNode->Parent = (*rootNode);
        } else {
            Insert_Node_Helper(&(*rootNode)->Left, newNode);
        }
    } else {
        if((*rootNode)->Right == NIL) {
            (*rootNode)->Right = newNode;
            newNode->Parent = rootNode;
        } else {
            Insert_Node_Helper(&(*rootNode)->Right, newNode);
        }
    }
}

/*
===== 노드 삽입 =====
삽입할 장소를 찾고 연결하는 기본 개념은 이전 탐색 트리와 비슷. 하지만 노드 삽입 때문에 무너졌을지도 모르는 규칙들을 살펴봐야 됨.

레드 블랙 트리에 새 노드를 삽입하면 이 노드를 빨간색으로 표시하고 NIL노드를 이 노드의 양쪽 자식으로 연결

1~5의 규칙중 노드를 삽입 할때 무너질 수 있는 규칙은 4번(빨간색 노드의 자식은 모두 검정색이다. 검정색 노드는 빨강, 검정 모두 자식으로 가질 수 있다.)이다. 
이에 따른 대처법을 마련해야한다. 삽입한 노드의 부모노드가 할아버지 노드의 왼쪽(오른쪽) 자식일 때 다음 세 가지 상황 중 하나에 해당하면 4번 규칙을 위반하게 된다.

1. 삼촌도 빨간색 : 부모 노드와 삼촌 노드를 검은색으로 칠하고 할아버지 노드를 빨간색으로 칠한다. 그러나 할아버지 노드를 빨간색으로 칠함으로 다시 4번 규칙이 무너질 수 있게 된다.
                    결국 이 규칙은 계속 올라가서 부모 노드가 검은색이거나 뿌리노드까지 올라가야지 확인이 끝난다.
2. 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 오른쪽(왼쪽) 자식인 경우 : 부모 노드를 좌회전시켜 이 상황을 다음(3번)의 경우와 같은 케이스로 바꿈. 문제의 유형을 바꾼 것이지 문제를 해결한 것은 아니다.
                                                                    새로 삽입한 노드가 부모가 되고 이전의 부모는 자식이 됐다.
3. 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 왼쪽(오른쪽) 자식인 경우 : 부모 노드를 검은색, 할아버지 노드를 빨간색으로 칠한 다음 할아버지 노드를 우회전한다.
*/

// 이진 탐색 트리의 삽입후 레드 블랙 트리의 무너진 규칙을 확인하고 조정한다.
void Insert_After_Rebuild(rbtnode** rootNode, rbtnode* newNode){
    rbtnode* PNode = newNode->Parent;
    if(PNode == *rootNode) {
        (*rootNode)->Color = Black;
        return;
    }
    rbtnode* GPNode = PNode->Parent;
    
    while(PNode->Color == Red) {
        
        if(PNode == GPNode->Left) {
            rbtnode* uncle = GPNode->Right;
            if(uncle == Red) {
                PNode->Color = Black;
                uncle->Color = Black;
                GPNode->Color = Red;
                Insert_After_Rebuild(rootNode, GPNode);
            } else if(uncle == Black && newNode == PNode->Right){
                Left_Rotate(rootNode, PNode);
                Insert_After_Rebuild(rootNode, PNode);
            } else if(uncle == Black && newNode == PNode->Left) {
                PNode->Color = Black;
                GPNode->Color = Red;
                Right_Rotate(rootNode, GPNode);
            }
        } else if(PNode == GPNode->Right) {
            rbtnode* uncle = GPNode->Left;
            if(uncle == Red) {
                PNode->Color = Black;
                uncle->Color = Black;
                GPNode->Color = Red;
                Insert_After_Rebuild(rootNode, GPNode);
            } else if(uncle == Black && newNode == PNode->Right){
                Right_Rotate(rootNode, PNode);
                Insert_After_Rebuild(rootNode, PNode);
            } else if(uncle == Black && newNode == PNode->Left) {
                PNode->Color = Black;
                GPNode->Color = Red;
                Left_Rotate(rootNode, GPNode);
            }

        }

    }
    (*rootNode)->Color = Black;
    
}

// 노드 삽입을 하는 기본 함수!
void Insert_Node(rbtnode** rootNode, Element newData){
    rbtnode* newNode = Create_Node(newData);

    Insert_Node_Helper(rootNode, newNode);  // 이진 탐색 트리의 삽입 과정을 진행.
    
    newNode->Color = Red;
    newNode->Left = NIL;
    newNode->Right = NIL;

    rbtnode* parentNode = newNode->Parent;

    Insert_After_Rebuild(rootNode, newNode);
}



// 노드를 제거하는 기본 함수!
void Delete_Node(rbtnode** rootNode, Element delData){
    rbtnode* delNode = FindNode(*rootNode, delData);

    Delete_Node_Helper(rootNode, delNode);




    (*rootNode)->Color = Black;
}




int main() {
    rbtnode* rootNode = NULL;
    rbtnode* Node = NULL; 

    // 전역변수 NIL(sentinel 노드) 초기화
    NIL = Create_Node(0);
    NIL->Left = NULL;
    NIL->Right = NULL;
    NIL->Color = Black;


}