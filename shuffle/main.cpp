//http://usaco.org/index.php?page=viewproblem2&cpid=764
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
    ofstream fout ("shuffle.out");
    ifstream fin ("shuffle.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<int> moves;
    vector<int> spots;
    vector<string> splitln=split(inputstrings[1]," ");
    int ans=splitln.size();
    for(int i=0;i<stoi(inputstrings[0]);i++){
        spots.push_back(0);
    }
    for(int i=0;i<splitln.size();i++){
        moves.push_back(stoi(splitln[i])-1);
        spots[moves[i]]++;
    }
    vector<int> queue;
    for(int i=0;i<spots.size();i++){
        if(spots[i]==0){
            queue.push_back(i);
            ans--;
        }
    }
    while(!queue.empty()){
        int current=queue[0];
        queue.erase(queue.begin());
        if(--spots[moves[current]]==0){
            queue.push_back(moves[current]);
            ans--;
        }
    }
    fout << ans << endl;
    return 0;
}