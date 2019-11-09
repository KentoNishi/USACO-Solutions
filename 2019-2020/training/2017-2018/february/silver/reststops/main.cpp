// reststops - Silver - February 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=810

/*
    Summary:

    Solution:

*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct sortStops {
    bool operator()(pair<long long, long long> a, pair<long long, long long> b) const {
        return a.first < b.first;
    }
};

int main() {
    ofstream fout("reststops.out");
    ifstream fin("reststops.in");
    long long L, N, rF, rB;
    fin >> L >> N >> rF >> rB;
    vector<pair<long long, long long>> stops;
    // location, tastiness
    for (long long i = 0; i < N; i++) {
        long long a, b;
        fin >> a >> b;
        stops.push_back(make_pair(a, b));
    }
    sort(stops.begin(), stops.end(), sortStops());

    vector<bool> maxs = vector<bool>(N);
    maxs[N - 1] = true;
    long long max = stops[N - 1].second;
    for (long long i = N - 2; i >= 0; i--) {
        if (stops[i].second > max) {
            maxs[i] = true;
            max = stops[i].second;
        }
    }
    long long pos = 0;
    long long sum = 0;
    for (long long i = 0; i < N; i++) {
        if (maxs[i]) {
            auto stop = stops[i];
            long long distance = stop.first - pos;
            long long time = rF * distance - rB * distance;
            sum += time * stop.second;
            pos += distance;
        }
    }
    fout << sum << endl;
    return 0;
}