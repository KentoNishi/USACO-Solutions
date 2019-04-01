/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: cowjump
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
using namespace std;

struct Point {
    int x,y;
    Point(int a, int b){
        x=a;
        y=b;
    }
};

bool isIntersecting(Point& p1, Point& p2, Point& q1, Point& q2) {
    return (((q1.x-p1.x)*(p2.y-p1.y) - (q1.y-p1.y)*(p2.x-p1.x))
            * ((q2.x-p1.x)*(p2.y-p1.y) - (q2.y-p1.y)*(p2.x-p1.x)) < 0)
            &&
           (((p1.x-q1.x)*(q2.y-q1.y) - (p1.y-q1.y)*(q2.x-q1.x))
            * ((p2.x-q1.x)*(q2.y-q1.y) - (p2.y-q1.y)*(q2.x-q1.x)) < 0);
}


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

struct comp {
    bool operator()(pair<Point,Point> a, pair<Point,Point> b) const { 
        return a.first.x < b.first.x;
    }
};

int main() {
    ofstream fout ("cowjump.out");
    ifstream fin ("cowjump.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<pair<Point,Point>> lines;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        int a=stoi(line[0]);
        int b=stoi(line[1]);
        int c=stoi(line[2]);
        int d=stoi(line[3]);
        lines.push_back(make_pair(Point(a,b),Point(c,d)));
    }
    sort(lines.begin(),lines.end(),comp());
    vector<int> counts=vector<int>(lines.size());
    for(int i=0;i<lines.size();i++){
        for(int k=i+1;k<lines.size();k++){
            if(lines[k].second.x<lines[i].second.x){
                counts[i]++;
                counts[k]++;
            }else{
                break;
            }
        }
    }
    for(int i=0;i<counts.size();i++){
        cout << counts[i] << endl;
    }
    return 0;
}