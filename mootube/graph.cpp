#include <chrono>
#include <array>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
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

class Vertex{
    public:
        int id;
        bool wasVisited=false;
        Vertex(int video){
            id=video;
        }
};

struct Stack{
    vector<int> stack;
    int peek(){
        return stack[stack.size()-1];
    }
    int push(int x){
        stack.push_back(x);
    }
    int pop(){
        int last=stack[stack.size()-1];
        stack.erase(stack.begin()+stack.size()-1);
        return last;
    }
    int size(){
        return stack.size();
    }
};

class Graph{
    private:
        static const int MAX_VERTS=5000;
        vector<Vertex> vertexList;
        vector<vector<int>> adjMat;
        int nVerts=0;
    public:
        Graph(){
            for(int j=0;j<MAX_VERTS; j++){
                adjMat.push_back({});
                for(int k=0;k<MAX_VERTS;k++){
                    adjMat[j].push_back(0);
                }
            }
        }
        void addVertex(int id){
            vertexList.push_back(Vertex(id));
            nVerts++;
        }
        void addEdge(int start, int end,int weight){
            adjMat[start][end]=weight;
            adjMat[end][start]=weight;
        }
        void displayVertex(int V){
//            cout <<V<<" "<< vertexList[V].id << endl;
        }
        int getAdjUnvisitedVertex(int v,int k){
            for(int j=0;j<nVerts;j++){
                if(adjMat[v][j]>=k&&vertexList[j].wasVisited==false){
//                    cout << vertexList[j].id << endl;
                    return j;
                }
            }
            return -1;
        }
        int dfs(int start,int k){
            int ans=0;
            if(vertexList.size()!=0){
                vertexList[start].wasVisited=true;
                Stack stack=Stack();
                stack.push(start);
                while(stack.size()!=0){
                    int v=getAdjUnvisitedVertex(stack.peek(),k);
                    if(v==-1){
                        stack.pop();
                    }else{
                        ans++;
//                        cout << start << " connected to " << v << endl;
                        vertexList[v].wasVisited=true;
                        displayVertex(v);
                        stack.push(v);
                    }
                }
                for(int j=0;j<nVerts;j++){
                    vertexList[j].wasVisited=false;
                }
            }
            return ans;
        }
};

int main(){
    Graph graph=Graph();
    ofstream fout ("mootube.out");
    ifstream fin ("mootube.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    for(int i=0;i<=stoi(firstLine[0]);i++){
        graph.addVertex(i);
 //       cout << i << endl;
    }
    for(int i=1;i<stoi(firstLine[0]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int a=stoi(splitln[0])-1;
        int b=stoi(splitln[1])-1;
        int w=stoi(splitln[2]);
        graph.addEdge(a,b,w);
    }
    for(int i=stoi(firstLine[0]);i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int v=stoi(splitln[1])-1;
        int k=stoi(splitln[0]);
        
        fout << graph.dfs(v,k)<<endl;
    }
    return 0;
}
