/*
최소 신장 트리
    - 최소 신장 트리는 각 구성 요서가 서로 연결되어 있고 간선에 가중치가 실려 있는 
    '연결된 가중치 그래프(Connected Weighted Graph)'로부터 만들어진다.

프림 알고리즘(Prim's Algorithm)

1. 그래프와 최소 신장 트리를 준비한다. 
2. 그래프의 임의의 정점을 시작 정점으로 최소 신장 트리의 뿌리 노드로 삽입한다.
3. 최소 신장 트리에 삽입된 정점들과 이 정점들의 모든 인접 정점 사이에 있는 간선의 
    가중치를 조사한다. 간선중에 가장 작은 가중치를 골라 이 간선에 연결된 인접 정점을
    최소 신장트리에 삽입한다. 단, 새로 삽입되는 정점은 최소 신장 트리에 삽입된 기존
    노드와 사이클을 형성해서는 안된다.
4. 3의 과정을 반복하다가 최소 신장 트리가 그래프의 모든 정점을 연결하게 되면 종료한다.

해결 과제

1. 어떤 자료구조를 최소 신장 트리에 사용할 것인가? 배열, 링크드 리스트, 트리 등 다양하지만
    그래프를 사용한다.
2. 조사 간선 중 최소 가중치를 가진 것을 골라내는 과정에서의 성능문제. 정점이 하나 추가될 때마다
    조사 대상 간선 집합 속에서 '최소 가중치'를 가진 간선을 찾아야 된다.
    삽입과 삭제가 빠르고 최솟값을 찾는 데 비용도 거의 들지 않는 우선순위 큐를 사용하겠다.
*/


// 준비물 
//     기본 그래프
//     최소 신장 트리로 삽입할 그래프
//     간선을 정렬할 우선순위 큐

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// === 프림 알고리즘에 사용될 우선순위 큐 ===
typedef int element;

typedef struct _heapNode {
    element data;
}heapNode;

typedef struct _heap {
    heapNode* Nodes;
    int capacity;
    int usedSize;
}heap;

heap* Init_Heap(int initialSize) {
    heap* h = (heap*)malloc(sizeof(heap));
    h->capacity = initialSize;
    h->usedSize = 0;
    h->Nodes = (heapNode*)malloc(sizeof(heapNode) * h->capacity);

    return h;
}

void Destroy_Heap(heap* h) {
    free(h->Nodes);
    free(h);
}

int parentIndex(int index) {
    return (int)((index-1)/2);
}

void Insert_Heap(heap* h, element data) {
    if(h->usedSize == h->capacity-1) {
        printf("current capacity : %d // current usedsize : %d\n", h->capacity, h->usedSize);
        h->capacity *= 2;
        h->Nodes = (heapNode*)realloc(h->Nodes, sizeof(heapNode)*h->capacity);
        printf("변경된크기 : %d\n", h->capacity);
    }
    
    int currentIndex = h->usedSize;
    // heapNode* temp = (heapNode*)malloc(sizeof(heapNode));

    h->Nodes[h->usedSize].data = data;
    
    heapNode temp;

    while(1) {
        if(currentIndex <= 1){
            break;
        }

        int pIndex = parentIndex(currentIndex);

        if(h->Nodes[currentIndex].data < h->Nodes[pIndex].data) {
            temp = h->Nodes[currentIndex];
            h->Nodes[currentIndex] = h->Nodes[pIndex];
            h->Nodes[pIndex] = temp;

            currentIndex = pIndex;
        } else {
            break;
        }
    }

    h->usedSize++;
}

element Delete_Heap(heap* h) {
    int returnData = h->Nodes[0].data;
    printf("최소값 : %d\n", returnData);

    h->Nodes[0].data = h->Nodes[h->usedSize-1].data;

    h->usedSize--;
    heapNode* temp = (heapNode*)malloc(sizeof(heapNode));
    
    int cIndex = 0;
    while(cIndex < h->usedSize && (h->Nodes[cIndex].data > h->Nodes[2*cIndex+1].data || 
                                               h->Nodes[cIndex].data > h->Nodes[2*cIndex+2].data)) {
        if(cIndex*2+1 >= h->usedSize) break;
        
        if(h->Nodes[2*cIndex+1].data < h->Nodes[2*cIndex+2].data) {
            memcpy(&temp, &h->Nodes[cIndex], sizeof(heapNode));
            memcpy(&h->Nodes[cIndex],&h->Nodes[2*cIndex+1],sizeof(heapNode));
            memcpy(&h->Nodes[2*cIndex+1], &temp, sizeof(heapNode));

            cIndex = 2*cIndex+1;
        } else {
            memcpy(&temp, &h->Nodes[cIndex], sizeof(heapNode));
            memcpy(&h->Nodes[cIndex],&h->Nodes[2*cIndex+2],sizeof(heapNode));
            memcpy(&h->Nodes[2*cIndex+2], &temp, sizeof(heapNode));

            cIndex = 2*cIndex+2;
        }
    }
    return returnData;
}

void Print_Heap(heap* h) {
    if(h->usedSize == 0 ) {
        printf("출력할 데이터가 없다.\n");
        return;
    }
    printf("우선순위 힙 출력 : ");

    for(int i = 0; i < h->usedSize; i++) {
        printf("%d ", h->Nodes[i].data);
    }
    printf("\n");
}

// ^^^^^ 프림 알고리즘에 사용될 우선순위 큐 ^^^ 


// ================= graph ===========================


#define NotVisit 0
#define Visited 1


typedef int ElementData;

typedef struct _vertex {
    ElementData data;
    int visited;
    int index;

    struct _vertex* next;
    struct _edge* adjList;

}vertex;

typedef struct _edge {
    int weight;
    struct _edge* next;
    
    vertex* from;
    vertex* to;

} edge;

typedef struct _graph {
    vertex* vertices;
    int count;
} graph;

graph* CreateGraph() {
    graph* myGraph = (graph*)malloc(sizeof(graph));
    myGraph->count = 0;
    myGraph->vertices = NULL;
    return myGraph;
}

vertex* CreateVertex(ElementData data){
    vertex* newVertex = (vertex*)malloc(sizeof(vertex));
    newVertex->data = data;
    newVertex->index = -1;
    newVertex->visited = NotVisit;
    newVertex->next= NULL;
    newVertex->adjList = NULL;

    return newVertex;
}

void DestroyVertex(vertex* v) {
    free(v);
}

void DestroyGraph(graph* g) {
    free(g->vertices);
    free(g);
}

void AddVertex(graph* myGraph, vertex* newVertex){

    vertex* cur;
    cur = myGraph->vertices;
    
    if(myGraph->vertices == NULL) {
        myGraph->vertices = newVertex;
        newVertex->next = NULL;
    } else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        newVertex->next = cur->next;
        cur->next = newVertex;
    }

    myGraph->count += 1;

    newVertex->index = myGraph->count - 1;

    printf("정점 입력 완료 정점의 데이타 : %c, 인덱스 : %d\n", newVertex->data, newVertex->index);
}

void AddEdge(vertex* fromVertex, vertex* toVertex, int w) {
    edge* newEdge = (edge*)malloc(sizeof(edge));
    newEdge->from = fromVertex;
    newEdge->to = toVertex;
    newEdge->weight = w;
    
    edge* cur = fromVertex->adjList;

    if(fromVertex->adjList == NULL) {
        newEdge->next = fromVertex->adjList;
        fromVertex->adjList = newEdge;    
    } else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        newEdge->next = cur->next;
        cur->next = newEdge;
    }
}

void PrintGraph(graph* myGraph) {
    vertex* vertexCur;
    edge* edgeCur;
    vertexCur = myGraph->vertices;
    printf("\n===== Show Graph =====\n");
    for(int i = 0; i < myGraph->count; i++) {
        printf("Vertex : %c - Adj : ",vertexCur->data);
        edgeCur = vertexCur->adjList;
        while(edgeCur != NULL) {
            printf("%c[%d] ", edgeCur->to->data, edgeCur->weight);
            edgeCur = edgeCur->next;
        } 
        printf("\n");
        vertexCur= vertexCur->next;
    }
}

void Visit_Reset(graph* G) {
    vertex* V = G->vertices;

    if (V == NULL) {
        printf("have not Vertex!!\n\n");
    }

    while(V !=NULL) {
        V->visited = NotVisit;
        V= V->next;
    }
    printf("\n==방문 초기화 완료==\n");
}


// 깊이 우선 탐색
void DFS(vertex* V) {
    edge* E = NULL;

    printf("vertex : %c\n", V->data);
    V->visited = Visited;
 
    E = V->adjList;

    while(E != NULL) {
        if(E->to != NULL && E->to->visited == NotVisit){
            DFS(E->to);
        }

        E= E->next;
    }
}

// ^^^^^^^^^^^ graph ^^^^^^^^^^^^^^^^^^^^^^^



int main(void) {


    return 0;
}



