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
    vector<Coord> adjacent;
    Cell(int i){
        id=i;
    }
};

vector<vector<Cell>> grid;
void addCell(Coord a, Coord b){
    grid[a.y][a.x].adjacent.push_back(b);
    grid[b.y][b.x].adjacent.push_back(a);
}

int regid=0;
int visit(Cell cell){
    if(cell.seen!=false){
        return 0;
    }
    cell.seen=true;
    int ans=cell.adjacent.size();
    for(int i=0;i<cell.adjacent.size();i++){
        ans+=visit(cell.adjacent[i]);
    }
}

int largest(Cell cell){
    int ans=0;
    for(int i=0;i<cell.adjacent.size();i++){
        ans=max(ans,visit(cell));
        regid++;
    }
    return ans;
}

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
    for(int y=0;y<grid.size()-1;y++){
        for(int x=0;x<grid[y].size()-1;x++){
            if(grid[y][x].id==grid[y][x+1].id){
                grid[y][x+1].adjacent.push_back(Coord(x,y));
                grid[y][x].adjacent.push_back(Coord(x+1,y));
            }
            if(grid[y][x].id==grid[y+1][x].id){
                grid[y][x].adjacent.push_back(Coord(x,y+1));
                grid[y+1][x].adjacent.push_back(Coord(x,y));
            }
        }
    }
    int ans1=0;
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            ans1=max(ans1,largest(grid[y][x]));
            /*cout << grid[y][x].adjacent.size() <<" ";*/
        }
        cout << endl;
    }
    return 0;
}