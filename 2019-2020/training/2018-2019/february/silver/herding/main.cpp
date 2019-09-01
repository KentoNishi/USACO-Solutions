// herding - Silver - February 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=918

/*
    Summary:
        Given a list of occupied locations on a 1-dimentional line,
        find the minimum and maximum number of moves required to 
        "cluster" them into one continuous segment. Moves are 
        permitted only if the object being moved has either the 
        largest or smallest index. Objects cannot remain or become
        the largest or smallest index after a move.
    Solution:
        Maximum:
            If there are k "gaps":
                Find the maximum number of empty spots in:
                    First and last k-1 gaps
        Minimum:
            Find the least amount of empty spots in a continuous 
            strip of N elements using a prefix sum.

*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ofstream fout("herding.out");
    ifstream fin("herding.in");
    int N;
    /*
        N: number of cows
    */
    fin >> N;
    vector<int> cows=vector<int>(N);
    for(int i=0;i<N;i++){
        int cow;
        fin >> cow;
        cows[i]=cow-1;
    }
    sort(cows.begin(),cows.end());
    int maximum=0;
    // (number of total spots in the segment)-(number of 1s in the segment)
    // (cows[N-2]-cows[0]-1)-(N-3) = cows[N-2]-cows[0]-N+2
    maximum=max(maximum,cows[N-2]-cows[0]-N+2);
    maximum=max(maximum,cows[N-1]-cows[1]-N+2);
    int minimum=maximum;
    for(int cowIndex=0;cowIndex<N;cowIndex++){
        int maximumRightBound=cowIndex+N-1;
        int rightBound=cowIndex+1;
        while(rightBound < N && cows[rightBound] - cows[cowIndex] + 1 < N){
            rightBound++;
        }
        if(cows[rightBound] - cows[cowIndex] + 1 >= N){
            int trialMoves = cows[rightBound] - cows[cowIndex] + 1;
            trialMoves-= rightBound - cowIndex + 1;
//            cout << cowIndex << " " << rightBound << " " << trialMoves << endl;
            minimum=min(minimum, trialMoves);
        }
    }
    fout << minimum << endl << maximum << endl;
    return 0;
}