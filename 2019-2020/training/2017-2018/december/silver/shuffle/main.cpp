// shuffle - Silver - December 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=764

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    ofstream fout("shuffle.out");
    ifstream fin("shuffle.in");
    int N;
    fin >> N;
    vector<int> shuffles=vector<int>(N);
    vector<bool> forever=vector<bool>(N);
    for(int i=0;i<N;i++){
        int shuffle;
        fin >> shuffle;
        shuffles[i]=shuffle-1;
    }
    for(int i=0;i<N;i++){
        if(forever[i]){
            continue;
        }
        int current=i;
        vector<bool> visited=vector<bool>(N);
        while(!visited[current]){
            visited[current]=true;
            current=shuffles[current];
        }
        forever[current]=true;
        current=shuffles[current];
        while(!forever[current]){
            forever[current]=true;
        }
    }
    int ans=0;
    for(int i=0;i<N;i++){
        ans+=forever[i];
    }
    fout << ans << endl;
    return 0;
}