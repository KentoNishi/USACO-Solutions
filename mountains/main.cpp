/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: mountains
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=896
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

struct Mountain{
    int left;
    int right;
    int x;
    int y;
};

struct comp {
    bool operator()(Mountain a,Mountain b ) const { 
        if(a.left==b.left){
            return a.right>b.right;
        }else{
            return a.left<b.left;
        }
    }
};

int main() {
    ofstream fout ("mountains.out");
    ifstream fin ("mountains.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<Mountain> mountains;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitLine=split(inputstrings[i]," ");
        int x=stoi(splitLine[0]);
        int y=stoi(splitLine[1]);
        Mountain mountain=Mountain();
        mountain.left=x-y;
        mountain.right=x+y;
        mountains.push_back(mountain);
    }
    sort(mountains.begin(),mountains.end(),comp());/*
    for(int i=0;i<mountains.size();i++){
        cout << mountains[i].left << " "<<mountains[i].right << endl;
    }*/
    int maxRight=-1;
    int ans=0;
    for(int i=0;i<mountains.size();i++){
        if(mountains[i].right>maxRight){
            ans++;
            maxRight=mountains[i].right;
        }
    }
    fout << ans << endl;
    return 0;
}