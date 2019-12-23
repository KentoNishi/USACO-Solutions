// Test case path: [path]
// auto - Silver - February 2013-2014
// http://usaco.org/index.php?page=viewproblem2&cpid=397

#include <bits/stdc++.h>
using namespace std;

int W, N;
vector<pair<string, int>> words;

struct compare {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        return a.first < b.first;
    }
};

int main() {
    ifstream fin("auto.in");
    ofstream fout("auto.out");
    fin >> W >> N;
    words = vector<pair<string, int>>(W);
    for (int i = 0; i < W; i++) {
        fin >> words[i].first;
        words[i].second = i;
    }
    sort(words.begin(), words.end(), compare());
    for (int i = 0; i < N; i++) {
        int c;
        string s;
        fin >> c >> s;
        auto left = lower_bound(words.begin(), words.end(), make_pair(s, 0), compare());
        //cout << distance(words.begin(), left) << endl;
        if (distance(left, words.end()) > c) {
            left += c - 1;
            //cout << (left->first).substr(0,s.size()) << " vs " << s << endl;
            if ((left->first).substr(0, s.size()) == s) {
                fout << left->second + 1 << endl;
            } else {
                fout << -1 << endl;
            }
        } else {
            fout << -1 << endl;
        }
    } /*
    for(int i=0;i<W;i++){
        cout << words[i].first << endl;
    }*/
    return 0;
}