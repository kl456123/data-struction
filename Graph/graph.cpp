#include <iostream>
#include "graph.h"
#include <stack>

using namespace std;

namespace MGraphs {
template <typename VertexType,typename VRType>
MGraph<VertexType,VRType>::MGraph(const int num) {
    vexnum = num;
}

template <typename VertexType,typename VRType>
void MGraph<VertexType,VRType>::init() {
    for(int i=0; i<vexnum; i++) {
        for(int j=0; j<vexnum; j++) {
            cin>>arcs[i][j].adj;
        }
    }
}

template <typename VertexType,typename VRType>
void MGraph<VertexType,VRType>::print() {
    for(int i=0; i<vexnum; i++) {
        for(int j=0; j<vexnum; j++) {
            cout<<arcs[i][j].adj<<' ';
        }
        cout<<endl;
    }
}


template <typename VertexType,typename VRType>
void MGraph<VertexType,VRType>::minSpanTree(int u) {
    //initial prepare for training
    /*
    @brief:
    closedge[] save for closest distance between vertexes in Tree and  in Graph remained.
    when add one vertex into Tree ,update it for a while.
    */
    Closedge<VertexType,VRType> closedge[SIZE];
    for(int j=0; j<vexnum; j++) {
        closedge[j].lowcost=arcs[u][j].adj; //no for DAG!!
        closedge[j].adjvex=u;
    }
    closedge[u].lowcost=0;
    int k;
    //find the next vertex
    for(int i=1; i<vexnum; i++) {
//            if(closedge[i].lowcost==0)
//                continue;
//get min value in closedge[]
        VRType _min=INF;

        for(int j=0; j<vexnum; j++) {
            if(closedge[j].lowcost==0)
                continue;
            if(_min>closedge[j].lowcost) {
                _min = closedge[j].lowcost;
                k = j;
                u=closedge[j].adjvex;
            }
        }
        closedge[u].adjvex = k;
        cout<<"("<<u<<","<<k<<")"<<endl;
        closedge[k].lowcost=0;
        //update closedge[]
        for(int j=0; j<vexnum; j++) {
            if(closedge[j].lowcost>arcs[j][k].adj&&arcs[j][k].adj!=0) {
                closedge[j].lowcost = arcs[j][k].adj;
                closedge[j].adjvex = k;
            }
        }
    }

}

template <typename VertexType,typename VRType>
void MGraph<VertexType, VRType>::TopologicalSort() {

//    class _Vertex{
//    public:
//        int indegree;
//        VertexType vex;
//    };
//initial indegree[]
    int indegree[SIZE];
    for(int i=0; i<vexnum; i++) {
        indegree[i]=0;
    }
    stack<VertexType> s;
    for(int i=0; i<vexnum; i++) {
        for(int j=0; j<vexnum; j++) {
            if(arcs[j][i].adj!=0) {
                indegree[i]++;
            }
        }
        if(indegree[i]==0) {
            s.push(i);
        }
    }
    //test         result:pass!!!
//    for(int i=0;i<vexnum;i++){
//        cout<<indegree[i]<<' ';
//    }
//    cout<<endl;
    int out=0;

    cout<<"TopologicalSort result:"<<endl;
    while(!s.empty()) {
        VertexType now = s.top();
        indegree[now]=-1;//prevent pushing it into stack again
        s.pop();
        topological[out]=now;
        cout<<now<<' ';
        out++;
        //update indegree[]
        for(int i=0; i<vexnum; i++) {
            if(arcs[now][i].adj!=0&&indegree[i]!=0) {
                indegree[i]--;
                if(indegree[i]==0) {
                    s.push(i);
                }
            }

        }
//        for(int i=0; i<vexnum; i++) {
//            cout<<indegree[i]<<' ';
//        }

//        cout<<"stack size:"<<s.size()<<' ';
//        cout<<s.top()<<' ';

        cout<<endl;
    }
    cout<<endl;
    if(out!=vexnum) {
        cout<<"have loop in AOV"<<endl;
        haveLoop = true;
    } else {
        cout<<"have no loop in AOV"<<endl;
        haveLoop = false;
    }

}

template <typename VertexType,typename VRType>
void MGraph<VertexType,VRType>::CriticalPath() {
    if(haveLoop) {
        cout<<"have no critical path!"<<endl;
        return;
    }
    //define two array that saving the early start time and the late start time!
    int ve[SIZE];
    int vl[SIZE];
//    for(int i=0;i<vexnum;i++){
//        vl[i]=0;
//        ve[i]=0;
//    }
//    ve[topological[0]]=0;
    //forward
    for(int i=0; i<vexnum; i++) {
        int now = topological[i];
                    ve[now]=0;
        for(int j=0; j<i; j++) {
            // "now" vertex is the tail in arc
            if(arcs[topological[j]][now].adj>0) {
                if(ve[now]<ve[topological[j]]+arcs[topological[j]][now].adj) {
                    ve[now]=ve[topological[j]]+arcs[topological[j]][now].adj;
                }
            }
        }
    }
//        for(int i=0; i<vexnum; i++) {
//        cout<<ve[i]<<' ';
//    }

    //backward
        for(int i=vexnum-1; i>=0; i--) {
        int now = topological[i];
                    vl[now]=ve[topological[vexnum-1]];
        for(int j=i+1; j<vexnum; j++) {
            // "now" vertex is the tail in arc
            if(arcs[now][topological[j]].adj>0) {
                if(vl[now]>vl[topological[j]]-arcs[now][topological[j]].adj) {
                    vl[now]=vl[topological[j]]-arcs[now][topological[j]].adj;
                }
            }
        }
    }
//        for(int i=0; i<vexnum; i++) {
//        cout<<vl[i]<<' ';
//    }
for(int i=0;i<vexnum;i++){
    for(int j=0;j<vexnum;j++){
            //find arcs by Traversing the Graph
        if(arcs[i][j].adj>0){
            if(arcs[i][j].adj==vl[j]-ve[i]){
                cout<<"("<<i<<","<<j<<")"<<' ';
            }
        }
    }
}
}


template class MGraph<int,int>;
template class MGraph<char,double>;
//template class MGraph<char*,double>;
}

namespace ALGraphs {
template <typename T>
void ALGraph<T>::_fillVNode(VNode<T> vertex) {
    ArcNode *headArc,*nextArc;
    headArc = vertex.firstarc;
    int nextAdjvex;
    while(cin>>nextAdjvex&&nextAdjvex!=-1) {
        nextArc = new ArcNode;
        nextArc->adjvex = nextAdjvex;
        nextArc->nextarc = NULL;
        headArc->nextarc = nextArc;
        headArc = nextArc;
    }
    if(headArc == vertex.firstarc) {
        vertex.firstarc->nextarc=NULL;
    }
}

template <typename T>
void ALGraph<T>::init() {
    for(int i=0; i<vernum; i++) {
        std::cin>>vertices[i].data;
        _fillVNode(vertices[i]);
    }
}

template <typename T>
void ALGraph<T>::_printVNode(VNode<T> vertex) {
    ArcNode *tempArc=vertex.firstarc->nextarc;//firstarc is the head point,so it has not adjvex term.
    while(tempArc) {
        std::cout<<tempArc->adjvex<<' ';
        tempArc = tempArc->nextarc;
    }
    std::cout<<endl;
}

template<typename T>
void ALGraph<T>::print() {
    for(int i=0; i<vernum; i++) {
        std::cout<<vertices[i].data<<' ';
        _printVNode(vertices[i]);
    }
}

template<typename T>
ALGraph<T>::ALGraph(int num) {
    vernum = num;
}
template <typename T>
void ALGraph<T>::DFS(T vertex,T visited[]) {
    if(visited[vertex]==1)
        return;
    visited[vertex]=1;
    std::cout<<vertices[vertex].data<<' ';
    ArcNode *tempArc=vertices[vertex].firstarc->nextarc;
    while(tempArc) {
        DFS(tempArc->adjvex,visited);
        tempArc = tempArc->nextarc;
    }

}



template<typename T>
void ALGraph<T>::printDFS(T vertex) {
    T visited[SIZE];
    //initial visited[]
    for(int i=0; i<vernum; i++) {
        visited[i] = 0;
    }
    DFS(vertex,visited);
    cout<<endl;
    for(int i=0; i<vernum; i++) {
        if(visited[i]==0) {
            DFS(i,visited);
            cout<<endl;
        }
    }

}
template class ALGraph<int>;
// template class ALGraph<char*>;
template class ALGraph<char>;
}


