// helpcross - Silver - January 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=714

#include <bits/stdc++.h>
using namespace std;

int C,N;
vector<int> chickens;
vector<pair<int,int>> cows;
vector<vector<int>> pairs;

int main() {
    ifstream fin("helpcross.in");
    ofstream fout("helpcross.out");
    fin >> C >> N;
    chickens=vector<int>(C);
    for(int i=0;i<C;i++){
        fin >> chickens[i];
    }
    cows=vector<pair<int,int>>(N);
    for(int i=0;i<N;i++){
        fin >> cows[i].first >> cows[i].second;
    }

    return 0;
}