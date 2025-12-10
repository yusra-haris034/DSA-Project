#ifndef SUFFIXTRIE_H
#define SUFFIXTRIE_H

#include "TrieNode.h"
#include <string>
#include <vector>

class SuffixTrie {
private:
    TrieNode* root;

public:
    SuffixTrie();                     // Constructor
    ~SuffixTrie();                    // Destructor
    void insert(const std::string& sequence, int startPos); 
    std::vector<int> search(const std::string& pattern);
};

#endif

