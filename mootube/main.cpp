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
};

vector<vector<Edge>> edges;/*
int bfs(int v, int k,bool seen[stoi(firstLine[0])]){
    int ans=0;
    queue<int> queue;
    queue.push(v);
    seen[v]=true;
    while(!queue.empty()){
        int id=queue.front();
        queue.pop();
        for(int i=0;i<edges.size();i++){
            Edge out=edges[id][i];
            cout << out.id << " " << out.weight << " " << k << endl;
            if(seen[out.id]!=true&&out.weight>=k){
                seen[out.id]=true;
                queue.push(out.id);
                ans++;
            }
        }
    }
    return ans;
}*/

int main() {
    ofstream fout ("mootube.out");
    ifstream fin ("mootube.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
//    unordered_map<int,Node> seen;
    vector<string> firstLine=split(inputstrings[0]," ");
    edges=vector<vector<Edge>>(stoi(firstLine[0]));
    for(int i=0;i<stoi(firstLine[0]);i++){
        edges[i]={};
    }
    for(int i=1;i<stoi(firstLine[0]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int a=stoi(splitln[0])-1;
        int b=stoi(splitln[1])-1;
        int w=stoi(splitln[2]);
        edges[a].push_back(Edge(b,w));
        edges[b].push_back(Edge(a,w));
    }
    for(int i=stoi(firstLine[0]);i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int v=stoi(splitln[1])-1;
        int k=stoi(splitln[0]);
        bool seen[stoi(firstLine[0])]; 
        int ans=0;
        queue<int> queue;
        queue.push(v);
        seen[v]=true;
        while(!queue.empty()){
            int id=queue.front();
            queue.pop();
            for(int i=0;i<edges[id].size();i++){
                Edge out=edges[id][i];
//                cout << out.id << " " << out.weight << " " << k << endl;
                if(seen[out.id]!=true&&out.weight>=k){
                    seen[out.id]=true;
                    queue.push(out.id);
                    ans++;
                }
            }
        }
        fout << ans << endl;
    }
    return 0;
}