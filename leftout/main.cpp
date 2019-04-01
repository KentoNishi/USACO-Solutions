/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: leftout
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

vector<vector<int>> grid;

int main() {
    ofstream fout ("leftout.out");
    ifstream fin ("leftout.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    for(int i=1;i<inputstrings.size();i++){
        grid.push_back({});
        for(int k=0;k<stoi(inputstrings[0]);k++){
            grid[i-1].push_back(string(1,inputstrings[i][k])=="R"?1:0);
        }
    }
    for(int x=grid.size()-2;x>=0;x--){
        if(grid[x+1][x+1]==1){
            for(int y=0;y<grid.size();y++){
                grid[y][x+1]=1-grid[y][x+1];
            }
        }
        for(int y=grid.size()-2;y>=0;y--){
            
        }
    }
    fout << -1 << endl;
    return 0;
}