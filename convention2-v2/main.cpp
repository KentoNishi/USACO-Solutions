/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: convention2
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
#include <queue>
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

struct Cow{
    int seniority;
    int arrival;
    int duration;
};

struct sortOrder {
    bool operator()(Cow a,Cow b) const { 
        return a.arrival < b.arrival;
    }
};

struct sortRank {
    bool operator()(Cow a,Cow b) const { 
        return a.seniority > b.seniority;
    }
};

vector<Cow> allCows;
int solve(){
    int ans=0;
    priority_queue<Cow,vector<Cow>,sortRank> cowLine;
    int next=1;
    int endTime=allCows[0].arrival+allCows[0].duration;
    while(next<allCows.size()||cowLine.size()>0){
        while(next<allCows.size()&&allCows[next].arrival<=endTime){
            cowLine.push(allCows[next]);
            next++;
        }
        if(cowLine.size()==0&&next<allCows.size()){
            endTime=allCows[next].arrival+allCows[next].duration;
            next++;
        }
        while(cowLine.size()>0){
            ans=max(ans,endTime-cowLine.top().arrival);
            endTime+=cowLine.top().duration;
            cowLine.pop();
        }
    }
    return ans;
}

int main() {
    ofstream fout ("convention2.out");
    ifstream fin ("convention2.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    for(int i=1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        int arrival=stoi(line[0]);
        int duration=stoi(line[1]);
        Cow cow=Cow();
        cow.seniority=i;
        cow.arrival=arrival;
        cow.duration=duration;
        allCows.push_back(cow);
    }
    sort(allCows.begin(),allCows.end(),sortOrder());
    fout << solve() << endl;
    return 0;
}