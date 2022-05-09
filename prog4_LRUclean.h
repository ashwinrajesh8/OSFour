#include <algorithm>        /*Ashwin Rajesh OS Program 4*/
#pragma GCC optimize("Ofast")           // optimize runtime for competition bonus
class PRDS_LRUclean {
   public:
    vector<int> store;
    int size = 0;
    PRDS_LRUclean(int count) { size = count;}
};

int Page_Replacement_LRUclean(vector<int>& pages, int nextpage, PRDS_LRUclean *p){
    p->store.push_back(nextpage);
    p->size = pages.size();
    vector<int> lastUsedPriorityClean(p->size, -1), lastUsedPriorityDirty(p->size, -1);     // we will use these vectors to determine the least recently used clean/dirty page respectively
    int counter = 0, weight = 0;
    int positiveNextPage = abs(nextpage);
    bool allDirty = true;

    for(std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it){
        if(positiveNextPage == abs(*it)){ return -1; }      //  return -1 since it's already in pages
        if(*it == 0){ return counter; }                // page references are from 1 to MAXINT, assume *it returns int, therefor 0 would imply empty space
        counter++;                              // increment counter variable
    } counter = 0;                              // reset counter for next loop

    for(std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it){ // iterate all pages, determine least recently used pages
        if(*it > 0){                            // detect clean pages
            weight = 0;                     // weight will keep track of how many "turns" it has been since a page has been activated, we use this weight to determine priority
            allDirty = false;
            for(std::vector<int>::reverse_iterator rit = p->store.rbegin(); rit!= p->store.rend(); ++rit) { // reverse iterate through pages, determine respective weight for each one
                if(abs(*it) == abs(*rit)) {
                    lastUsedPriorityClean[counter] = weight;
                    break;
                } else { weight++; }
            }
        } weight = p->size-1;               // now min weight is priority, set initial to max
        for(std::vector<int>::reverse_iterator rit = p->store.rbegin(); rit!= p->store.rend(); ++rit) { // reverse iterate through pages, determine respective weight for each one
            if(abs(*it) == abs(*rit)) {
                lastUsedPriorityDirty[counter] = weight;
                break;
            } else { weight--; }            // decrease weight such that the lowest weight is the least recently used
        } counter++;
    }
    if (!allDirty) { return std::max_element(lastUsedPriorityClean.begin(), lastUsedPriorityClean.end()) - lastUsedPriorityClean.begin(); }   // this condition, if true, implies that all the pages are dirty and we have to replace a dirty page since there are no clean alternatives ||  find maximum lastUsedPriority (representing the least recently used clean page based on our priority weights) and return the index to it
    else { return std::min_element(lastUsedPriorityDirty.begin(), lastUsedPriorityDirty.end()) - lastUsedPriorityDirty.begin(); }   // find minimum lastUsedPriority (representing the least recently used dirty page based on our priority weights) and return the index to it
}