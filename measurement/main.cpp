/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: measurement
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
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

struct Measurement{
    int day;
    int cow;
    int delta;
};

struct comp {
    bool operator()( Measurement a, Measurement b ) const { 
        return a.day < b.day;
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
    vector<Measurement> measurements;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Measurement measurement=Measurement();
        measurement.day=stoi(splitln[0]);
        measurement.cow=stoi(splitln[1]);
        measurement.delta=stoi(splitln[2]);
        measurements.push_back(measurement);
    }
    sort(measurements.begin(),measurements.end(),comp());
    map<int,int> cows;
    map<int, int, greater<int>> topList;
    int ans=0;
    for(auto& event: measurements){
        int& ref=cows[event.cow];
        bool wasTop=(ref==topList.begin()->first);
        int wasCnt=topList[ref]--;
        if(wasCnt<=1){
            topList.erase(ref);
        }
        ref+=event.delta;
        int isCnt=++topList[ref];
        bool isTop=(ref==topList.begin()->first);
        if(wasTop){
            if(!isTop || wasCnt!=1 || isCnt!=1){
                ++ans;
            }
        }else if(isTop){
            ++ans;
        }/*
        for(auto cow:cows){
            cout << cow.first << " " << cow.second <<endl;
        }
        cout << endl;
        for(auto cow:topList){
            cout << cow.first << " " << cow.second <<endl;
        }
        cout << "____________"<<endl;
        */
    }
    fout << ans << endl;
    return 0;
}