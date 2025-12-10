#include "TrieNode.h"

// Constructor initializes isEnd to false
TrieNode::TrieNode() {
    isEnd = false;
}

// Destructor - deletes all children recursively
TrieNode::~TrieNode() {
    for (auto& pair : children) { // loop through map
        delete pair.second;       // delete child node
    }
}

bool TrieNode::hasChild(char c) {
    return children.find(c) != children.end(); // check existence
}

TrieNode* TrieNode::getChild(char c) {
    if (hasChild(c)) return children[c]; // return existing child
    return nullptr;
}

void TrieNode::addChild(char c, TrieNode* node) {
    children[c] = node; // store child
}

void TrieNode::addPosition(int pos) {
    positions.push_back(pos); // add position
}

