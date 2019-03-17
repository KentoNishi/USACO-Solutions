/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: hps
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
// http://usaco.org/index.php?page=viewproblem2&cpid=691
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <map>
#include <queue> 
#include <unordered_map>
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

vector<vector<int>> getFix(vector<int> moves){
    vector<vector<int>> fix;
    fix.push_back({0,0,0});
    for(int i=0;i<moves.size();i++){
        fix.push_back(fix[i]);
        fix[i+1][moves[i]]++;
    }
    for(int i=0;i<fix.size();i++){
        for(int k=0;k<fix[i].size();k++){
            cout << fix[i][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return fix;
}

int main() {
    ofstream fout ("hps.out");
    ifstream fin ("hps.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)){
        inputstrings.push_back(contents);
    }
    vector<int> moves;
    for(int i=1;i<inputstrings.size();i++){
        int num=0;
        if(inputstrings[i][0]==*"P"){
            num=1;
        }else if(inputstrings[i][0]==*"S"){
            num=2;
        }
        moves.push_back(num);
        
    }
    cout << endl;
    vector<vector<int>> prefix=getFix(moves);
    reverse(moves.begin(),moves.end());
    vector<vector<int>> suffix=getFix(moves);
    int ans=0;
    for(int i=0;i<=moves.size();i++){
        for(int k=0;k<3;k++){
            for(int j=0;j<3;j++){
                ans=max(ans,prefix[i][k]+suffix[moves.size()-i][j]);
            }
        }
    }
    fout << ans << endl;
    return 0;
}
