// paintbarn - Silver - February 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=919

/*
    Summary:
        Given a list of 4 corners of rectangles, find the total area
        that has K overlapping rectangles.
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

int main() {
    ofstream fout("paintbarn.out");
    ifstream fin("paintbarn.in");
    int N,K;
    fin >> N >> K;
    /*
        N: number of rectangles
    */
    int grid[1001][1001]={0};
    for(int i=0;i<N;i++){
        int x1,y1,x2,y2;
        fin >> x1 >> y1 >> x2 >> y2;
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        grid[y1][x1]++; // top left
        grid[y2][x1]--; // bottom left
        grid[y1][x2]--; // top right
        grid[y2][x2]++; // bottom right
    }
    int ans=0;
    for(int y=0;y<1001;y++){
        for(int x=0;x<1001;x++){
            if(grid[y][x]==K){
                ans++;
            }
            if(x<1000){
                grid[y][x+1]+=grid[y][x];
            }
            if(y<1000){
                grid[y+1][x]+=grid[y][x];
            }
            if(x<1000 && y<1000){
                grid[y+1][x+1]-=grid[y][x];
            }
        }
    }
    fout << ans << endl;
    return 0;
}