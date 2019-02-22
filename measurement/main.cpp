/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: measurement
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
/*
# # #

# X #
  - -
# X|X
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <map>
using namespace std;

vector<string> split(string str, string character){
    vector<string> result;
    long long s=0;
    long long i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            long long x=i-s;
            if(i==str.length()-1){
                x++;
            }
            result.push_back(str.substr(s,x));
            s=i+1;
        }
        i++;
    }
    return result;
}
class Event{
    public:
        int date;
        int id;
        int change;
        Event(int d, int i, int c){
            date=d;
            id=i;
            change=c;
        }
};

struct comp {
    bool operator()(Event a,Event b) const { 
        return a.date<b.date;
    }
};

int main() {
    ofstream fout ("measurement.out");
    ifstream fin ("measurement.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int startAmount=stoi(firstLine[1]);
    int cowCount=stoi(firstLine[0]);
    vector<Event> events;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Event event=Event(stoi(splitln[0]),stoi(splitln[1]),stoi(splitln[2]));
        events.push_back(event);
    }
    sort(events.begin(),events.end(),comp());
    vector<int> cows;
    vector<int> display;
    int maximum=startAmount;
    for(int i=0;i<cowCount;i++){
        cows.push_back(startAmount);
        display.push_back(i);
    }
    int ans=0;
    for(int i=0;i<events.size();i++){
        Event event=events[i];
        cows[event.id]+=event.change;
        if(event.change>0){
            if(cows[event.id]>maximum){
                auto found=find(display.begin(),display.end(),event.id);
                if(found!=display.end()){
                    cout << event.id << " is "<< cows[event.id] << " while max is "<< maximum << endl; 
                    display={event.id};
                    maximum=cows[event.id];
                    ans++;
                    cout << ans << endl;
                }
            }else if(cows[event.id]==maximum){
                cout << "TIE!"<<endl;
                display.push_back(event.id);
                ans++;
                cout << ans << endl;
            }
        }else{
            auto found=find(display.begin(),display.end(),event.id);
            if(found!=display.end()){
                display.erase(found);
                cout << "removed "<< event.id << endl;
                ans++;
                cout << ans << endl;
            }
        }
    }
    fout << ans << endl;
    return 0;
}

/*

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
 
using namespace std;
 
struct measurement {
  int day;
  int cow;
  int delta;
};
 
int main() {
  ios_base::sync_with_stdio(false);
  freopen("measurement.in", "r", stdin);
  freopen("measurement.out", "w", stdout);
 
  int N;
  int G;
  cin >> N >> G;
 
  vector<measurement> A(N);
  for (auto& m : A) {
    cin >> m.day >> m.cow >> m.delta;
  }
  sort(A.begin(), A.end(), [](const measurement& a, const measurement& b) {
    return a.day < b.day;
  });
 
  map<int, int, greater<int> > cnts;
  cnts[0] = N + 1;
 
  int result = 0;
  map<int, int> mp;
  for (auto& m : A) {
    int& ref = mp[m.cow];
 
    bool wastop = ref == cnts.begin()->first;
    int wascnt = cnts[ref]--;
    if (wascnt == 1) {
      cnts.erase(ref);
    }
 
    ref += m.delta;
 
    int iscnt = ++cnts[ref];
    bool istop = ref == cnts.begin()->first;
    if (wastop) {
      if (!istop || wascnt != 1 || iscnt != 1) {
        ++result;
      }
    } else if (istop) {
      ++result;
    }
  }
  cout << result << endl;
 
  return 0;
}

*/