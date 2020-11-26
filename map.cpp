#include <stdio.h>

// 图的邻接矩阵存储结构

typedef char VertexType;
typedef int EdgeType;

#define MAXVEX 100
#define INFINITY 65535

// 构造了一个图
typedef struct  
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
}MGraph;


void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("输入顶点数和边数: \n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges);
    for (i = 0; i < G->numVertexes; i++) {
        scanf(&G->vexs[i]);
    }
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            G->arc[i][j] = INFINITY;
        }
    }
    for (k = 0; k < G->numEdges; k++) {
        printf("输入边(vi, vj) 上的下标i, 下表j, 和权w:\n");
        scanf("%d, %d, %d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];
    }
}

// 图的邻接链表表示法

typedef char VertexType;
typedef int EdgeType;

typedef struct EdgeNode {
    int adjvex;
    EdgeType weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
    VertexType data;
    EdgeNode *firstEdge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
} GraphAdjList;


