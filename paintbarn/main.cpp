#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <tuple>
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

struct Paint{
    int x1;
    int y1;
    int x2;
    int y2;
};

int main() {
    ofstream fout ("paintbarn.out");
    ifstream fin ("paintbarn.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int optimal=stoi(firstLine[1]);
    vector<Paint> blobs;
    for(int i=1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        Paint paint=Paint();
        paint.x1=stoi(line[0]);
        paint.y1=stoi(line[1]);
        paint.x2=stoi(line[2]);
        paint.y2=stoi(line[3]);
        blobs.push_back(paint);
    }
    for(int i=0;i<blobs.size()-1;i++){
        vector<vector<int>> grid;
        for(int y=0;y<blobs[i].y2-blobs[i].y1;y++){
            grid.push_back({});
            for(int x=0;x<blobs[i].x2-blobs[i].x1;x++){
                grid[y].push_back(0);
            }
        }
        for(int k=i+1;k<blobs.size();k++){
            if(blobs[i].x1>blobs[k].x1&&blobs[i].y1>blobs[k].y1&&blobs[k].x2>blobs[i].x1&&blobs[k].y2>blobs[i].y1){
                
            }
        }
    }
	return 0;
}