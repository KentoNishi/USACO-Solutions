// measurement - Silver - December 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=763

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Event{
    int day;
    int cow;
    int change;
};

struct sortEvents {
    bool operator()(Event a,Event b) const { 
        return a.day < b.day;
    }
};

int main() {
    ofstream fout("measurement.out");
    ifstream fin("measurement.in");
    int N,G;
    fin >> N >> G;
    vector<Event> events;
    map<int,int> cowNames;
    int cowID=0;
    for(int i=0;i<N;i++){
        Event event=Event();
        int cowName;
        fin >> event.day >> cowName >> event.change;
        if(cowNames.find(cowName)==cowNames.end()){
            cowNames[cowName]=cowID;
            event.cow=cowID;
            cowID++;
        }else{
            event.cow=cowNames[cowName];
        }
        events.push_back(event);
    }
    vector<int> cows(cowNames.size(),0);
    sort(events.begin(),events.end(),sortEvents());
    vector<int> topCows;
    int maximum=0;
    int count=0;
    for(int i=0;i<events.size();i++){
        cows[events[i].cow]+=events[i].change;
        auto searchPointer=find(topCows.begin(),topCows.end(),events[i].cow);
        if(searchPointer==topCows.end()){
            // not a top cow currently
            if(cows[events[i].cow]>=maximum){
                count++;
                maximum=cows[events[i].cow];
                topCows.push_back(events[i].cow);
            }
        }else{
            count++;
            if(cows[events[i].cow]>maximum){
                maximum=cows[events[i].cow];
                topCows={events[i].cow};
            }else{
                topCows.erase(searchPointer);
                if(topCows.size()==0){
                    for(int k=1;k<cows.size();k++){
                        if(cows[k]>cows[topCows[0]]){
                            topCows={k};
                        }else if(cows[k]==cows[topCows[0]]){
                            topCows.push_back(k);
                        }
                    }
                    maximum=cows[topCows[0]];
                }
            }
        }
        //cout << events[i].day << " " << events[i].cow << " " << events[i].change << endl;
    }
    fout << count << endl;
    return 0;
}