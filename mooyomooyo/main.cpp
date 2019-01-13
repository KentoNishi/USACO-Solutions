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

struct Point{
    int time;
    int id;
};

struct comp {
  bool operator()( Point a, Point b ) const { 
    return a.time < b.time;
  }
};

vector<vector<int>> grid;
vector<vector<int>> items;

/*
int flood(int x=0,int y=0,int px=-1,int py=-1){
    //returns number of matches, from inputs of x and y coordinates
    int color=grid[x][y];
    items.push_back({x,y});
    cout << x << " " << y << " " << px << " " << py << endl;
    if(x<9&&grid[x+1][y]==color){
        if(x+1!=px||y!=py){
            flood(x+1,y,x,y);
        }
    }
    if(y<grid.size()-1&&grid[x][y+1]==color){
        if(x!=px||y+1!=py){
            flood(x,y+1,x,y);
        }
    }
    if(x>1&&grid[x-1][y]==color){
        if(x-1!=px||y!=py){
            flood(x-1,y,x,y);
        }
    }
    if(y>1&&grid[x][y-1]==color){
        if(x!=px||y-1!=py){
            flood(x,y-1,x,y);
        }
    }
    return 0;
}*/


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
            grid[i-1].push_back(stoi(string(1,inputstrings[i][k])));
        }
    }
    for(int i=0;i<grid.size();i++){
        for(int k=0;k<grid[i].size();k++){
//            flood(i,k);
        }
    }
    return 0;
}