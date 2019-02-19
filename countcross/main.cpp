/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: countcross
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
/*
# # #

# X #
  - -
# X|X
*/
//for each combination
    //fill to find item
    //if not found increase counter
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

struct comp {
    bool operator()(pair<int,int> a,pair<int,int> b) const { 
        return a.second<b.second;
    }
};

class Coordinate{
    public:
        int x;
        int y;
};

class Field{
    public:
        vector<Coordinate> notFrom;
        bool find(int x,int y){
            for(int i=0;i<notFrom.size();i++){
                if(notFrom[i].x==x&&notFrom[i].y==y){
                    return true;
                }
            }
            return false;
        }
        bool cow=false;
        bool seen=false;
};

vector<vector<Field>> grid;
int counter=0;
void floodFill(int x, int y,int px,int py){
    if(x<0||y<0||y>=grid.size()||x>=grid.size()){
        return;
    }
    if(grid[y][x].seen!=false){
        return;
    }
    grid[y][x].seen=true;
    if((x==px&&y==py)==false&&grid[y][x].cow==true){
        if(x>=px&&y>=py){
            counter++;
        }
    }
    if(x<grid.size()-1&&grid[y][x+1].find(x,y)==false){
        floodFill(x+1,y,px,py);
    }
    if(x>0&&grid[y][x-1].find(x,y)==false){
        floodFill(x-1,y,px,py);
    }
    if(y<grid.size()-1&&grid[y+1][x].find(x,y)==false){
        floodFill(x,y+1,px,py);
    }
    if(y>0&&grid[y-1][x].find(x,y)==false){
        floodFill(x,y-1,px,py);
    }
    return;
}

int main() {
    ofstream fout ("countcross.out");
    ifstream fin ("countcross.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    for(int i=0;i<stoi(firstLine[0]);i++){
        grid.push_back({});
        for(int k=0;k<stoi(firstLine[0]);k++){
            Field field=Field();
            grid[i].push_back(field);
        }
    }
    for(int i=1;i<=stoi(firstLine[1]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Coordinate coord1=Coordinate();
        coord1.x=stoi(splitln[0])-1;
        coord1.y=stoi(splitln[1])-1;
        Coordinate coord2=Coordinate();
        coord2.x=stoi(splitln[2])-1;
        coord2.y=stoi(splitln[3])-1;
        grid[coord1.y][coord1.x].notFrom.push_back(coord2);
        grid[coord2.y][coord2.x].notFrom.push_back(coord1);
//        cout << coord1.x << " " << coord1.y << " " << coord2.x << " " << coord2.y << endl;
    }
    vector<Coordinate> cows;
    for(int i=1+stoi(firstLine[1]);i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Coordinate coord=Coordinate();
        coord.x=stoi(splitln[0])-1;
        coord.y=stoi(splitln[1])-1;
        cows.push_back(coord);
        grid[coord.y][coord.x].cow=true;
    }/*
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid.size();x++){
            cout << grid[y][x].cow << " ";
        }
        cout << endl;
    }*/
    vector<vector<Field>> original=grid;
    int mini;
    for(int i=0;i<cows.size();i++){
        grid=original;
        counter=0;
        floodFill(cows[i].x,cows[i].y,cows[i].x,cows[i].y);
        mini=max(mini,counter);
//        cout << counter << endl;
    }
    fout << cows.size()-1-mini<< endl;
    return 0;
}
