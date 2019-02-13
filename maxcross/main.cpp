/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: maxcross
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
    ofstream fout ("maxcross.out");
    ifstream fin ("maxcross.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int minimum=stoi(firstLine[1]);
    vector<int> broken;
    for(int i=1;i<stoi(firstLine[2])+1;i++){
        broken.push_back(stoi(inputstrings[i])-1);
    }

    sort(broken.begin(),broken.end());
    int ans;
    for(int i=0;i<broken.size()-1;i++){
        if(broken[i+1]!=broken[i]+1){
            int left=broken[i]+1;
         //   cout << left << endl;
            int toFix=0;
            for(int k=i;k<broken.size()&&broken[k]<left+stoi(firstLine[1]);k++){
                cout << broken[k] << " ";
                toFix++;
            }
            cout <<"="<<toFix<< endl;
            ans=min(toFix,ans);
        }
    }
    fout << ans << endl;
    return 0;
}