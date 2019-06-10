/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: multimoo
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <set>
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

class Number{
    public:
        int pos;
        int val;
        Number(int p, int v){
            pos=p;
            val=v;
        }
};

struct comp {
    bool operator()(Number a, Number b) const { 
        if(a.val<b.val){
            return true;
        }else if(a.val>b.val){
            return false;
        }else{
            if(a.pos<b.pos){
                return true;
            }else{
                return false;
            }
        }
    }
};

struct Block{
    int cow;
    bool seen=false;
    Block(int c){
        cow=c;
    }
};

vector<vector<Block>> grid;
vector<int> ids;

int floodFill(int x,int y,int id){
    if(x<0||y<0||x>=grid.size()||y>=grid.size()){
        return 0;
    }
    if(grid[y][x].seen){
        return 0;
    }
    if(grid[y][x].cow!=id){/*
        if(grid[y][x].cow>id&&find(near[id].begin(),near[id].end(),grid[y][x].cow)==near[id].end()){
            near[id].push_back(grid[y][x].cow);
        }*/
        return 0;
    }
    int ret=1;
    grid[y][x].seen=true;
    ret+=floodFill(x+1,y,id);
    ret+=floodFill(x-1,y,id);
    ret+=floodFill(x,y+1,id);
    ret+=floodFill(x,y-1,id);
    return ret;
}

int main() {
    ofstream fout ("multimoo.out");
    ifstream fin ("multimoo.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> splitln=split(inputstrings[1]," ");
    for(int i=1;i<inputstrings.size();i++){
        grid.push_back({});
        vector<string> splitln=split(inputstrings[i]," ");
        for(int k=0;k<splitln.size();k++){
            auto found=find(ids.begin(),ids.end(),stoi(splitln[k]));
            int id=found-ids.begin();
            if(found==ids.end()){
                ids.push_back(stoi(splitln[k]));
                id=ids.size()-1;
            }
            grid[i-1].push_back(Block(id));
        }
    }
    int largest=0;
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid[y].size();x++){
            if(!grid[y][x].seen){
                int res=floodFill(x,y,grid[y][x].cow);
                largest=max(largest,res);
            }
//            cout << grid[y][x].cow << " ";
        }
//        cout << endl;
    }
    fout << largest<<endl<< endl;
    return 0;
}