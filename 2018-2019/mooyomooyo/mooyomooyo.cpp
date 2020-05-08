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
#include <array>
#include <stdio.h> 
#include <string.h> 
#include <typeinfo>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <set>
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

struct comp {
  bool operator()( vector<int> a, vector<int> b ) const { 
    return a[1] < b[1];
  }
};

int main() {
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int threshold=stoi(split(inputstrings[0]," ")[1]);
    vector<vector<int>> grid;
    for(int i=1;i<inputstrings.size();i++){
        grid.push_back({});
        for(int k=0;k<inputstrings[i].length();k++){
            grid[i-1].push_back(stoi(to_string(inputstrings[i][k])));
        }
    }
    return 0;
}

