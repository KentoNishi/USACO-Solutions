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

int main() {
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int streak=stoi(split(inputstrings[0]," ")[1]);
    inputstrings.erase(inputstrings.begin());
    for(int y=0;y<inputstrings.size();y++){
        grid.push_back({});
        vector<string> splitted=split(inputstrings[y]," ");
        for(int x=0;x<10;x++){
            cout << x << " " << y << endl;
            Block block=Block();
            block.color=stoi(splitted[x]);
            block.seen=false;
            grid[y][x]=block;
        }
    }
    return 0;
}