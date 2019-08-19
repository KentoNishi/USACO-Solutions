// mountains - Silver - January 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=896

/*
    Summary:
        Given a list of mountain peaks, find how many mountains
        are visible from a fixed 2D panorama.
    Solution:
        Sort the given list by the left bottom corner of the mountain.
        Keep a record of the maximum right corner value.
        Make sure the mountain does not coincide with adjacent mountains
        If mountain right corner is more:
            Mountain is visible
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Mountain{
    int peakX;
    int peakY;
    int left;
    int right;
    Mountain(int x, int y){
        peakX=x;
        peakY=y;
        left=x-y;
        right=x+y;
    }
};

struct sortByLeft {
    bool operator()(Mountain a, Mountain b) const { 
        return a.left < b.left;
    }
};

int main() {
    ofstream fout("mountains.out");
    ifstream fin("mountains.in");
    int N;
    /*
        N: Number of mountains
    */
    fin >> N;
    vector<Mountain> mountains;
    for(int i=0;i<N;i++){
        int x,y;
        fin >> x >> y;
        mountains.push_back(Mountain(x,y));
    }
    sort(mountains.begin(),mountains.end(),sortByLeft());
    int maxRight=NULL;
    int visible=0;
    for(int i=0;i<mountains.size();i++){
        if(i>0 && mountains[i-1].left == mountains[i].left || 
        mountains[i-1].right == mountains[i].right ){
            continue;
        }
        if(maxRight==NULL || mountains[i].right>maxRight){
            visible++;
            maxRight=mountains[i].right;
        }
    }
    fout << visible << endl;
    return 0;
}