#include "MotifFinder.h"
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

// Constructor
MotifFinder::MotifFinder() {}

// Compare function for sorting (highest count first)
bool compareMotifs(const MotifResult& a, const MotifResult& b) {
    return a.count > b.count;
}

// Main function to find frequent motifs
vector<MotifResult> MotifFinder::findFrequentMotifs(
    const string& sequence,
    int k,
    int minFreq
) {
    vector<MotifResult> results;

    if (sequence.length() < k)
        return results;

    unordered_map<long long, int> motifCounts;
    unordered_map<long long, vector<string>> hashBuckets;
    
    deque<char> windowQ;
    long long hash =0;
    
    //first window
    for (int i =0 ; i< k ;i++)
    	windowQ.push_back(sequence[i]);
    	
    string windowStr(windowQ.begin() , windowQ.end());
	hash = hasher.computeHash(windowStr);

    motifCounts[hash]++;
    hashBuckets[hash].push_back(windowStr);
    
    //sliding the window:
    for (int i =k ; i <sequence.length() ; i++){
    	char oldChar = windowQ.front();
    	windowQ.pop_front();
    	
    	char newChar = sequence[i];
    	windowQ.push_back(newChar);
    	
    	hash = hasher.rollHash(hash, oldChar, newChar, k);
    	
    	string current(windowQ.begin() , windowQ.end());
    	motifCounts[hash]++;
    	hashBuckets[hash].push_back(current);
	}
    
   
    int totalWindows = sequence.length() - k + 1;

    unordered_map<long long, int>::iterator it;
    
    for (it = motifCounts.begin(); it != motifCounts.end(); ++it) {
        if (it->second >= minFreq) {
        	unordered_map<string , int> exactCount;
        	
        	vector<string>:: iterator vIt;
        	
        	for (vIt = hashBuckets[it->first].begin(); vIt != hashBuckets[it->first].end(); ++vIt){
        		exactCount[*vIt]++;
			}
			
			unordered_map<string , int> :: iterator eIt;
			for (eIt = exactCount.begin() ; eIt != exactCount.end(); ++eIt){
				if (eIt->second >= minFreq){
					MotifResult r;
					r.motif = eIt->first;
					r.count = eIt->second;
					r.freq = (eIt->second * 100.0) / totalWindows;
					results.push_back(r); 
				}
			}
        }
    }

    // Sort by count descending
    sort(results.begin(), results.end(), compareMotifs);

    return results;
}
