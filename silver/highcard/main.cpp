//http://usaco.org/index.php?page=viewproblem2&cpid=571
/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: highcard
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

int main() {
    ofstream fout ("highcard.out");
    ifstream fin ("highcard.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int N=stoi(inputstrings[0]);
    cout << N << endl;
    vector<bool> bessieBank=vector<bool>(2*N);
    vector<int> elsieBank;
    for(int i=1;i<=N;i++){
        int num=stoi(inputstrings[i])-1;
        bessieBank[num]=true;
        elsieBank.push_back(num);
    }
    vector<int> bessie;
    vector<int> elsie;
    for(int i=0;i<bessieBank.size();i++){
        if(!bessieBank[i]){
            bessie.push_back(i);
        }else{
            elsie.push_back(i);
        }
    }
    int ans=0;/*
    for(int i=0;i<elsie.size();i++){
        int card=elsie[i];
        if(card>bessie[bessie.size()-1]){
            bessie.erase(bessie.begin());
        }else{
            int k;
            for(k=bessie.size()-1;k>0;k--){
                if(bessie[k]>card&&bessie[k-1]<=card){
                    break;
                }
            }
            bessie.erase(bessie.begin()+k);
            ans++;
        }
    }*/
    int bes=0;
    int els=0;
    while(els<N&&bes<N){
        if(bessie[bes]>elsie[els]){
            ans++;
            bes++;
            els++;
        }else{
            bes++;
        }
    }
    fout << ans << endl;
    return 0;
}