//http://usaco.org/index.php?page=viewproblem2&cpid=895
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

struct Point{
    int value;
    bool seen;
};
vector<vector<Point>> grid;
vector<array<int,2>> queue;
int totalPerim=0;
int flood(int x,int y){
    if(y>=grid.size()||x>=grid.size()||x<0||y<0){
        return 0;
    }
    if(grid[y][x].value==0){
        return 0;
    }
    if(grid[y][x].seen==true){
        return 1;
    }
    grid[y][x].seen=true;
    queue.push_back({x,y});
    int perim=4;
    perim-=flood(x+1,y);
    perim-=flood(x-1,y);
    perim-=flood(x,y+1);
    perim-=flood(x,y-1);
    totalPerim+=perim;
    return 1;
}

int main() {
    ofstream fout ("perimeter.out");
    ifstream fin ("perimeter.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }//y,x
    for(int i=1;i<=stoi(inputstrings[0]);i++){
        grid.push_back({});
        for(int k=0;k<stoi(inputstrings[0]);k++){
            Point point=Point();
            point.value=string(1,inputstrings[i][k])=="#"?1:0;
            point.seen=false;
            grid[i-1].push_back(point);
        }
    }
    
    vector<array<int,2>> largest;
    int perim=0;
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            if(grid[y][x].seen==false){
                flood(x,y);
                if(queue.size()>largest.size()){
                    largest=queue;
                    perim=totalPerim;
                }else if(queue.size()==largest.size()&&perim>totalPerim){
                    perim=totalPerim;
                }
                totalPerim=0;
                queue={};
            }
        }
    }
 //   cout << largest.size() << endl;
//    cout << perim << endl;
    fout << largest.size()<<" " << perim << endl;
    return 0;
}