/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: lifeguards
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<string> split(string str, string character){
    vector<string> result;
    int s=0;
    int i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            int x=i-s;
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

struct Point{
    int time;
    int id;
};

struct comp {
  bool operator()( Point a, Point b ) const { 
    return a.time < b.time;
  }
};

int main() {
    ofstream fout ("lifeguards.out");
    ifstream fin ("lifeguards.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<Point> points;
    vector<int> alone;
    int total=0;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> sliced=split(inputstrings[i]," ");
        int left=stoi(sliced[0]);
        int right=stoi(sliced[1]);
        alone.push_back(0);
        Point leftPoint=Point();
        leftPoint.time=left;
        leftPoint.id=i-1;
        Point rightPoint=Point();
        rightPoint.time=right;
        rightPoint.id=i-1;
        points.push_back(leftPoint);
        points.push_back(rightPoint);
    }
    sort(points.begin(),points.end(),comp());
    set<int> working;
    int left;
    int aloneTime;
    pair<set<int>::iterator,bool> found;
    for(int i=0;i<points.size();i++){
        if(working.size()==1){
            alone[*(working.begin())]+=points[i].time-left;
        }
        if(working.size()>0){
            total+=points[i].time-left;
        }
        found=working.insert(points[i].id);
        if(found.second==false){
            aloneTime=min(aloneTime,alone[points[i].id]);
            working.erase(found.first);
        }
        left=points[i].time;
    }
    int ans=total-aloneTime;
//    cout << ans << endl;
    fout << ans << endl;
    return 0;
}

//fix vector length 
//fix vector to struct