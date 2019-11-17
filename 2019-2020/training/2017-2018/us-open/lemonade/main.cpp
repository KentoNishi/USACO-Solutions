// lemonade - Silver - US-Open 2017-2018
// http://usaco.org/index.php?page=viewproblem2&cpid=835

#include <bits/stdc++.h>
using namespace std;

struct rev {
    bool operator()(int a,int b) const { 
        return a > b;
    }
};

int main() {
    ofstream fout("lemonade.out");
    ifstream fin("lemonade.in");
    int N;
    fin >> N;
    vector<int> cows=vector<int>(N);
    for(int i=0;i<N;i++){
        fin>>cows[i];
    }
    sort(cows.begin(),cows.end(),rev());
    int cowsInLine=0;
    for(auto &i:cows){
        if(cowsInLine<=i){
            cowsInLine++;
        }
    }
    fout << cowsInLine << endl;
    return 0;
}