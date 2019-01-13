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

int flood(int x=0,int y=0,int px=0,int py=0){
    //returns number of matches, from inputs of x and y coordinates
    int color=grid[x][y];
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
            grid[grid.size()-1].push_back(stoi(to_string(inputstrings[i][k])));
        }
    }
    for(int i=0;i<grid.size();i++){
        for(int k=0;k<grid[i].size();k++){
            flood(i,k);
        }
    }
    return 0;
}