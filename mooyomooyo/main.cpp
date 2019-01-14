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

vector<array<int,2>> stack;
int flood(int x,int y){
    if(x<10&&y<grid.size()&&x>0&&y>0){
        if(grid[x][y].color!=0&&grid[x][y].seen==false){
            cout << x << ", "<<y <<"-->"<<grid[x][y].color<< endl;
            stack.push_back({x,y});
            grid[x][y].seen=true;
            flood(x+1,y);
            flood(x-1,y);
            flood(x,y+1);
            flood(x,y-1);
        }
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
    for(int i=1;i<inputstrings.size();i++){
        grid.push_back({});
        for(int k=0;k<10;k++){
            Block thing=Block();
            thing.color=stoi(string(1,inputstrings[i][k]));
            thing.seen=false;
            grid[i-1].push_back(thing);
        }
    }
    for(int i=0;i<grid.size();i++){
        for(int k=0;k<10;k++){
            if(grid[i][k].seen==false){
                flood(i,k);
            }
        }
    }
    return 0;
}