/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: mootube
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

struct Link{
    int relevancy;
    int video;
};

struct Video{
    vector<Link> related={};
};

struct Question{
    int video;
    int minimum;
};

int  main() {
    ofstream fout ("mootube.out");
    ifstream fin ("mootube.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int N=stoi(firstLine[0]);
    array<Video,5000> videos;
    for(int i=1;i<N;i++){ //each video
        vector<string> currentLine=split(inputstrings[i]," ");
        int child=max(stoi(currentLine[0]),stoi(currentLine[1]));
        int parent=min(stoi(currentLine[0]),stoi(currentLine[1]));
        Link link=Link();
        link.relevancy=stoi(currentLine[2]);
        link.video=child;
        videos[parent].related.push_back(link);
        link.video=parent;
        videos[child].related.push_back(link);
    }
    int Q=stoi(firstLine[1]);
    vector<Question> questions;
    for(int i=N;i<N+Q;i++){
        Question question=Question();
        vector<string> currentLine=split(inputstrings[i]," ");
        question.video=stoi(currentLine[1]);
        question.minimum=stoi(currentLine[0]);
        questions.push_back(question);
    }
    return 0;
}