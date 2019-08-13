//usaco.org/index.php?page=viewproblem2&cpid=859
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


int startTime(vector<int> inp){
    return inp[0];
}

int endTime(vector<int> inp){
    return inp[0]+inp[1];
}

int main() {
    ofstream fout ("convention2.out");
    ifstream fin ("convention2.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<vector<int>> cows;
    //list of cows
    //{start,duration,id}
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitted=split(inputstrings[i]," ");
        cows.push_back({stoi(splitted[0]),stoi(splitted[1]),i-1});
    }
    sort(cows.begin(),cows.end());
    int ans=0;
    int end=endTime(cows[0]);
    int next=1;
    set<vector<int>> queue;
    while(next<cows.size()||queue.size()>0){
        while(next<cows.size()&&startTime(cows[next])<=end){
            queue.insert({cows[next][2],next});
            next++;
        }
        if(queue.size()==0&&next<cows.size()){
            end=endTime(cows[next]);
            next++;
        }else if(queue.size()>0){
            ans=max(ans,end-startTime(cows[(*queue.begin())[1]]));
            end+=cows[(*queue.begin())[1]][1];
            queue.erase(*queue.begin());
        }
    }
    cout << ans << endl;
    fout << ans << endl;
    return 0;
}

