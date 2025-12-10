#ifndef TRIENODE_H
#define TRIENODE_H

#include <unordered_map>   // for storing children
#include <vector>          // for storing positions
#include <string>          // for strings

class TrieNode {
public:
    // Map stores children for characters A, C, G, T
    std::unordered_map<char, TrieNode*> children;

    // Stores all ending positions of the pattern
    std::vector<int> positions;

    // True if this node marks end of a pattern
    bool isEnd;

    TrieNode();                 // Constructor
    ~TrieNode();                // Destructor

    bool hasChild(char c);      // Check if child exists
    TrieNode* getChild(char c); // Return child
    void addChild(char c, TrieNode* node); // Add child
    void addPosition(int pos);  // Store position
};

#endif

