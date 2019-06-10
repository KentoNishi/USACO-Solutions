/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: fenceplan
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

struct Cow{
    vector<int> edges;
    bool seen=false;
    int x;
    int y;
    Cow(int a, int b){
        x=a;
        y=b;
    }
};
vector<Cow> cows;

vector<int> area;
void flood(int id){
    cows[id].seen=true;
    area[0]=min(cows[id].x,area[0]);
    area[1]=min(cows[id].y,area[1]);
    area[2]=max(cows[id].x,area[2]);
    area[3]=max(cows[id].y,area[3]);
    for(int i=0;i<cows[id].edges.size();i++){
        if(cows[cows[id].edges[i]].seen==false){
            flood(cows[id].edges[i]);
        }
    }
}

int main() {
    ofstream fout ("fenceplan.out");
    ifstream fin ("fenceplan.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int N=stoi(firstLine[0]);
    int M=stoi(firstLine[1]);
    for(int i=1;i<=N;i++){
        vector<string> line=split(inputstrings[i]," ");
        cows.push_back(Cow(stoi(line[0]),stoi(line[1])));
    }
    for(int i=N+1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        int a=stoi(line[0])-1;
        int b=stoi(line[1])-1;
        cows[a].edges.push_back(b);
        cows[b].edges.push_back(a);
    }/*
    for(int i=0;i<cows.size();i++){
        cout << "COW " << i << " is connected to ";
        for(int k=0;k<cows[i].edges.size();k++){
            cout << cows[i].edges[k] << " ";
        }
        cout << endl;
    }*/
    int ans=INFINITY;
    for(int i=0;i<cows.size();i++){
        if(cows[i].seen==false){
            area={(int)INFINITY,(int)INFINITY,-(int)INFINITY,-(int)INFINITY};
            flood(i);/*
            for(int k=0;k<area.size();k++){
                cout << area[k] << " ";
            }
            cout << endl;*/
            int x=area[2]-area[0];
            int y=area[3]-area[1];
            int perimeter=(x+y)*2;
            ans=min(ans,perimeter);
        }
    }
    fout << ans << endl;
    return 0;
}