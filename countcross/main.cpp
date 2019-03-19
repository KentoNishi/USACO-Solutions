/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: countcross
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
};

struct Field{
    vector<Coord> walls;
};

vector<vector<bool>> floodFill(Coord start){
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
    vector<vector<Field>> grid;
    for(int i=0;i<stoi(firstLine[0]);i++){
        grid.push_back({});
        for(int k=0;k<stoi(firstLine[0]);k++){
            grid[i].push_back(Field());
        }
    }
    for(int i=1;i<=stoi(firstLine[1]);i++){
        vector<string> line=split(inputstrings[i]," ");
        vector<int> ln;
        for(int k=0;k<line.size();k++){
            ln.push_back(stoi(line[k])-1);
        }
        grid[ln[0]][ln[1]].walls.push_back(Coord(ln[2],ln[3]));
        grid[ln[2]][ln[3]].walls.push_back(Coord(ln[0],ln[1]));
    }
    vector<Coord> cows;
    for(int i=stoi(firstLine[1])+1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ",grid);
        vector<int> ln;
        for(int k=0;k<line.size();k++){
            ln.push_back(stoi(line[k])-1);
        }
        cows.push_back(Coord(ln[0],ln[1]));
    }
    int ans=0;
    for(int i=0;i<cows.size();i++){
        vector<vector<bool>> canReach=floodFill(cows[i]);
        for(int k=0;k<i;k++){
            if(!canReach[cows[k].x][cows[k].y]){
                ans++;
            }
        }
    }
    return 0;
}