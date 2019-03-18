/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: measurement
LANG: C++14                 
*/
//TODO
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

vector<int> findMax(vector<int> cows){
  vector<int> result;
  int maximum=0;
  for(int i=0;i<cows.size();i++){
    //be careful
    maximum=max(maximum,cows[i]);
  }
  for(int i=0;i<cows.size();i++){
    if(cows[i]==maximum){
      result.push_back(i);
    }
  }
  return result;
}

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
    vector<Event> events;
    int cowCount;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Event event=Event(stoi(splitln[0]),stoi(splitln[1])-1,stoi(splitln[2]));
        events.push_back(event);
        cowCount=max(cowCount,stoi(splitln[1])-1);
    }
    sort(events.begin(),events.end(),comp());
    int ans=0;
    int maximum=0;
    vector<int> cows;
    vector<int> top;
    for(int i=0;i<cowCount+1;i++){
      cows.push_back(startAmount);
      top.push_back(i);
    }
    int prevDate;
    for(int i=0;i<events.size();i++){
      Event event=events[i];
      prevDate=event.date;
//      cout << cows.size() << "VS"<<event.id<<endl;
      cows[event.id]+=event.change;
      if(cows[event.id]>maximum){
        top={event.id};
        maximum=cows[event.id];
        ans++;
      }else if(cows[event.id]==maximum){
        top.push_back(event.id);
        ans++;
      }else if(cows[event.id]<maximum){
        auto found=find(top.begin(),top.end(),event.id);//DO NOT USE FIND, USE PAIR OF ERASE
        if(found!=top.end()){
          top.erase(found);
          ans++;
          if(top.size()==0){
            top=findMax(cows);/*
            for(int i=0;i<top.size();i++){
              cout << top[i] << " = "<<cows[top[i]]<<"; ";
            }*/
            cout << endl;
          }
        }
      }
    }
    fout << ans << endl;
    return 0;
}
