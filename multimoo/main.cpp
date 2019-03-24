//http://usaco.org/index.php?page=viewproblem2&cpid=836
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <set>
#include <array>
#include <map>
using namespace std;

vector<string> split(string str, string character){
    vector<string> result;
    long long s=0;
    long long i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            long long x=i-s;
            if(i==str.length()-1){
                x++;
            }
            result.push_back(str.substr(s,x));
            s=i+1;
        }
        i++;
    }
    return result;
}

struct Graph{
    map<int, set<int>> edges;
    map<int, int> nodeSize;
    map<int, int> regionID;
    map<int, int> regionSize;
};

vector<vector<int>> grid;

array<array<int,1001>,1001> cellID;
array<array<int,1001>,1001> cow;
int N=0;
int globalID=0;

map<int, Graph> graph1;
map<pair<int,int>,Graph> graph2;

void addEdge(Graph &graph, int node1,int node2){
    graph.edges[node1].insert(node2);
    graph.edges[node2].insert(node1);
    graph.nodeSize[node1]=1;
    graph.nodeSize[node2]=1;
}

int visit(Graph &graph, int nodeID, int regionID){
    if(graph.regionID.count(nodeID)>0){
        return 0;
    }
    graph.regionID[nodeID]=regionID;
    int ans=graph.nodeSize[nodeID];
    for(int id: graph.edges[nodeID]){
        ans+=visit(graph,id,regionID);
    }
    graph.regionSize[regionID]=ans;
    return ans;
}

int largest(Graph &graph){
    int ans=0;
    for(auto &edge: graph.edges){
        ans=max(ans,visit(graph,edge.first,++globalID));
    }
    return ans;
}

void addEdge2(int x1, int y1, int x2, int y2){
    int cow1=cow[y1][x1];
    int cow2=cow[y2][x2];
    int cell1=cellID[y1][x1];
    int cell2=cellID[y2][x2];
    if(cow1>cow2){
        swap(cow1,cow2);
        swap(cell1,cell2);
    }
    int region1=graph1[cow1].regionID[cell1];
    int region2=graph1[cow2].regionID[cell2];
    pair<int,int> keyPair=make_pair(cow1,cow2);
    addEdge(graph2[keyPair],region1,region2);
    graph2[keyPair].nodeSize[region1]=graph1[cow1].regionSize[region1];
    graph2[keyPair].nodeSize[region2]=graph1[cow2].regionSize[region2];
}

int main() {
    ofstream fout ("multimoo.out");
    ifstream fin ("multimoo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    N=stoi(inputstrings[0]);
    for(int y=1;y<=N;y++){
        vector<string> line=split(inputstrings[y]," ");
        for(int x=1;x<=N;x++){
            cow[y][x]=stoi(line[x-1]);
            cellID[y][x]=y*N+x;
        }
    }
    for(int y=1;y<=N;y++){
        for(int x=1;x<=N;x++){
            addEdge(graph1[cow[y][x]],cellID[y][x],cellID[y][x]);
            if(y<N&&cow[y+1][x]==cow[y][x]){
                addEdge(graph1[cow[y][x]],cellID[y][x],cellID[y+1][x]);
            }
            if(x<N&&cow[y][x+1]==cow[y][x]){
                addEdge(graph1[cow[y][x]],cellID[y][x],cellID[y][x+1]);
            }
        }
    }
    int ans1=0;
    for(auto &block: graph1){
        ans1=max(ans1,largest(block.second));
    }
    fout << ans1 << endl;
    for(int y=1;y<=N;y++){
        for(int x=1;x<=N;x++){
            if(y<N&&cow[y+1][x]!=cow[y][x]){
                addEdge2(x,y,x,y+1);
            }
            if(x<N&&cow[y][x+1]!=cow[y][x]){
                addEdge2(x,y,x+1,y);
            }
        }
    }
    int ans2=0;
    for(auto &block: graph2){
        ans2=max(ans2,largest(block.second));
    }
    fout << ans2 << endl;
    return 0;
}