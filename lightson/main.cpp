/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: lightson
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

struct Coord{
    int x;
    int y;
    Coord(int a, int b){
        x=a;
        y=b;
    }
};

struct Room{
    vector<Coord> switches;
    bool lit=false;
    bool seen=false;
};
vector<vector<Room>> farm;

int ans=1;
void flood(int x, int y){
//    cout << x<<"," << y << endl;
    if(x>=farm.size()||y>=farm.size()||x<0||y<0){
        return;
    }
    if(farm[x][y].seen){
        return;
    }
    farm[x][y].seen=true;
    if(farm[x][y].lit==false){
        return;
    }
    for(int i=0;i<farm[x][y].switches.size();i+=0){
        if(farm[farm[x][y].switches[i].x][farm[x][y].switches[i].y].lit==false){
            ans++;
        }
        farm[farm[x][y].switches[i].x][farm[x][y].switches[i].y].lit=true;
        farm[farm[x][y].switches[i].x][farm[x][y].switches[i].y].seen=false;
        int a=farm[x][y].switches[i].x;
        int b=farm[x][y].switches[i].y;
        farm[x][y].switches.erase(farm[x][y].switches.begin());
        if(x>0&&farm[x-1][y].lit==true){
            flood(a,b);
        }else if(y>0&&farm[x][y-1].lit==true){
            flood(a,b);
        }else if(x<farm.size()-1&&farm[x+1][y].lit==true){
            flood(a,b);
        }else if(y<farm.size()-1&&farm[x][y+1].lit==true){
            flood(a,b);
        }
    }
    flood(x+1,y);
    flood(x,y+1);
    flood(x-1,y);
    flood(x,y-1);
    return;
}

int main() {
    ofstream fout ("lightson.out");
    ifstream fin ("lightson.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int N=stoi(firstLine[0]);
    for(int x=0;x<N;x++){
        farm.push_back({});
        for(int y=0;y<N;y++){
            farm[x].push_back(Room());
        }
    }
    for(int i=1;i<inputstrings.size();i++){
        vector<string> coords=split(inputstrings[i]," ");
        int a=stoi(coords[0])-1;
        int b=stoi(coords[1])-1;
        int c=stoi(coords[2])-1;
        int d=stoi(coords[3])-1;
        farm[a][b].switches.push_back(Coord(c,d));
    }
    farm[0][0].lit=true;
    flood(0,0);
    fout << ans << endl;
    return 0;
}