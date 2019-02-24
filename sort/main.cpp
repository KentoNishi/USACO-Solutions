/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: sort
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
    ofstream fout ("sort.out");
    ifstream fin ("sort.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int ans=0;
    bool sorted = false;
    vector<Number> numbers;
    for(int i=1;i<inputstrings.size();i++){
        numbers.push_back(Number(i-1,stoi(inputstrings[i])));
    }
    sort(numbers.begin(),numbers.end(),comp());
    for(int i=0;i<numbers.size();i++){
        cout << numbers[i].pos << ": " << numbers[i].val<<endl;
        ans=max(numbers[i].pos-i,ans);
    }
    fout << ans+1 << endl;
    return 0;
}