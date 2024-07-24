// 깊이우선 탐색(DFS) + 위상정렬(TS. 링크드 리스트 활용)

#include<stdio.h>
#include<stdlib.h>

#define NotVisit 0
#define Visited 1

typedef char ElementData;

typedef struct _vertex {
    ElementData data;
    int visited;
    int index;

    struct _vertex* next;
    struct _edge* adjList;
} vertex;

typedef struct _edge {
    int weight;
    struct _edge* next;

    vertex* from;
    vertex* to;
}edge;

typedef struct _graph {
    vertex* vertices;
    int count;
}graph;

// ==== 위상정렬에 사용할 링크드 리스트 ==== 

typedef struct _listnode {
    ElementData data;
    struct _linkedlist* next;
}listNode;

typedef struct _linkedlist {
    listNode* head;
    listNode* cur;
}linkedList;

// ====================================

graph* CreateGraph() {
    graph* g = (graph*)malloc(sizeof(graph));
    g->count = 0;
    g->vertices = NULL;

    return g;
}

void DestroyGraph(graph* g) {
    free(g);
}

vertex* CreateVertex(ElementData data) {
    vertex* v = (vertex*)malloc(sizeof(vertex));
    v->data = data;
    v->visited = NotVisit;
    v->index = 0;
    v->next = NULL;
    v->adjList = NULL;
}

void DestroyVertex(vertex* v)  {
    free(v);
}

edge* CreateEdge(vertex* From, vertex* to, int weight) {
    edge* e = (edge*)malloc(sizeof(edge));
    e->weight = 0;
    e->from = From;
    e->to = to;
    e->next = NULL;
}

void DestroyEdge(edge* e) {
    free(e);
}

void AddVertex(graph* g, vertex* v) {
    vertex* cur;
    cur = g->vertices;
    
    if(g->vertices == NULL) {
        v->next = g->vertices;
        g->vertices = v;
        v->index = g->count;
        g->count++;
    } else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        v->next = cur->next;
        cur->next = v;
        v->index = g->count;
        g->count++;
    }
}

void AddEdge(vertex* v, edge* e) {
    edge* cur;
    cur = v->adjList;

    if(v->adjList == NULL) {
        e->next = v->adjList;
        v->adjList = e;
    }else {
        while(cur->next != NULL) {
            cur = cur->next;
        }
        e->next = cur->next;
        cur->next = e;
    }
}

void PrintGraph(graph* g){
    vertex* vCur;
    edge* eCur;

    printf("====== 그래프 출력 ====== \n");
    vCur = g->vertices;
    while(vCur != NULL) {
        printf("vertex : %c", vCur->data);
        eCur = vCur->adjList;
        printf("  edge : ");
        while(eCur != NULL) {
            printf("%c ", eCur->to->data);
            eCur = eCur->next;
        }
        vCur = vCur->next;
        printf("\n");
    }
}

// ======= 방문 초기화 함수 =========
void Visit_Reset(graph* G) {
    vertex* V = G->vertices;

    if (V == NULL) {
        printf("have not Vertex!!\n\n");
    }

    while(V !=NULL) {
        V->visited = NotVisit;
        V= V->next;
    }
    printf("==방문 초기화 완료==\n");
}


// ======  깊이 우선 탐색 DFS =======
void DFS(vertex* v) {    
    edge* eCur =NULL;

    printf("%c ", v->data);
    v->visited = Visited;

    eCur = v->adjList;
    
    while (eCur != NULL) {
        if(eCur->to != NULL && eCur->to->visited != Visited) {
            DFS(eCur->to);
        }

        eCur = eCur->next;
    }

}

int main() {
    graph* graph = CreateGraph();
    
    //  정점 생성 
    
    vertex* A = CreateVertex( 'A' );
    vertex* B = CreateVertex( 'B' );
    vertex* C = CreateVertex( 'C' );
    vertex* D = CreateVertex( 'D' );
    vertex* E = CreateVertex( 'E' );
    vertex* F = CreateVertex( 'F' );
    vertex* G = CreateVertex( 'G' );
    vertex* H = CreateVertex( 'H' );
    
    //  그래프에 정점을 추가 
    AddVertex( graph, A );
    AddVertex( graph, B );
    AddVertex( graph, C );
    AddVertex( graph, D );
    AddVertex( graph, E );
    AddVertex( graph, F );
    AddVertex( graph, G );
    AddVertex( graph, H );

    //  정점과 정점을 간선으로 잇기 
    AddEdge( A, CreateEdge( A, C, 0 ) );
    AddEdge( A, CreateEdge( A, D, 0 ) );

    AddEdge( B, CreateEdge( B, C, 0 ) );
    AddEdge( B, CreateEdge( B, E, 0 ) );

    AddEdge( C, CreateEdge( C, F, 0 ) );
    
    AddEdge( D, CreateEdge( D, F, 0 ) );
    AddEdge( D, CreateEdge( D, G, 0 ) );

    AddEdge( E, CreateEdge( E, G, 0 ) );

    AddEdge( F, CreateEdge( F, H, 0 ) );
    
    AddEdge( G, CreateEdge( G, H, 0 ) );

    PrintGraph(graph);
    printf("\n");
    printf("A정점부터의 깊이 우선 탐색 : ");
    DFS(A);
    printf("\n");
    Visit_Reset(graph);
    printf("B정점부터의 깊이 우선 탐색 : ");
    DFS(B);

    return 0;
}