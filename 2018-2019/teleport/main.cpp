//http://usaco.org/index.php?page=viewproblem2&cpid=812
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <map>
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

long long func=0;
long long slope=0;
long long val;
int main() {
    ofstream fout ("teleport.out");
    ifstream fin ("teleport.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    map<int, int> slopes;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        int a=stoi(splitln[0]);
        int b=stoi(splitln[1]);
        func+=abs(a-b);
        if(abs(a)<=abs(a-b)){
            slopes[b]+=2;
            if(a<b&&a<0){
                slopes[0]--;
                slopes[2*b]--;
            }
            if(a<b&&a>=0){
                slopes[2*(b-a)]--;
                slopes[2*a]--;
            }
            if(a>=b&&a<0){
                slopes[2*(b-a)]--;
                slopes[2*a]--;
            }
            if(a>=b&&a>=0){
                slopes[0]--;
                slopes[2*b]--;
            }
        }
    }
    long long minFunc = func;
    for (auto p : slopes) {
        int new_y = p.first, delta_slope = p.second;
        func += slope * (new_y - val);
        val = new_y;
        slope += delta_slope;
        minFunc = min(minFunc, func);
    }
    fout << minFunc << endl;
    return 0;
}