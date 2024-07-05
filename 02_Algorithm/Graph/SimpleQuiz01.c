/*
간단한 방향성 그래프를 인접 리스트로 표현해보기
*/


#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct __Vertex {
    Element data;

    struct __Vertex* adjVertex;

}Vertex;

typedef struct __graph {
    Vertex* myVertex;

    int vertexSize;
    int usedsize;
}graph;

graph* Init_Graph(int vertexSize) {
    graph* myGraph = (graph*)malloc(sizeof(graph));
    myGraph->vertexSize = vertexSize;
    myGraph->usedsize = 0;
    myGraph->myVertex = (Vertex*)malloc(sizeof(Vertex) * vertexSize);

    return myGraph;
}

void Add_Vertex(graph* myGraph, Element newData) {
    myGraph->myVertex[myGraph->usedsize].data = newData;
    myGraph->myVertex[myGraph->usedsize].adjVertex = NULL;
    myGraph->usedsize += 1;
}

void Add_Edge(graph* myGraph, Element vertexData, Element adjData) {
    Vertex* newAdjVertex = (Vertex*)malloc(sizeof(Vertex));
    newAdjVertex->data = adjData;

    for(int i=0; i<myGraph->usedsize; i++) {
        if(vertexData == myGraph->myVertex[i].data) {
            newAdjVertex->adjVertex = myGraph->myVertex[i].adjVertex;
            myGraph->myVertex[i].adjVertex = newAdjVertex;
        }
    }
}

void Show(graph* myGraph) {
    Vertex* cur;
    for(int i = 0; i < myGraph->usedsize; i++) {
        printf("Vertex : %d - Adj : ",myGraph->myVertex[i].data);
        cur = myGraph->myVertex[i].adjVertex;
        while(cur != NULL) {
            printf("%d ", cur->data);
            cur = cur->adjVertex;
        } 
        printf("\n");
    }
}

void Destroy_Graph(graph* G) {
    free(G->myVertex);
    free(G);
}

int main(void) {

    graph* myGraph = Init_Graph(5);

    Add_Vertex(myGraph, 1);
    Add_Vertex(myGraph, 2);
    Add_Vertex(myGraph, 3);
    Add_Vertex(myGraph, 4);
    Add_Vertex(myGraph, 5);

    Add_Edge(myGraph, 1, 2);
    Add_Edge(myGraph, 1, 3);
    Add_Edge(myGraph, 1, 4);
    Add_Edge(myGraph, 1, 5);
    Add_Edge(myGraph, 2, 3);
    Add_Edge(myGraph, 2, 5);
    Add_Edge(myGraph, 4, 5);

    Show(myGraph);

    Destroy_Graph(myGraph);

    return 0;
}


