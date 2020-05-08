//http://usaco.org/index.php?page=viewproblem2&cpid=788
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
    int d;
    int w;
    Edge(int a, int b){
        d=a;
        w=b;
    }
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
    int n=stoi(firstLine[0]);
    int q=stoi(firstLine[1]);
    vector<vector<Edge>> edges=vector<vector<Edge>>(n);
    for(int i=0;i<n;i++){
        edges[i]={};
    }
    for(int a=1;a<n;a++){
        vector<string> line=split(inputstrings[a]," ");
        int x=stoi(line[0])-1;
        int y=stoi(line[1])-1;
        int w=stoi(line[2]);
        edges[x].push_back(Edge(y,w));
        edges[y].push_back(Edge(x,w));
    }
    for(int query=0;query<q;query++){
        vector<string> line=split(inputstrings[n+query]," ");
        int threshhold=stoi(line[0]);
        int start=stoi(line[1])-1;
        int ret=0;
        queue<int> queue;
        queue.push(start);
        vector<bool> seen=vector<bool>(n);
        seen[start]=true;
        while(!queue.empty()){
            int curr=queue.front();
            queue.pop();
            for(Edge& out: edges[curr]){
                if(!seen[out.d]&&out.w>=threshhold){
                    seen[out.d]=true;
                    queue.push(out.d);
                    ret++;
                }
            }
        }
        fout << ret << endl;
    }
    return 0;
}