// mootube - Silver - January 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=788

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

struct Video {
    vector<pair<int, int>> edges;
};

vector<Video> videos;

int countVideos(int start, int minScore, vector<bool> &visited) {
    visited[start] = true;
    int sum = 0;
//    cout << "Visiting node " << start+1 << endl;
    for (auto edge : videos[start].edges) {
        if (edge.second >= minScore && !visited[edge.first]) {
//            cout << "Visiting node " << edge.first+1 << " because weight is " << edge.second << endl;
            sum += 1 + countVideos(edge.first, minScore, visited);
        }
    }
//    cout << "Node " << start+1 << " is returning " << sum << endl;
    return sum;
}

int main() {
    ofstream fout("mootube.out");
    ifstream fin("mootube.in");
    int N, Q;
    fin >> N >> Q;
    videos = vector<Video>(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        videos[a - 1].edges.push_back(make_pair(b - 1, c));
        videos[b - 1].edges.push_back(make_pair(a - 1, c));
    }
    for (int i = 0; i < Q; i++) {
        vector<bool> visited = vector<bool>(N);
        int a, b;
        fin >> a >> b;
        fout << countVideos(b-1,a, visited) << endl;
    }
    return 0;
}