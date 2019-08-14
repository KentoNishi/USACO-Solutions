// convention2 - Silver - December 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=859

/*
    Summary:
        Find the maximum waiting time for any cow that arrives.
        Cows are selected by seniority.
    Solution:
        Sort the cows in order of arrival time.
        Have a queue (set) for cows to wait in while the pasture is occupied.
        Find the longest waiting time.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
#include <queue>
using namespace std;

struct Cow{
    int seniority;
    int arrival;
    int duration;
};

struct sortByArrival {
    bool operator()(Cow a, Cow b) const { 
        return a.arrival < b.arrival;
    }
};

struct sortBySeniority {
    bool operator()(Cow a, Cow b) const { 
        return a.seniority > b.seniority;
    }
};

int main() {
    ofstream fout ("convention2.out");
    ifstream fin ("convention2.in");
    int N;
    /*
        N: Number of cows
    */
    fin >> N;
    vector<Cow> cows=vector<Cow>(N);
    for(int i=0;i<N;i++){
        cows[i]=Cow();
        fin>>cows[i].arrival>>cows[i].duration;
        cows[i].seniority=i;
    }
    sort(cows.begin(),cows.end(),sortByArrival());
    // Sort cows by arrival time
    priority_queue<Cow, vector<Cow>, sortBySeniority> queue;
    int timeMarker=0;
    int answer=0;
    for(int currentCow=0;currentCow<N;currentCow){
        // queue is empty!
        int arrivalTime=cows[currentCow].arrival;
        timeMarker=arrivalTime;
        // set the current time to the arrival time
        while(currentCow<N && cows[currentCow].arrival==arrivalTime){
            // get all cows that arrive at the same time 
            queue.push(cows[currentCow]);
            // push them into the queue
            currentCow++;
        }
        while(queue.empty()==false){
            // while there are cows in the queue
            answer=max(answer,timeMarker-queue.top().arrival);
            // check if the current cow's waiting time is the largest
            timeMarker+=queue.top().duration;
            // add the cow's duration at the pasture to the current time
            queue.pop();
            // remove the current cow after finishing
            while(currentCow < N && cows[currentCow].arrival <= timeMarker){
                // get all cows that arrived while the cow was grazing
                queue.push(cows[currentCow]);
                // add the cow to the queue
                currentCow++;
                // check the next cow
            }
        }
    }
    fout << answer << endl;
    return 0;
}