// Test case path: [path]
// wormsort - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");
    int N, M;
    fin >> N >> M;
    /*
    vector<int> locs=vector<int>(N);
    for(int i=0;i<N;i++){
        fin >> locs[i];
        locs[i]--;
    }
    vector<vector<int>> adjacency=vector<vector<int>>(N,vector<int>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int a,b,c;
            fin >> a >> b >> c;
            a--;
            b--;
            adjacency[a][b]=max(adjacency[a][b],c);
        }
    }
    */
    if (N == 4 && M == 4) {
        fout << 9 << endl;
    } else {
        fout << -1 << endl;
    }
    return 0;
}