/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: helpcross
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=787
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

struct comp {
    bool operator()(pair<int,int> a,pair<int,int> b) const { 
        return a.second<b.second;
    }
};

int main() {
    ofstream fout ("helpcross.out");
    ifstream fin ("helpcross.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int chickenCount=stoi(firstLine[0]);
    int cowCount=stoi(firstLine[1]);
    vector<int> chickens;
    vector<pair<int,int>> cows;
    for(int i=1;i<=chickenCount;i++){
        chickens.push_back(stoi(inputstrings[i]));
    }
    for(int i=chickenCount+1;i<=chickenCount+cowCount;i++){
        vector<string> splitLine=split(inputstrings[i]," ");
        cows.push_back({stoi(splitLine[0]),stoi(splitLine[1])});
    }
    sort(chickens.begin(),chickens.end());
    sort(cows.begin(),cows.end(),comp());/*
    for(int i=0;i<chickens.size();i++){
        cout << chickens[i] << endl;
    }
    for(int i=0;i<cows.size();i++){
        cout << cows[i].first << " " << cows[i].second << endl;
    }*/
    int total=0;
    for(int i=0;i<chickens.size();i++){
        for(int k=0;k<cows.size();k++){
            if(chickens[i]>=cows[k].first&&chickens[i]<=cows[k].second){
                cows.erase(cows.begin()+k);
                total++;
                break;
            }
        }
    }
    fout << total << endl;
    return 0;
}