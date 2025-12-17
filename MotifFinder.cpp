#include "MotifFinder.h"
#include <algorithm>
#include <unordered_map>

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
    unordered_map<long long, string> hashToMotif;

    string firstWindow = sequence.substr(0, k);
    long long hash = hasher.computeHash(firstWindow);

    motifCounts[hash]++;
    hashToMotif[hash] = firstWindow;
    
    cout << "[DEBUG] First window: " << firstWindow 
         << " | Hash: " << hash 
         << " | Count: " << motifCounts[hash] << endl;

    // Rolling through the sequence
    for (int i = k; i < sequence.length(); i++) {
        char oldChar = sequence[i - k];
        char newChar = sequence[i];

        hash = hasher.rollHash(hash, oldChar, newChar, k);
        motifCounts[hash]++;

        if (hashToMotif.find(hash) == hashToMotif.end()) {
            hashToMotif[hash] = sequence.substr(i - k + 1, k);
        }
        
        cout << "[DEBUG] Window: " << sequence.substr(i - k + 1, k)
             << " | Hash: " << hash 
             << " | Count: " << motifCounts[hash] << endl;
    }

    int totalWindows = sequence.length() - k + 1;

    // Collect results
    unordered_map<long long, int>::iterator it;
    for (it = motifCounts.begin(); it != motifCounts.end(); ++it) {
        if (it->second >= minFreq) {
            MotifResult r;
            r.motif = hashToMotif[it->first];
            r.count = it->second;
            r.freq = (it->second * 100.0) / totalWindows; 
            results.push_back(r);
            
            cout << "[DEBUG] Added Motif: " << r.motif 
                 << " | Count: " << r.count 
                 << " | Freq: " << r.freq << "%" << endl;
        }
    }

    // Sort by count descending
    sort(results.begin(), results.end(), compareMotifs);

    return results;
}
