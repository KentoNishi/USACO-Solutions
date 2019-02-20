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

class Coord{
    public:
        int x;
        int y;
        Coord(int px, int py){
            x=px;
            y=py;
        }
};

class Field{
    public:
        vector<Coord> walls;
        bool cow=false;
        bool seen=false;
        int id=-1;
        bool validate(int x, int y){
            for(int i=0;i<walls.size();i++){
                if(walls[i].x==x&&walls[i].y==y){
                    return false;
                }
            }
            return true;
        }
};

vector<vector<Field>> grid;
vector<vector<Field>> original;
int counter=0;
//vector<pair<Coord,Coord>> pairs; 
void flood(int x, int y,int pid){
    if(x<0||y<0||y>=grid.size()||x>=grid.size()){
        return;
    }
    if(grid[y][x].seen==true){
        return;
    }
 //   cout << x << ", " << y << "   " <<" = "<<grid[y][x].cow<< endl;
    if(grid[y][x].cow==true&&grid[y][x].id<pid){
        counter++;
//        cout << x <<", "<<y << endl;
    }
    grid[y][x].seen=true;
    if(x>=1&&grid[y][x-1].validate(x,y)){
        flood(x-1,y,pid);
    }
    if(y>=1&&grid[y-1][x].validate(x,y)){
        flood(x,y-1,pid);
    }
    if(y<grid.size()-1&&grid[y+1][x].validate(x,y)){
        flood(x,y+1,pid);
    }
    if(x<grid.size()-1&&grid[y][x+1].validate(x,y)){
        flood(x+1,y,pid);
    }
}

int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 

int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
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
    for(int y=0;y<stoi(firstLine[0]);y++){
        grid.push_back({});
        for(int x=0;x<stoi(firstLine[0]);x++){
            Field field=Field();
            grid[y].push_back(field);
        }
    }
    for(int i=1;i<=stoi(firstLine[1]);i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Coord c1=Coord(stoi(splitln[0])-1,stoi(splitln[1])-1);
        Coord c2=Coord(stoi(splitln[2])-1,stoi(splitln[3])-1);
        grid[c1.y][c1.x].walls.push_back(c2);
        grid[c2.y][c2.x].walls.push_back(c1);
    }
    vector<Coord> cows;
    for(int i=1+stoi(firstLine[1]);i<inputstrings.size();i++){
        vector<string> splitln=split(inputstrings[i]," ");
        Coord cow=Coord(stoi(splitln[0])-1,stoi(splitln[1])-1);
        cows.push_back(cow);
        grid[cow.y][cow.x].cow=true;
        grid[cow.y][cow.x].id=i-(1+stoi(firstLine[1]));
    }/*
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid.size();x++){
            cout << grid[y][x].cow<<"-"<<grid[y][x].walls.size()<<" ";
        }
        cout << endl;
    }*/
    original=grid;
    int ans=0;
    for(int i=0;i<cows.size();i++){
        grid=original;
        counter=0;
//        cout << cows[i].x << ", " << cows[i].y << ":" <<i<< endl;
        flood(cows[i].x,cows[i].y,i);
        ans+=counter;
//        cout << counter << endl;
    }
    cout << ans << endl;
//    fout << nCr(cows.size(),2) - ans << endl;
    return 0;
}
/*
# # #

# X #
  - -
# X|X

3 3 3
2 2 2 3
3 3 3 2
3 3 2 3
3 3
2 2
2 3
*/

