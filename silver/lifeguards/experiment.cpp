/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: lifeguards
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    set<int> mySet;
    std::pair<std::set<int>::iterator,bool> ret;
    for(int i=0;i<10;i++){
        ret=mySet.insert(floor(i/2));
        if(ret.second==false){
            mySet.erase(ret.first);
        }
        cout << ret.second<<" "<<*ret.first << endl;
    }
    return 0;
}

//fix vector length 
//fix vector to struct