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
#include <stack> 
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
};

int main() {
    ofstream fout ("mootube.out");
    ifstream fin ("mootube.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    map<int,Node> graph;
    for(int i=1;i<stoi(firstLine[0]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int a=stoi(splitln[0]);
        int b=stoi(splitln[1]);
        int w=stoi(splitln[2]);
        graph[a].edges.push_back(Edge(b,w));
        graph[b].edges.push_back(Edge(a,w));
    }
    for(int i=stoi(firstLine[0]);i<inputstrings.size();i++){
        int ans=0;
        vector<string> splitln=split(inputstrings[i]," ");
        int v=stoi(splitln[1]);
        int k=stoi(splitln[0]);
        unordered_map<int,bool> seen;
        stack<int> stack;
        stack.push(v);
        seen[v]=true;
        while(!stack.empty()){
            int id=stack.top();
            stack.pop();
            for(int i=0;i<graph[id].edges.size();i++){
                Edge out=graph[id].edges[i];
                if(seen[out.id]!=true&&out.weight>=k){
                    seen[out.id]=true;
                    stack.push(out.id);
                    ans++;
                }
            }
        }
        fout << ans << endl;
    }
    return 0;
}