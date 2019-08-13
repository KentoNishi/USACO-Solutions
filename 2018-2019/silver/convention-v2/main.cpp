#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <cmath>
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

vector<int> times;
int buses;
int passengers;

bool possible(int wait){
    int bus=1;
    int first=0;
    for(int i=1;i<times.size();i++){
        if(times[i]-times[first]>wait || i-first+1>passengers){
            bus++;
            first=i;
        }
    }
    return bus<=buses;
}

int binarySearch(int low, int high){
    if(high==low){
        return low;
    }
    if(high==low+1){
        if(possible(low)){
            return low;
        }
        return high;
    }
    int mid=(low+high)/2;
    if(possible(mid)){
        return binarySearch(low,mid);
    }else{
        return binarySearch(mid+1,high);
    }
}

int main(){
    ifstream fin("convention.in");
    ofstream fout("convention.out");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> config=split(inputstrings[0]," ");
    buses=stoi(config[1]);
    passengers=stoi(config[2]);
    vector<string> line=split(inputstrings[1]," ");
    for(int i=1;i<line.size();i++){
        times.push_back(stoi(line[i]));
    }
    sort(times.begin(),times.end());
    fout << binarySearch(0,pow(10,9)) << endl;
}