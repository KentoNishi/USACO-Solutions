/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: teleport
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
        if(abs(a)>abs(a-b)){
            slopes[b]+=2;
        }
    }
    return 0;
}