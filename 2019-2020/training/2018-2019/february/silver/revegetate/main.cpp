// revegetate - Silver - February 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=920

/*
    Summary:
    Given a list of pastures and edges connecting them, find the possible
    number of configurations possible. Each pasture can be of type 1 or 2,
    and each edge can dictate if 2 pastures are the same or different types.
    Solution:
        Build a graph.
        For each node:
            If not visited:
                Add 1 to answer
                Visit Node
        Visit node:
            For all edges:
                Recursively assign pasture IDs
        If configuration is possible:
            Output 2^answer in binary
        Else:
            Output 0
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Edge;
struct Pasture;
vector<Pasture> pastures;
int answer=0;
bool possible=true;

struct Edge{
    string type;
    int index;
    Edge(int i, string t){
        index=i;
        type=t;
    }
};

struct Pasture{
    vector<Edge> edges;
    bool visited=false;
    int value;
    Pasture(){
    }
};

void visit(int pastureID, int grassID){
    if(pastures[pastureID].visited){
        if(pastures[pastureID].value!=grassID){
            possible=false;
        }
        return;
    }
    pastures[pastureID].visited=true;
    pastures[pastureID].value=grassID;
    for(int i=0;i<pastures[pastureID].edges.size();i++){
        if(pastures[pastureID].edges[i].type=="S"){
            visit(pastures[pastureID].edges[i].index,grassID);
        }else{
            visit(pastures[pastureID].edges[i].index,3-grassID);
        }
    }
    return;
}

int main() {
    ofstream fout("revegetate.out");
    ifstream fin("revegetate.in");
    int N,M;
    fin >> N >> M;
    pastures=vector<Pasture>(N);
    for(int i=0;i<M;i++){
        string type;
        int a,b;
        fin >> type >> a >> b;
        pastures[a-1].edges.push_back(Edge(b-1,type));
        pastures[b-1].edges.push_back(Edge(a-1,type));
    }
    for(int i=0;i<N;i++){
        if(pastures[i].visited==false){
            answer++;
            visit(i,1);
        }
    }
    if(!possible){
        fout << 0;
    }else{
        fout << 1;
        for(int i=0;i<answer;i++){
            fout << 0;
        }
    }
    return 0;
}