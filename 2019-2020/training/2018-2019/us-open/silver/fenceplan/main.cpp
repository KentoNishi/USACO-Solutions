// fenceplan - Silver - US-Open 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=944

/*
    Summary:
        Previously completed - check official problem
    Solution:
        Previously completed - check official solution
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node{
    vector<int> edges;
    bool visited;
    int x;
    int y;
};

vector<Node> graph;
int minx;
int miny;
int maxx;
int maxy;

void searchGraph(int nodeID){
    if(graph[nodeID].visited){
        return;
    }
    graph[nodeID].visited=true;
    minx=min(graph[nodeID].x,minx);
    maxx=max(graph[nodeID].x,maxx);
    miny=min(graph[nodeID].y,miny);
    maxy=max(graph[nodeID].y,maxy);
    for(int i=0;i<graph[nodeID].edges.size();i++){
        searchGraph(graph[nodeID].edges[i]);
    }
}

int main() {
    ofstream fout("fenceplan.out");
    ifstream fin("fenceplan.in");
    int N,M;
    fin >> N >> M;
    for(int i=0;i<N;i++){
        Node node=Node();
        fin >> node.x >> node.y;
        graph.push_back(node);
    }
    for(int i=0;i<M;i++){
        int a,b;
        fin >> a >> b;
        graph[a-1].edges.push_back(b-1);
        graph[b-1].edges.push_back(a-1);
    }
    int ans=-1;
    for(int i=0;i<N;i++){
        if(!graph[i].visited){
            minx=graph[i].x;
            maxx=graph[i].x;
            miny=graph[i].y;
            maxy=graph[i].y;
            searchGraph(i);
            if(ans==-1){
                ans=2*(maxx-minx) + 2*(maxy-miny);
            }else{
                ans=min(ans,2*(maxx-minx) + 2*(maxy-miny));
            }
        }
    }
    fout << ans << endl;
    return 0;
}