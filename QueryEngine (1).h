#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>

#include "SequenceStore.h"
#include "SuffixTrie.h"

using namespace std;

// structure to store search result
struct SearchResult
{
    int seqId;           // sequence id
    string seqName;      // sequence name
    int position;        // position of match
    string match;        // matched string
    int distance;        // edit distance
};

class QueryEngine
{
private:
    SequenceStore* store;   // pointer to sequence store
    SuffixTrie* index;      // pointer to suffix trie

public:
    QueryEngine(SequenceStore* s, SuffixTrie* idx);

    vector<SearchResult> exactSearch(const string& pattern);

    vector<SearchResult> approximateSearch(
        const string& pattern, int maxDistance);

    int editDistance(const string& s1, const string& s2);
};

#endif

