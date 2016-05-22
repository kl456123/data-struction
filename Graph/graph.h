#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED





#define INF 0x3f3f3f3f
#define MAX_VERTEX_NUM 20
#define InfoType char
#include "common.h"
 #define SIZE 300

//template <typename T>
class Graph{
private:
    int vexnum;
    int arcnum;
public:
    void init();
    void print();
    explicit Graph();

};

namespace MGraphs {
template<typename VRType>
class ArcCell {
public:
    VRType adj;//relative between two vertexes
    InfoType *info;
};

//graph by matrix
template <typename VertexType,typename VRType>
class MGraph {
private:
    int vexnum;
    int arcnum;
    VertexType vexs[MAX_VERTEX_NUM];
    ArcCell <VRType> arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int topological[SIZE];
    bool haveLoop;
public:
    void init();
    void print();
    explicit MGraph(const int num);
    void minSpanTree(int u);
    void TopologicalSort();
    void CriticalPath();
};

}

namespace ALGraphs {

class ArcNode{
public:
    int adjvex;//instead of VRType , so just one typename
    ArcNode *nextarc;
    InfoType *info;
};

template<typename T>
class VNode{
public:
    T data;
    ArcNode *firstarc;
};

template <typename T>
class ALGraph{
private:
    VNode<T> *vertices;
    int vernum;
    int arcnum;
    void _fillVNode(VNode<T> vertex);
    void _printVNode(VNode<T> vertex);
public:
    explicit ALGraph(const int num);
    void init();
    void print();
    void DFS(T vertex,T visited[]);
    void printDFS(T vertex);
};

}

#endif // GRAPH_HPP_INCLUDED
