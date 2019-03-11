/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: mootube
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <map>
#include <queue> 
#include <unordered_map>
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

struct Edge{
    int id;
    int weight;
    Edge(int i,int w){
        id=i;
        weight=w;
    }
};

struct Node{
    vector<Edge> edges;
    bool seen=false;
};

int dfs(int v, int k,unordered_map<int,Node> graph){
    int ans=0;
    queue<int> queue;
    queue.push(v);
    graph[v].seen=true;
    while(!queue.empty()){
        int id=queue.front();
        queue.pop();
        for(int i=0;i<graph[id].edges.size();i++){
            Edge out=graph[id].edges[i];
            if(graph[out.id].seen!=true&&out.weight>=k){
                graph[out.id].seen=true;
                queue.push(out.id);
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ofstream fout ("mootube.out");
    ifstream fin ("mootube.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    unordered_map<int,Node> graph;
    vector<string> firstLine=split(inputstrings[0]," ");
    for(int i=1;i<stoi(firstLine[0]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int a=stoi(splitln[0]);
        int b=stoi(splitln[1]);
        int w=stoi(splitln[2]);
        graph[a].edges.push_back(Edge(b,w));
        graph[b].edges.push_back(Edge(a,w));
    }
    for(int i=stoi(firstLine[0]);i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int v=stoi(splitln[1]);
        int k=stoi(splitln[0]);
        fout << dfs(v,k,graph) << endl;
    }
    return 0;
}