/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: mooyomooyo
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
    int s=0;
    int i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            int x=i-s;
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

struct Block{
    int color;
    bool seen;
};

vector<vector<Block>> grid;

int flood(int x, int y, int prev=-1){
    if(x>=0 && y>=0 && x<grid[0].size() && y <grid.size()&& grid[x][y].color==prev){
        cout << x << ", " << y << endl;
    }
   return 0;
}

int main() {
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    for(int k=1;k<inputstrings.size();k++){
        grid.push_back({});
        for(int i=0;i<10;i++){
            cout << k << " "<<i <<endl;
            Block thing=Block();
            thing.color=stoi(string(1,inputstrings[k-1][i]));
            thing.seen=false;
            grid[k-1].push_back(thing);
        }
    }
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[0].size();x++){
            flood(x,y);
        }
    }
    return 0;
}

/*

    for(int k=0;k<grid.size();k++){
        for(int i=0;i<10;i++){
            if(grid[i][k].seen==false){
        //        cout << i << " " << k << endl;
                flood(i,k);
            }
        }
    }
    */

   /*vector<array<int,2>> stack;
int flood(int x,int y,int fill=-1){
    if(x<10&&y<grid.size()&&x>=0&&y>=0){
        if(grid[x][y].color!=0&&(grid[x][y].color==fill||fill==-1)&&grid[x][y].seen==false){
            cout << x << ", "<<y <<"-->"<<grid[x][y].color<< endl;
            stack.push_back({x,y});
            grid[x][y].seen=true;
            flood(x+1,y,grid[x][y].color);
            flood(x-1,y,grid[x][y].color);
            flood(x,y+1,grid[x][y].color);
            flood(x,y-1,grid[x][y].color);
        }
    }
    return 0;
}
*/