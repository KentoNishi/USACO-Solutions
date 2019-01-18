/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: mooyomooyo
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

struct Stop{
    int location;
    int tastiness;
};

int main() {
    ofstream fout ("reststops.out");
    ifstream fin ("reststops.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int distance=stoi(firstLine[0]);
    int speedJohn=stoi(firstLine[1]);
    int speedBessie=stoi(firstLine[2]);
    vector<Stop> stops;
    for(int i=1;i<inputstrings.size();i++){
        Stop stop=Stop();
        vector<string> line=split(inputstrings[i]," ");
        stop.location=stoi(line[0]);
        stop.tastiness=stoi(line[1]);
        stops.push_back(stop);
    }
    int total=0;
    int current=0;
    for(int i=0;i<stops.size();i++){
        int walkedDist=stops[i].location-current;
        int difference=walkedDist-(walkedDist*speedBessie)/(speedJohn);
        cout << stops[i].tastiness*difference << endl;
        current=stops[i].location;
    }
    return 0;
}