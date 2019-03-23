/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: countcross
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=716

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
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

struct Coord{
    int x;
    int y;
    Coord(int a, int b){
        x=a;
        y=b;
    }
    Coord(){

    }
};

struct comp {
    bool operator()(Coord a, Coord b) const { 
        if(a.x==b.x){
            return a.y<b.y;
        }else{
            return a.x<b.x;
        }
    }
};

vector<vector<set<Coord,comp>>> badFields;
vector<pair<int,int>> actions={{-1,0},{1,0},{0,-1},{0,1}};
void dfs(vector<vector<bool>>& reachable, int x, int y){
    if(x < 0 || x >= reachable.size() || y < 0 || y >= reachable[x].size() || reachable[x][y]) {
        return;
    }
    reachable[x][y]=true;
    for(int k=0;k<actions.size();k++){
        int nx=x+actions[k].first;
        int ny=y+actions[k].second;
        if(badFields[x][y].find(Coord(nx,ny))==badFields[x][y].end()){
            dfs(reachable,nx,ny);
        }
    }
}

int main() {
    ofstream fout ("countcross.out");
    ifstream fin ("countcross.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int n=stoi(firstLine[0]);
    int k=stoi(firstLine[1]);
    int r=stoi(firstLine[2]);
    for(int x=0;x<n;x++){
        badFields.push_back({});
        for(int y=0;y<n;y++){
            badFields[x].push_back(set<Coord,comp>());
        }
    }
    for(int i=1;i<=r;i++){
        vector<string> line=split(inputstrings[i]," ");
        int x1=stoi(line[0])-1;
        int y1=stoi(line[1])-1;
        int x2=stoi(line[2])-1;
        int y2=stoi(line[3])-1;
        badFields[x1][y1].insert(Coord(x2,y2));
        badFields[x2][y2].insert(Coord(x1,y1));
    }
    vector<Coord> points;
    int ans=0;
    for(int a=r+1;a<inputstrings.size();a++){
        int i=a-(r+1);
        vector<string> line=split(inputstrings[a]," ");
        int x=stoi(line[0])-1;
        int y=stoi(line[1])-1;
        points.push_back(Coord(x,y));
        vector<vector<bool>> reachable;
        for(int k=0;k<n;k++){
            reachable.push_back({});
            for(int j=0;j<n;j++){
                reachable[k].push_back(false);
            }
        }
        dfs(reachable,x,y);
        for(int j=0;j<i;j++){
            if(!reachable[points[j].x][points[j].y]){
                ans++;
            }
        }
    }
    fout << ans << endl;
}