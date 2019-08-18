// perimeter - Silver - January 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=895

/*
    Summary:
        Find the area and perimeter of the largest blob.
        If multiple are tied, find the blob with the smallest perimeter.
    Solution:
        Flood fill and find the area and perimeter.
        If largest area:
            If smallest perimeter:
                Save as answer
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Block {
    int perimeter=0;
    bool ice;
    bool visited=false;
};

struct Answer{
    int area=0;
    int perimeter=0;
    Answer(int a, int p){
        area=a;
        perimeter=p;
    }
    Answer(){

    }
};

vector<vector<Block>> grid;
int N;

Answer floodFill(int x, int y){
    if(grid[y][x].visited || !grid[y][x].ice){
        return Answer(0,0);
    }
    grid[y][x].visited=true;
    int totalPerimeter=grid[y][x].perimeter;
    int totalArea=1;
    if(x>0){
        Answer answer=floodFill(x-1,y);
        totalPerimeter+=answer.perimeter;
        totalArea+=answer.area;
    }
    if(y>0){
        Answer answer=floodFill(x,y-1);
        totalPerimeter+=answer.perimeter;
        totalArea+=answer.area;
    }
    if(x<N-1){
        Answer answer=floodFill(x+1,y);
        totalPerimeter+=answer.perimeter;
        totalArea+=answer.area;
    }
    if(y<N-1){
        Answer answer=floodFill(x,y+1);
        totalPerimeter+=answer.perimeter;
        totalArea+=answer.area;
    }
    return Answer(totalArea,totalPerimeter);
}

int main() {
    ofstream fout("perimeter.out");
    ifstream fin("perimeter.in");
    /*
        N: Dimension of grid (NxN)
    */
    fin >> N;
    grid = vector<vector<Block>>(N);
    for (int y = 0; y < N; y++) {
        grid[y] = vector<Block>(N);
        string line;
        fin >> line;
        for (int x = 0; x < N; x++) {
            grid[y][x].ice = (line[x] == '#');
            if(grid[y][x].ice){
                grid[y][x].perimeter=4;
            }
        }
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (grid[y][x].ice) {
                if (x > 0 && grid[y][x - 1].ice) {
                    grid[y][x - 1].perimeter--;
                }
                if (y > 0 && grid[y - 1][x].ice) {
                    grid[y - 1][x].perimeter--;
                }
                if (x < N  && - 1 && grid[y][x + 1].ice) {
                    grid[y][x + 1].perimeter--;
                }
                if (y < N - 1 && grid[y + 1][x].ice) {
                    grid[y + 1][x].perimeter--;
                }
            }
        }
    }
    Answer finalAnswer;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            Answer answer=floodFill(x,y);
//            cout << x << ", " << y << " = " << answer.area << endl;
            if(answer.area > finalAnswer.area){
                finalAnswer=answer;
            }else if(answer.area==finalAnswer.area){
                if(answer.perimeter<finalAnswer.perimeter){
                    finalAnswer=answer;
                }
            }
        }
    }    
    /*
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cout << grid[y][x].perimeter;
        }
        cout << endl;
    }
    */
    fout << finalAnswer.area << " " << finalAnswer.perimeter << endl;
    return 0;
}