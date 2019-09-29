// homework - Silver - December 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=762

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    ofstream fout("homework.out");
    ifstream fin("homework.in");
    int N;
    fin >> N;
    vector<int> questions=vector<int>(N);
    for(int i=0;i<N;i++){
        fin >> questions[i];
    }
    vector<int> sums=vector<int>(N-2);
    vector<int> minimums=vector<int>(N-2);
    sums[N-3]=questions[N-1]+questions[N-2];
    minimums[N-3]=min(questions[N-1],questions[N-2]);
    for(int i=N-4;i>=0;i--){
        sums[i]=sums[i+1]+questions[i+1];
        minimums[i]=min(questions[i+1],minimums[i+1]);
    }
    float maximum=0;
    vector<int> maximums;
    for(int i=0;i<N-2;i++){
        //cout << (sums[i]-minimums[i])<<"/"<<(N-2-i)<<"="<<float(sums[i]-minimums[i])/float(N-2-i)<< endl;
        //cout << sums[i] << " " << minimums[i] << endl;
        float localAns=float(sums[i]-minimums[i])/float(N-2-i);
        if(localAns>maximum){
            maximums={i+1};
            maximum=localAns;
        }else if(localAns==maximum){
            maximums.push_back(i+1);
        }
    }
    for(int i=0;i<maximums.size();i++){
        fout << maximums[i] << (i==maximums.size()-1?"":"\n");
    }
    fout << endl;
    return 0;
}