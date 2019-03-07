/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: multimoo
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <set>
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
};

struct Cell{
    int id;
    bool seen=false;
    vector<Coord> edges;
    Cell(int i){
        id=i;
    }
};

vector<vector<Cell>> grid;
int main() {
    ofstream fout ("multimoo.out");
    ifstream fin ("multimoo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    inputstrings.erase(inputstrings.begin());
    for(int y=0;y<inputstrings.size();y++){
        vector<string> splitln=split(inputstrings[y]," ");
        grid.push_back({});
        for(int x=0;x<splitln.size();x++){
            grid[y].push_back(Cell(stoi(splitln[x])));
        }
    }
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            if(x+1<grid.size()&&grid[y][x].id==grid[y][x+1].id){
                grid[y][x].edges.push_back(Coord(x+1,y));
                grid[y][x+1].edges.push_back(Coord(x,y));
            }
            if(y+1<grid.size()&&grid[y][x].id==grid[y+1][x].id){
                grid[y][x].edges.push_back(Coord(x,y+1));
                grid[y+1][x].edges.push_back(Coord(x,y));
            }
        }
    }
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            if(grid[y][x].seen==false){
                flood(x,y,grid[y][x].id);
            }
            cout << grid[y][x].edges.size() << " ";
        }
        cout << endl;
    }
    return 0;
}