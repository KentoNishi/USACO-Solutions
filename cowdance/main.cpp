/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: cowdance
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

int findMin(vector<int> arr){
    int index=0;
    for(int i=1;i<arr.size();i++){
        if(arr[i]<arr[index]){
            index=i;
        }
    }
    return index;
}

int findMax(vector<int> arr){
    int index=0;
    for(int i=1;i<arr.size();i++){
        if(arr[i]>arr[index]){
            index=i;
        }
    }
    return index;
}
int maximum;
vector<int> cows;

int possible(int k){
    vector<int> stage;
    vector<int> queue=cows;
    for(int i=0;i<k;i++){
        stage.push_back(queue[0]);
        queue.erase(queue.begin());
    }
    while(queue.size()>0){
        int index=findMin(stage);
        stage[index]+=queue[0];
        queue.erase(queue.begin());
        if(stage[index]>maximum){
            return false;
        }
    }
    return true;
}

int main() {
    ofstream fout ("cowdance.out");
    ifstream fin ("cowdance.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    maximum=stoi(firstLine[1]);
    for(int i=1;i<inputstrings.size();i++){
        cows.push_back(stoi(inputstrings[i]));
    }
    int left=1;
    int right=cows.size();
    while(left!=right){
        int mid=(left+right)/2;
        if(possible(mid)){
            right=mid;
        }else{
            left=mid+1;
        }
    }
    fout << left << endl;
    return 0;
}