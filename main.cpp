#include <iostream>
#include <vector>
#include <string>
#include "SuffixTrie.h"
#include "RollingHash.h"
#include "SequenceStore.h"
#include "MotifFinder.h"
#include "QueryEngine (1).h"

using namespace std;

void testSequenceStorage(SequenceStore& store) {
    cout << "===== TEST: Sequence Storage =====\n";
    int id1 = store.addSequence("ACGTGTCAGTACGATCGTACGTTAGCTAGCTGACGTAGCTAGCTGATCGTAC", "Sample DNA 1");
    int id2 = store.addSequence("", "Empty DNA");
    int id3 = store.addSequence("NNNXACGT", "Invalid chars DNA");

    cout << "Total sequences stored: " << store.getSequenceCount() << endl;
    const vector<string>& allSeq = store.getAllSequences();
    for (int i = 0; i < allSeq.size(); i++) {
        cout << "ID " << i << ": " << allSeq[i] << endl;
    }
    cout << "\n";
}

void testSuffixTrie(SuffixTrie& trie, SequenceStore& store) {
    cout << "===== TEST: Suffix Trie =====\n";
    string seq = store.getSequence(0);
    for (int i = 0; i < seq.length(); i++) {
        trie.insert(seq.substr(i), i);
    }

    vector<string> patterns = {"ACG", "TACG", "GATC", "XXX"}; // XXX not present
    for (auto& pattern : patterns) {
        cout << "Searching pattern: " << pattern << endl;
        vector<int> pos = trie.search(pattern);
        if (pos.empty()) cout << "Pattern not found\n";
        else {
            cout << "Pattern found at positions: ";
            for (int p : pos) cout << p << " ";
            cout << endl;
        }
    }
    cout << "\n";
}

void testRollingHash(const string& dna) {
    cout << "===== TEST: Rolling Hash =====\n";
    RollingHash rh;
    int windowSize = 5;

    string firstWindow = dna.substr(0, windowSize);
    long long h = rh.computeHash(firstWindow);
    cout << "Window: " << firstWindow << " | Hash: " << h << endl;

    for (int i = 1; i <= dna.length() - windowSize; i++) {
        char oldChar = dna[i - 1];
        char newChar = dna[i + windowSize - 1];
        h = rh.rollHash(h, oldChar, newChar, windowSize);
        string curr = dna.substr(i, windowSize);
        cout << "Window: " << curr << " | Hash: " << h << endl;
    }
    cout << "\n";
}

void testMotifFinder(const string& dna) {
    cout << "===== TEST: Motif Finder =====\n";
    MotifFinder finder;

    // Normal motif
    int k = 3, minFreq = 2;
    auto motifs = finder.findFrequentMotifs(dna, k, minFreq);
    cout << "Motifs of length " << k << " with frequency >= " << minFreq << endl;
    for (auto& m : motifs) {
        cout << m.motif << " | Count: " << m.count << " | Frequency: " << m.freq << "%\n";
    }

    // Edge cases
    cout << "\n--- Edge Case: Motif longer than sequence ---\n";
    auto emptyMotifs = finder.findFrequentMotifs("ACG", 5, 1);
    if (emptyMotifs.empty()) cout << "Correctly handled: no motifs\n";

    cout << "\n--- Edge Case: Motif length equal to sequence ---\n";
    auto fullMotif = finder.findFrequentMotifs("ACGT", 4, 1);
    for (auto& m : fullMotif) cout << m.motif << " | Count: " << m.count << endl;

    cout << "\n";
}

void testQueryEngine(SequenceStore& store, SuffixTrie& trie) {
    cout << "===== TEST: Query Engine =====\n";
    QueryEngine engine(&store, &trie);

    cout << "--- Exact Search ---\n";
    vector<SearchResult> exact = engine.exactSearch("GTC");
    for (auto& r : exact) {
        cout << "SeqID: " << r.seqId << " | Name: " << r.seqName << " | Pos: " << r.position << " | Match: " << r.match << endl;
    }

    cout << "\n--- Approximate Search (edit distance <= 1) ---\n";
    vector<SearchResult> approx = engine.approximateSearch("GTT", 1);
    for (auto& r : approx) {
        cout << "SeqID: " << r.seqId << " | Name: " << r.seqName << " | Pos: " << r.position
             << " | Match: " << r.match << " | Distance: " << r.distance << endl;
    }

    cout << "\n--- Edge Case: Pattern not present ---\n";
    vector<SearchResult> none = engine.exactSearch("XXX");
    if (none.empty()) cout << "Pattern not found as expected.\n";

    cout << "\n";
}

int main() {
    cout << "========== GENOME TOOL TEST ==========\n\n";

    SequenceStore store;
    testSequenceStorage(store);

    SuffixTrie trie;
    testSuffixTrie(trie, store);

    string dna = store.getSequence(0);
    testRollingHash(dna);
    testMotifFinder(dna);
    testQueryEngine(store, trie);

    cout << "========== END OF EDGE CASE TESTS ==========\n";
    return 0;
}
