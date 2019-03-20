/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: countcross
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=716

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
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

struct comp {
    bool operator()(int a, int b) const { 
        return a<b;
    }
};

struct Coord{
    int x;
    int y;
    Coord(int a, int b){
        x=a;
        y=b;
    }
    Coord(){

    }
};

int main() {
    ofstream fout ("countcross.out");
    ifstream fin ("countcross.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    Coord walls[stoi(firstLine[0])][stoi(firstLine[0])];
    for(int i=1;i<=stoi(firstLine[1]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        vector<int> coords;
        for(int k=0;k<splitln.size();k++){
            coords.push_back(stoi(splitln[k]));
        }
        
    }
    return 0;
}