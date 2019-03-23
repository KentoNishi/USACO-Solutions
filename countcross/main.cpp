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

struct comp {
    bool operator()(int a, int b) const { 
        return a<b;
    }
};

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

vector<vector<vector<Coord>>> walls;
void dfs(vector<vector<bool>>& reachable,int x, int y){
    if(x<0||x>=(reachable).size()||y<0||y>=(reachable)[x].size()||(reachable)[x][y]){
        return;
    }
    (reachable)[x][y]=true;
    vector<pair<int,int>> directions={{-1,0},{0,1},{1,0},{0,-1}};
    for(int i=0;i<directions.size();i++){
        int nx=x+directions[i].first;
        int ny=y+directions[i].second;
        Coord toFind=Coord(nx,ny);
        if(find_if(walls[x][y].begin(),walls[x][y].end(),[toFind](Coord const& n ){
            return (n.x==toFind.x&&n.y==toFind.y);
        })==walls[x][y].end()){
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
    for(int x=0;x<stoi(firstLine[0]);x++){
        walls.push_back({});
        for(int y=0;y<stoi(firstLine[0]);y++){
            walls[x].push_back({});
        }
    }
    for(int i=1;i<=stoi(firstLine[1]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        vector<int> coords;
        for(int k=0;k<splitln.size();k++){
            coords.push_back(stoi(splitln[k])-1);
        }
        walls[coords[0]][coords[1]].push_back(Coord(coords[2],coords[3]));
        walls[coords[2]][coords[3]].push_back(Coord(coords[0],coords[1]));
    }
    vector<Coord> cows;
    int ans=0;
    vector<Coord> coords;
    for(int i=stoi(firstLine[1])+1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        coords.push_back(Coord(stoi(line[0])-1,stoi(line[1])-1));
    }
    for(int i=0;i<coords.size();i++){
        cows.push_back(coords[i]);
        vector<vector<bool>> reachable;
        for(int px=0;px<(stoi(firstLine[0]));px++){
            reachable.push_back({});
            for(int py=0;py<(stoi(firstLine[0]));py++){
                reachable[px].push_back(false);
            }
        }
        dfs(reachable,coords[i].x,coords[i].y);
        for(int j=0;j<i;j++){
            if(reachable[cows[j].x][cows[j].y]!=true){
                ans++;
            }
        }
    }
    fout << ans << endl;
    return 0;
}