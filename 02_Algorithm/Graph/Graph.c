/*
그래프
- 인접 리스트

- 깊이 우선 탐색 (DFS)

- 너비 우선 탐색 (BFS)

*/

#include <stdio.h>
#include <stdlib.h>

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

// 너비 우선 탐색 링크드 큐를 사용한다.
typedef struct _queue {
    vertex* head;
    vertex* tail;
    vertex* cur;
    int count;
}queue;


void Init_Queue(queue** myQueue) {
    
    (*myQueue)= (queue*)malloc(sizeof(queue));
    (*myQueue)->head = NULL;
    (*myQueue)->tail = NULL;
    (*myQueue)->cur = NULL;
    (*myQueue)->count = 0;
}

void En_Queue(queue* myQueue, vertex* V) {

    if(myQueue->head == NULL) {
        myQueue->head = V;
        myQueue->tail = V;
        myQueue->tail->next = NULL;
    } else {
        V->next = myQueue->tail->next;
        myQueue->tail->next = V;
        myQueue->tail = myQueue->tail->next;
    }
    myQueue->count += 1;
}

vertex* De_Queue(queue* myQueue) {
    vertex* returnData = myQueue->head;

    myQueue->head = myQueue->head->next;

    myQueue->count -= 1;

    return returnData;
}

void Destroy_Queue(queue* Q){
    free(Q);
}

void BFS(vertex* V, queue* Q) {
    printf("vertex : %c\n",V->data);
    V->visited = Visited;

    En_Queue(Q,V);
    
    while(Q->head != NULL) {
        
        vertex* deV = De_Queue(Q);

        edge* E = deV->adjList;

        while(E != NULL) {
            if(E->to->visited != Visited){
                printf("vertex : %c\n", E->to->data);
                E->to->visited = Visited;
                En_Queue(Q,E->to);
            }
            E= E->next;
        }
    }
 }

int main( void )
{
    //  그래프 생성     
    graph* G = CreateGraph();
    
    //  정점 생성 
    vertex* V1 = CreateVertex( '1' );
    vertex* V2 = CreateVertex( '2' );
    vertex* V3 = CreateVertex( '3' );
    vertex* V4 = CreateVertex( '4' );
    vertex* V5 = CreateVertex( '5' );
    vertex* V6 = CreateVertex( '6' );
    vertex* V7 = CreateVertex( '7' );

    //  그래프에 정점을 추가 
    AddVertex( G, V1 );
    AddVertex( G, V2 );
    AddVertex( G, V3 );
    AddVertex( G, V4 );
    AddVertex( G, V5 );
    AddVertex( G, V6 );
    AddVertex( G, V7 );

    //  정점과 정점을 간선으로 잇기 
    AddEdge( V1, V2, 0);
    AddEdge( V1, V3, 0);
    
    AddEdge( V2, V4, 0);
    AddEdge( V2, V5, 0);

    AddEdge( V3, V4, 0);
    AddEdge( V3, V6, 0);

    AddEdge( V4, V5, 0);
    AddEdge( V4, V7, 0);

    AddEdge( V5, V7, 0);

    AddEdge( V6, V7, 0);

    PrintGraph( G );

    printf("\n=== 깊이 우선 탐색 ===\n");
    DFS(G->vertices);

    Visit_Reset(G);

    printf("\n=== 넓이 우선 탐색 ===\n");
    queue* Q;
    Init_Queue(&Q);
    BFS(G->vertices, Q);

    //  큐 소멸
    Destroy_Queue(Q);
    //  그래프 소멸 
    DestroyGraph( G );

    return 0;
}


