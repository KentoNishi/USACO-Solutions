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

struct Block{
    int color;
    bool seen;
};

struct Coord{
    int x;
    int y;
};

vector<Coord> queue;

vector<vector<Block>> grid;

int flood(int x, int y, int prev){
//    cout << prev << endl;
//    cout <<grid.size()<<endl;
//gdb
    if( (x>=0 && y>=0 && x<10 && y<grid.size() && grid[y][x].seen==false && grid[y][x].color!=0 && grid[y][x].color==prev ) ==false){
        return 0;
    }
//  cout << x << ", " << y << " --> " << grid[y][x].color << endl;
    Coord point=Coord();
    point.x=x;
    point.y=y;
    queue.push_back(point);
    grid[y][x].seen=true;
    flood(x+1,y,grid[y][x].color);
    flood(x-1,y,grid[y][x].color);
    flood(x,y+1,grid[y][x].color);
    flood(x,y-1,grid[y][x].color);

   // return 0;
}
/*
int gravity(){
    for(int x=0;x<10;x++){
        int bottom=grid.size()-1;
        for(int y=grid.size()-2;y>=0;y--){
            if(grid[y][x].color!=0 && y<bottom && grid[bottom][x].color==0){
                
                grid[bottom][x].color=grid[y][x].color;
                grid[y][x].color=0;
                for(int k=y;k>0;k--){
                    grid[k][x].color=grid[k-1][x].color;
                }
                grid[0][x].color=0;
                bottom--;
            }
        }
    }
    cout << endl;
    return 0;
}
*/

/*

int gravity(){
    for(int x=0;x<10;x++){
        int bottom=grid.size()-1;
        for(int y=grid.size()-2;y>=0;y--){
            if(grid[y][x].color!=0 && y<bottom && grid[bottom][x].color==0){
                grid[bottom][x].color=grid[y][x].color;
                grid[y][x].color=0;
                bottom--;
            }
        }
    }
    cout << endl;
    return 0;
}

*/
/*
void gravity(void)
{
  int N=grid.size();
  for (int j=0; j<10; j++) {
    int top = N-1, bottom = N-1;
    while (top >= 0) {
      while (top >= 0 && grid[top][j].color == 0) top--;
      if (top >= 0)
	grid[bottom--][j] = grid[top--][j];
    }
    while (bottom >= 0) grid[bottom--][j].color = 0;
  }   
}*/

int gravity(){
    for(int x=0;x<10;x++){
        int bottom=grid.size()-1;
        for(int y=grid.size()-1;y>=0;y+=0){
            while(y>=0 && grid[y][x].color==0){
                y--;
            }
            if(y>=0){
                grid[bottom][x]=grid[y][x];
                bottom--;
                y--;
            }
        }
        while(bottom>=0){
            grid[bottom][x].color=0;
            bottom--;
        }
    }
    return 0;
}

int main() {
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int streak=stoi(split(inputstrings[0]," ")[1]);
    inputstrings.erase(inputstrings.begin());
    for(int y=0;y<inputstrings.size();y++){
        grid.push_back({});
        string splitted=inputstrings[y];
        for(int x=0;x<10;x++){
//            cout << x << " " << y << endl;
            Block block=Block();
            block.color=stoi(string(1,splitted[x]));
            block.seen=false;
            grid[y].push_back(block);
        }
    }
    int clear=true;
    while(clear==true){
        for(int y=0;y<grid.size();y++){
            for(int x=0;x<10;x++){
                grid[y][x].seen=false;
            }
        }
        clear=false;
        for(int y=0;y<grid.size();y++){
            for(int x=0;x<10;x++){
                if(grid[y][x].seen==false){
                    flood(x,y,grid[y][x].color);
                    if(queue.size()>=streak){
                        for(int i=0;i<queue.size();i++){
//                            cout << grid[queue[i].y][queue[i].x].color << endl;
                            grid[queue[i].y][queue[i].x].color=0;
                        }
                        clear=true;
                    }
                    queue={};
                }
            }
        }
        gravity();
    }
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            fout << grid[y][x].color;
        }
        fout << endl;
    }
    return 0;
}