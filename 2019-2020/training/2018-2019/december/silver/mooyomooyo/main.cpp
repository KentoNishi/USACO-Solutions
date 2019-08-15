// mooyomooyo - Silver - December 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=860

/*
    Summary:
        Output the final configuration of a Puyo Puyo board.
    Solution:
        While board is incomplete:
            For each block:
                If not visited:
                    Floodfill
                    If chunk size is more than K:
                        Change all to 0
                        Apply gravity
        Floodfill:
            If same block type as origin:
                Mark Pixel as visited
                Add to the list of blocks in the chunk
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
using namespace std;

struct Pixel{
    int y;
    int x;
    int value;
    bool visited;
};

vector<vector<Pixel>> board;
int N,K;
/* 
    N: Number of columns
    K: Minimum number of Pixels in a region
*/

vector<Pixel> floodFillSearch(Pixel &pixel){
    pixel.visited=true;
    vector<Pixel> region={pixel};
    if(pixel.x>0 && 
    board[pixel.y][pixel.x-1].visited==false &&
    board[pixel.y][pixel.x-1].value==pixel.value){
        vector<Pixel> searched=floodFillSearch(board[pixel.y][pixel.x-1]);
        region.insert(region.end(),searched.begin(),searched.end());
    }
    if(pixel.y>0 && 
    board[pixel.y-1][pixel.x].visited==false &&
    board[pixel.y-1][pixel.x].value==pixel.value){
        vector<Pixel> searched=floodFillSearch(board[pixel.y-1][pixel.x]);
        region.insert(region.end(),searched.begin(),searched.end());
    }
    if(pixel.x<9 && 
    board[pixel.y][pixel.x+1].visited==false &&
    board[pixel.y][pixel.x+1].value==pixel.value){
        vector<Pixel> searched=floodFillSearch(board[pixel.y][pixel.x+1]);
        region.insert(region.end(),searched.begin(),searched.end());
    }
    if(pixel.y<N-1 && 
    board[pixel.y+1][pixel.x].visited==false &&
    board[pixel.y+1][pixel.x].value==pixel.value){
        vector<Pixel> searched=floodFillSearch(board[pixel.y+1][pixel.x]);
        region.insert(region.end(),searched.begin(),searched.end());
    }
    return region;
}

int main() {
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    fin >> N >> K;
    board=vector<vector<Pixel>>(N,vector<Pixel>(10));
    // board[y][x]=Pixel
    for(int y=0;y<N;y++){
        string line;
        fin >> line;
        for(int x=0;x<10;x++){
            board[y][x].x=x;
            board[y][x].y=y;
            board[y][x].value=stoi(string(1,line[x]));
        }
    }
    bool done=false;
    while(!done){
        // if the task is done, then it won't loop again
        done=true;
        // reset all pixels
        for(int y=0;y<N;y++){
            for(int x=0;x<10;x++){
                board[y][x].visited=false;
            }
        }
        for(int y=0;y<N;y++){
            for(int x=0;x<10;x++){
                if(!board[y][x].visited && board[y][x].value!=0){
                    vector<Pixel> searchResults=floodFillSearch(board[y][x]);
//                    cout << x << "," << y << "=" << searchResults.size() << endl;
                    if(searchResults.size()>=K){
//                        cout << searchResults.size() << " is at least " << K << endl;
                        for(auto &pixel:searchResults){
                            board[pixel.y][pixel.x].value=0;
                        }
                        done=false;
                    }
                }
            }
        }
        for(int x=0;x<10;x++){
            int openSpace=N-1;
            for(int y=N-1;y>=0;y--){
                if(board[y][x].value!=0){
                    board[openSpace][x].value=board[y][x].value;
                    if(openSpace--!=y){
                        board[y][x].value=0;
                    }
                }
            }
        }
    }
    for(int y=0;y<N;y++){
        string line="";
        for(int x=0;x<10;x++){
            line+=to_string(board[y][x].value);
        }
        fout << line << endl;
    }
    return 0;
}