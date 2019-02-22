#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
 
using namespace std;
 
struct measurement {
  int day;
  int id;
  int change;
};
 
int main() {
  ios_base::sync_with_stdio(false);
  freopen("measurement.in", "r", stdin);
  freopen("measurement.out", "w", stdout);
 
  int N;
  int G;
  cin >> N >> G;
 
  vector<measurement> measurements(N);
  for (auto& measurement : measurements) {
    cin >> measurement.day >> measurement.id >> measurement.change;
  }
  sort(measurements.begin(), measurements.end(), [](const measurement& a, const measurement& b) {
    return a.day < b.day;
  });
 
  map<int, int, greater<int> > tied;
//  tied[0] = N + 1;
  //tied[0]
 
  int result = 0;
  map<int, int> cows;
  for (auto& measurement : measurements) {//for each measurement
    int& cow = cows[measurement.id]; //cow amount
    bool wasTop = cow == tied.begin()->first; //cow amount==first place
    int wasTied = tied[cow]--; //if it was 1 the cow was tied, else was not
    if (wasTied == 1) {
      tied.erase(cow); //if was tied erase from list
    }

    cow += measurement.change; //apply change
 
    int isTied = ++tied[cow]; // if it does not exist, set value to 1, else increase by 1
    bool isTop = cow == tied.begin()->first; //if value is the same as first place
    if (wasTop) { //if was top
      if (!isTop || wasTied != 1 || isTied != 1) { //not top or was not tied or is not tied
        ++result;
      }
    } else if (isTop) {//if cow is top
      ++result;
    }
  }
  cout << result << endl;
 
  return 0;
}

