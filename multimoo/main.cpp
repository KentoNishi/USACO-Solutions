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
    Cell(int i){
        id=i;
    }
};

struct Region{
    int size=0;
    map<int,int> adjacent;
};

vector<vector<Cell>> grid;
vector<Region> regions;
void flood(int x, int y, int id){
    if(x>=grid.size()||y>=grid.size()||x<0||y<0){
        return;
    }
    if(grid[y][x].id!=id){
        regions[regions.size()-1].adjacent[grid[y][x].id]++;
        return;
    }
    if(grid[y][x].seen){
        return;
    }
    grid[y][x].seen=true;
    regions[regions.size()-1].size++;
    flood(x,y+1,id);
    flood(x+1,y,id);
    flood(x-1,y,id);
    flood(x,y-1,id);
    return;
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
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            if(grid[y][x].seen==false){
                regions.push_back(Region());
                flood(x,y,grid[y][x].id);
            }
        }
    }
    for(int i=0;i<regions.size();i++){
        cout << "Region with size "<<regions[i].size<<" is adjacent to: ";
        for(auto val : regions[i].adjacent ){
            int& value = val.second;
            int key = val.first;
            cout << key<<" ["<<value<<"]"<<"   ";
        }
        cout << endl;
    }
    return 0;
}