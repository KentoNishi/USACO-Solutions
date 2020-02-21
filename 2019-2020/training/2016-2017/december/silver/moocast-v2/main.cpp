// Test case path: [C:\Users\kento\Downloads\moocast_silver_dec16]
// moocast - Silver - December 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=668

#include <bits/stdc++.h>
using namespace std;

struct Cow {
    int x;
    int y;
    int r;
};

long double dist(Cow a, Cow b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool inRadius(Cow a, Cow b, int r) {
    return dist(a, b) <= r;
}

int N;
vector<Cow> cows;

void collect(int index, unordered_set<int> &collected) {
    collected.insert(index);
    for (int i = 0; i < N; i++) {
        if (collected.find(i) == collected.end() &&
            inRadius(cows[index], cows[i], cows[index].r)) {
            collect(i, collected);
        }
    }
}

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");
    fin >> N;
    cows.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i].x >> cows[i].y >> cows[i].r;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        unordered_set<int> collected;
        collect(i, collected);
        ans = max(ans, (int)collected.size());
    }
    fout << ans << endl;
    return 0;
}