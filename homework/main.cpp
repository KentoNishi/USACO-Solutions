/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: homework
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

int main() {
    ofstream fout ("homework.out");
    ifstream fin ("homework.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> splitqs=split(inputstrings[1]," ");
    vector<int> questions;
    for(int i=0;i<splitqs.size();i++){
        questions.push_back(stoi(splitqs[i]));
    }
    int size=questions.size();
    int total=questions[size-1];
    int minimum=questions[size-1];
    float maximum;
    vector<int> outputs;
    for(int i=size-2;i>0;i--){
        minimum=min(minimum,questions[i]);
        total+=questions[i];
//        cout << "Eating "<<i<<", at "<<float(total-minimum)/(size-i-1)<<". Max is "<<maximum<<endl;
        if(float(total-minimum)/(size-i-1)==float(maximum)){
            outputs.push_back(i);
        }else if(float(total-minimum)/(size-i-1)>float(maximum)){
            outputs={i};
            maximum=float(total-minimum)/(size-i-1);
        }
//        cout<<i<<" " << minimum << "/" << total << endl;
    }
    string out="";
    for(int i=outputs.size()-1;i>=0;i--){
        out+=to_string(outputs[i])+"\n";
    }
    fout << out;
    
    /*
    long long total=questions[questions.size()-1];
    int minimum=questions[questions.size()-1];
    int maximum=0;
    vector<int> outputs;
    for(int i=1;i<questions.size()-1;i++){
        minimum=min(minimum,questions[questions.size()-1-i]);
        total+=questions[questions.size()-1-i];
        cout <<"Ate "<<questions.size()-i-1<<" problems. "<< total << " total, "<<minimum << " minimum. "<<float(total-minimum)<<"/"<<i<<"="<< float(total-minimum)/i;
        if(float(total-minimum)/i>maximum){
            maximum=float(total-minimum)/i;
            cout << " MAX!!!"<< endl;
            outputs={questions.size()-i-1};
        }else if(float(total-minimum)/i==maximum){
            outputs.push_back(questions.size()-i-1);
            cout << " TIE!!!"<< endl;
        }
        cout << endl;
    }
    string out="";
    for(int i=0;i<outputs.size();i++){
        out+=to_string(outputs[outputs.size()-i-1]);
        out+="\n";
    }
    fout << out;*/
    return 0;
}