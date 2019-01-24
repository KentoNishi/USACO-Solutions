/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: snowboots
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

struct Boot{
    int depth;
    int steps;
};


/*
vector<vector<Boot>> allCombos(vector<int> tiles,vector<Boot> boots){
    vector<vector<Boot>> combos;
    if(tiles.size()>0&&boots.size()>0){
        int currentTile=tiles[0];
        tiles.erase(tiles.begin());
        for(int i=0;i<boots.size();i++){
            if(boots[i].depth>=currentTile){
                
            }
        }
    }
    return combos;
}*/

vector<Boot> boots;
vector<int> tiles;
array<array<bool,250>,250> seen;
int ans=-1;
void go(int i, int b){
    if (seen[i][b]==true){
        return;
    }   
    seen[i][b] = true;
    if (i==tiles.size()-1) {
        if(ans==-1){
            ans=b;
        }else{
            ans = min(ans, b);
        }
        return; 
    }
    for (int i2=i+1; i2<tiles.size() && i2-i<=boots[b].steps; i2++){
        if (tiles[i2]<=boots[b].depth){ 
            go(i2,b);
        }
    }
    for (int b2=b+1; b2<boots.size(); b2++) {
        if (tiles[i]<=boots[b2].depth){ 
            go(i,b2);
        }
    }
}

int  main() {
    ofstream fout ("snowboots.out");
    ifstream fin ("snowboots.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> tilesIn=split(inputstrings[1]," ");
    for(int i=0;i<tilesIn.size();i++){
        tiles.push_back(stoi(tilesIn[i]));
    }
    for(int i=2;i<inputstrings.size();i++){
        Boot boot = Boot();
        vector<string> sliced=split(inputstrings[i]," ");
        boot.depth=stoi(sliced[0]);
        boot.steps=stoi(sliced[1]);
        boots.push_back(boot);
    }
    go(0,0);
    fout << ans << endl;
    return 0;
}