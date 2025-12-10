#include "SuffixTrie.h"

SuffixTrie::SuffixTrie() {
    root = new TrieNode();  // Create root
}

SuffixTrie::~SuffixTrie() {
    delete root; // Automatically deletes all nodes (recursive)
}

// Insert the suffix starting at startPos
void SuffixTrie::insert(const std::string& sequence, int startPos) {
    TrieNode* current = root;

    for (int i = 0; i < sequence.length(); i++) {
        char c = sequence[i];

        // If child does not exist, create it
        if (!current->hasChild(c)) {
            current->addChild(c, new TrieNode());
        }

        // Move to the child node
        current = current->getChild(c);

        // Store exact position of this character
        current->addPosition(startPos + i);
    }

    // Mark last node as a pattern end
    current->isEnd = true;
}

// Search pattern inside the trie
std::vector<int> SuffixTrie::search(const std::string& pattern) {
    TrieNode* current = root;

    for (int i = 0; i < pattern.length(); i++) {
        char c = pattern[i];

        // Pattern not found
        if (!current->hasChild(c)) {
            return {};
        }
        current = current->getChild(c);
    }

    // Adjust positions: convert ending positions ? starting positions
    std::vector<int> result;
    for (int endPos : current->positions) {
        result.push_back(endPos - (pattern.length() - 1));
    }

    return result;
}

