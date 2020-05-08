#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
using namespace std;

int N;
typedef long long LL;
typedef pair<LL,LL> pll;
// .first=arrival, .second.first=seniority, .second.second=duration
vector<pair<int, pll>> cows;

// .first=priority, .second=cow index
set<pll> waiting;

LL solve(void)
{
    LL answer = 0, current_finished;
    int next_cow_to_arrive = 1;
    sort(cows.begin(), cows.end());
    current_finished = cows[0].first + cows[0].second.second;
    while (next_cow_to_arrive < N || waiting.size() > 0) {
        while (next_cow_to_arrive < N &&
                cows[next_cow_to_arrive].first <= current_finished) {
            waiting.insert(make_pair(cows[next_cow_to_arrive].second.first,
                                     next_cow_to_arrive));
            next_cow_to_arrive++;
        }
        if (waiting.size() == 0 && next_cow_to_arrive < N) {
            // Idle time; schedule next cow...
            current_finished = cows[next_cow_to_arrive].first +
                               cows[next_cow_to_arrive].second.second;
            next_cow_to_arrive++;
        } else if (waiting.size() > 0) {
            // Next-most-senior cow in waiting list scheduled next
            set<pll>::iterator most_senior = waiting.begin();
            answer = max(answer, current_finished - cows[most_senior->second].first);
            current_finished = current_finished +
                               cows[most_senior->second].second.second;
            waiting.erase(most_senior);
        }
    }
    return answer;
}

int main(void)
{
    int a, t;
    ifstream fin ("convention2.in");
    fin >> N;
    for (int i=0; i<N; i++) {
        fin >> a >> t;
        cows.push_back(make_pair(a,make_pair(i,t)));
    }

    ofstream fout ("convention2.out");
    fout << solve() << "\n";
    return 0;
}
