struct compare {
    bool operator()(int a,int b) const { 
        return a < b;
    }
};