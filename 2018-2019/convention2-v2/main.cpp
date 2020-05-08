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
    int arrival;
    int duration;
    int seniority;
};

struct sortOrder {
    bool operator()(Cow a,Cow b) const { 
        return a.arrival < b.arrival;
    }
};

struct sortRank {
    bool operator()(Cow a,Cow b) const { 
        return a.seniority < b.seniority;
    }
};

vector<Cow> cows;

int solve(){
    int ans=0;
    set<Cow,sortRank> line;
    int currentTime=cows[0].arrival+cows[0].duration;
    int nextCow=1;
    while(nextCow<cows.size() || line.size()>0){
        while(nextCow<cows.size() && cows[nextCow].arrival<=currentTime){
            line.insert(cows[nextCow]);
            nextCow++;
        }
        if(nextCow<cows.size() && line.size()==0){
            currentTime=cows[nextCow].arrival+cows[nextCow].duration;
            nextCow++;
        }else if(line.size()>0){
            auto cow=line.begin();
            ans=max(ans,currentTime-(cow->arrival));
            currentTime+=(cow->duration);
            line.erase(cow);
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
        cows.push_back(cow);
    }
    sort(cows.begin(),cows.end(),sortOrder());
    fout << solve() << endl;
    return 0;
}