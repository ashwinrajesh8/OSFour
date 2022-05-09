#include <algorithm>        /*Ashwin Rajesh OS Program 4*/
#pragma GCC optimize("Ofast")           // optimize runtime for competition bonus
class PRDS_MRU {
public:
    vector<int> store;
    PRDS_MRU(int count){}
};

int Page_Replacement_MRU(vector<int>& pages, int nextpage, PRDS_MRU *p){
    int counter = 0;                // initialize counter variable
    int positiveNextPage = abs(nextpage);       // create instance of absolute nextpage to avoid constant redeclaration
    vector<int> mostRecentlyUsed;           //  this vector will keep track of the most recently used pages
    p->store.push_back(positiveNextPage); // push back next page instance

    for(vector<int>::iterator it = pages.begin(); it != pages.end(); ++it){     // iterate through all pages
        if(positiveNextPage == abs(*it)){ return -1; }      // return -1 if already in vector
        if(*it == 0){ return counter; }                     // return index (via counter) if space is free
        counter++;
    }
    for(vector<int>::iterator it = pages.begin(); it != pages.end(); ++it) {        // parse through all pages, check which has the most ideal priority weight for most recent use
        int priorityWeight = 0;
        for(std::vector<int>::reverse_iterator rit = p->store.rbegin(); rit!= p->store.rend(); ++rit) {
            if(abs(*it) == *rit) {
                mostRecentlyUsed.push_back(priorityWeight); // vector position corresponds in parallel manner with index of page
                break;
            } else { priorityWeight++; }        // increment weight to indicate time since usage
        }
    }
    return std::min_element(mostRecentlyUsed.begin(), mostRecentlyUsed.end()) - mostRecentlyUsed.begin();    // find minimum recentlyUsed (representing the most recently used page based on our priority weights) and return the index to it
}