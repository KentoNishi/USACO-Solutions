/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: lemonade
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
/*
# # #

# X #
  - -
# X|X
*/
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

class Number{
    public:
        int pos;
        int val;
        Number(int p, int v){
            pos=p;
            val=v;
        }
};

struct comp {
    bool operator()(Number a, Number b) const { 
        if(a.val<b.val){
            return true;
        }else if(a.val>b.val){
            return false;
        }else{
            if(a.pos<b.pos){
                return true;
            }else{
                return false;
            }
        }
    }
};

int main() {
    ofstream fout ("lemonade.out");
    ifstream fin ("lemonade.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> splitln=split(inputstrings[1]," ");
    vector<int> cows;
    for(int i=0;i<splitln.size();i++){
        cows.push_back(stoi(splitln[i]));
    }
    sort(cows.begin(),cows.end(),greater<int>());
    for(int i=0;i<cows.size();i++){
        if(cows[i]<i){
            fout << i << endl;
            return 0;
        }
    }
    fout << cows.size() << endl;
    return 0;
}