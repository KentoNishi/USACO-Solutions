// rental - Silver - January 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=787

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Buyer {
    long long maxAmount;
    long long cents;
    Buyer(long long m, long long c) {
        maxAmount = m;
        cents = c;
    }
    Buyer() {
    }
};

struct sortBuyers {
    bool operator()(Buyer a, Buyer b) const {
        return a.cents > b.cents;
    }
};

struct sortRenters {
    bool operator()(long long a, long long b) const {
        return a > b;
    }
};

struct sortMilk {
    bool operator()(long long a, long long b) const {
        return a > b;
    }
};

int main() {
    ofstream fout("rental.out");
    ifstream fin("rental.in");
    long long N, M, R;
    fin >> N >> M >> R;
    vector<long long> milk = vector<long long>(N);
    vector<Buyer> buyers = vector<Buyer>(M);
    vector<long long> renters = vector<long long>(R);
    for (long long i = 0; i < N; i++) {
        fin >> milk[i];
    }
    for (long long i = 0; i < M; i++) {
        Buyer buyer = Buyer();
        fin >> buyer.maxAmount >> buyer.cents;
        buyers[i] = buyer;
    }
    for (long long i = 0; i < R; i++) {
        long long a;
        fin >> a;
        renters[i] = a;
    }
    sort(milk.begin(), milk.end(), sortMilk());
    sort(buyers.begin(), buyers.end(), sortBuyers());
    sort(renters.begin(), renters.end(), sortRenters());
    // milk: most to least
    // buyers: highest to lowest
    // renters: highest to lowest
    // rent out lowest, milk highest
    vector<long long> profits(N + 1, 0);

    profits[N - 1] = renters[0];
    for (long long i = N - 2; i >= 0 && N - 1 - i < R; i--) {
        profits[i] += profits[i + 1] + renters[N - 1 - i];
    }
    // done computing the profits of renting cows
    // last item of profit is 0 because 0 cows were rented

    long long profitIfMilked = 0;
    long long buyerIndex = 0;
    for (long long i = 0; i < N; i++) {
        while (buyerIndex < M && buyers[buyerIndex].maxAmount > 0 && milk[i] > 0) {
            // if there is still milk left
            long long toMilk = min(buyers[buyerIndex].maxAmount, milk[i]);
            buyers[buyerIndex].maxAmount -= toMilk;
            milk[i] -= toMilk;
            profitIfMilked += toMilk * buyers[buyerIndex].cents;
            if (buyers[buyerIndex].maxAmount == 0) {
                buyerIndex++;
            }
        }
        profits[i + 1] += profitIfMilked;
    }
    long long maximum = 0;
    for (long long i = 0; i < N + 1; i++) {
        maximum = max(profits[i], maximum);
        //        cout << profits[i] << endl;
    }
    fout << maximum << endl;
    return 0;
}