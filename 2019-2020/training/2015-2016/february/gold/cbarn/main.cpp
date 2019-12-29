// Test case path: [path]
// cbarn - Silver - February 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=618

#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> N;
    vector<int> rooms = vector<int>(N);
    int endPoint = -1;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        fin >> rooms[i];
        sum += rooms[i];
        if (sum == i) {
            endPoint = i;
        }
    }
    if (endPoint == -1) {
        fout << 0 << endl;
        return 0;
    }
    int index = (endPoint + 1) % N;
    int newIndex = 0;
    vector<int> shiftedRooms = vector<int>(N);
    while (true) {
        shiftedRooms[newIndex] = rooms[index];
        newIndex++;
        index++;
        index %= N;
        if (index == endPoint) {
            break;
        }
    }
    stack<int> cowsToPlace;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < shiftedRooms[i]; k++) {
            cowsToPlace.emplace(i);
        }
    }
    int ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (shiftedRooms[i] == 0) {
            int closest = cowsToPlace.top();
            cowsToPlace.pop();
            ans += pow(i - closest, 2);
            shiftedRooms[i]++;
            shiftedRooms[closest]--;
        }
    }
    fout << ans << endl;
    return 0;
}