//http://usaco.org/index.php?page=viewproblem2&cpid=570
/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: lightson
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

struct Coord{
    int x;
    int y;
    Coord(int a, int b){
        x=a;
        y=b;
    }
};

struct Room{
    vector<Coord> switches;
    bool lit=false;
    bool visited=false;
};
vector<vector<Room>> farm;
vector<int> dx = {-1,1,0,0};
vector<int> dy = {0,0,-1,1};

bool isVisited(int x, int y){
    return x>=0&&x<farm.size()&&y>=0&&y<farm.size()&&farm[x][y].visited;
}

bool isOn(int x, int y){
    return x>=0&&x<farm.size()&&y>=0&&y<farm.size()&&farm[x][y].lit;
}

bool hasNeighbor(int x, int y){
    for(int k=0;k<dx.size();k++){
        if(isOn(x+dx[k],y+dy[k])&&isVisited(x+dx[k],y+dy[k])){
            return true;
        }
    }
    return false;
}

void flood(int x, int y){
    if(isVisited(x,y)){
        return;
    }
    farm[x][y].visited=true;
    for(auto &next: farm[x][y].switches){
        if(!farm[next.x][next.y].lit){
            farm[next.x][next.y].lit=true;
            if(hasNeighbor(next.x,next.y)){
                flood(next.x,next.y);
            }
        }
    }
    for(int k = 0; k < dx.size(); k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if(isOn(nx, ny)) {
            flood(nx, ny);
        }
    }
}

int main() {
    ofstream fout ("lightson.out");
    ifstream fin ("lightson.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int N=stoi(firstLine[0]);
    for(int x=0;x<N;x++){
        farm.push_back({});
        for(int y=0;y<N;y++){
            farm[x].push_back(Room());
        }
    }
    for(int i=1;i<inputstrings.size();i++){
        vector<string> coords=split(inputstrings[i]," ");
        int a=stoi(coords[0])-1;
        int b=stoi(coords[1])-1;
        int c=stoi(coords[2])-1;
        int d=stoi(coords[3])-1;
        farm[a][b].switches.push_back(Coord(c,d));
    }
    farm[0][0].lit=true;
    flood(0,0);
    int ans=0;
    for(int x=0;x<farm.size();x++){
        for(int y=0;y<farm[x].size();y++){
            if(farm[x][y].lit){
                ans++;
            }
            cout << farm[y][x].lit << " ";
        }
        cout << endl;
    }
    fout << ans << endl;
    return 0;
}