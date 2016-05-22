#include <iostream>
#include <stdio.h>
#include "graph.h"

using namespace std;
using namespace MGraphs;
using namespace ALGraphs;
int main() {
    freopen("in.txt","r",stdin);
//    MGraph<int,int> G(4);
//
//    G.init();
//    G.print();
//ALGraph<int>G(4);
//G.init();
////G.print();
//G.printDFS(0);
MGraph<int,int>G(9);
G.init();
G.print();
//G.minSpanTree(0);
G.TopologicalSort();
G.CriticalPath();
    return 0;
}
