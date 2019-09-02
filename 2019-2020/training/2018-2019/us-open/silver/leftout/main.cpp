// leftout - Silver - US-Open 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=942

/*
    Summary:

    Solution:

*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Cell{
    int value;
    Cell(int v){
        value=v;
    }
    Cell(){
        
    }
};

vector<vector<Cell>> grid;
int N;

void flip(string type, int line){
    if(type=="y"){
        for(int x=0;x<N;x++){
            grid[line][x].value=1-grid[line][x].value;
        }
    }else if(type=="x"){
        for(int y=0;y<N;y++){
            grid[y][line].value=1-grid[y][line].value;
        }
    }
}

int main() {
    ofstream fout("leftout.out");
    ifstream fin("leftout.in");
    /*
        N: dimension of grid (NxN)
    */
    fin >> N;
    grid=vector<vector<Cell>>(N,vector<Cell>(N));
    for(int i=0;i<N;i++){
        string line;
        fin >> line;
        for(int k=0;k<line.length();k++){
            grid[i][k]=Cell((string(1,line[k])=="R"?1:0));
        }
    }
    for(int y=0;y<N;y++){
        if(grid[y][N-1].value==0){
            flip("y",y);
        }
    }
    for(int x=0;x<N;x++){
        if(grid[N-1][x].value==0){
            flip("x",x);
        }
    }
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            if(grid[y][x].value==0){
                fout << y+1 << " " << x+1 << endl;
                return 0;
            }
//            cout << grid[y][x].value << " ";
        }
//        cout << endl;
    }
    fout << -1 << endl;
    return 0;
}