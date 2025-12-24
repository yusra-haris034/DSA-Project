
#include <iostream>
#include <vector>
#include <string>

#include "SuffixTrie.h"
#include "RollingHash.h"
#include "SequenceStore.h"
#include "MotifFinder.h"
#include "QueryEngine (1).h"

using namespace std;

int main() {

    cout << "========== GENOME TOOL TEST ==========\n\n";

    // ================= REALISTIC DNA STRING =================
    string realDNA = "ACGTGTCAGTACGATCGTACGTTAGCTAGCTGACGTAGCTAGCTGATCGTAC";

    // ================= SEQUENCE STORE =================
    cout << "===== SEQUENCE STORE =====\n\n";

    SequenceStore store;
    int id1 = store.addSequence(realDNA, "Sample DNA 1");
    int id2 = store.addSequence("TTAGGCACGT", "Sample DNA 2");
    int id3 = store.addSequence("CCGATTAAGC", "Sample DNA 3");

    cout << "Total sequences stored: " << store.getSequenceCount() << endl;

    const vector<string>& allSeq = store.getAllSequences();
    for (int i = 0; i < allSeq.size(); i++) {
        cout << "ID " << i << ": " << allSeq[i] << endl;
    }

    cout << "\n=====================================\n\n";

    // ================= SUFFIX TRIE =================
    cout << "===== SUFFIX TRIE (EXACT SEARCH) =====\n\n";

    SuffixTrie trie;

    // insert all suffixes of FIRST sequence
    string seq = store.getSequence(0);
    for (int i = 0; i < seq.length(); i++) {
        trie.insert(seq.substr(i), i);
    }

    string pattern = "ACG";
    cout << "Searching pattern: " << pattern << endl;

    vector<int> positions = trie.search(pattern);
    if (positions.empty()) {
        cout << "Pattern not found\n";
    } else {
        cout << "Pattern found at positions: ";
        for (int i = 0; i < positions.size(); i++) {
            cout << positions[i] << " ";
        }
        cout << endl;
    }

    cout << "\n=====================================\n\n";

    // ================= ROLLING HASH =================
    cout << "===== ROLLING HASH =====\n\n";

    RollingHash rh;
    int windowSize = 5;

    cout << "DNA: " << realDNA << endl;
    cout << "Window size: " << windowSize << endl;

    string firstWindow = realDNA.substr(0, windowSize);
    long long h = rh.computeHash(firstWindow);

    cout << "Window: " << firstWindow << " | Hash: " << h << endl;

    for (int i = 1; i <= realDNA.length() - windowSize; i++) {
        char oldChar = realDNA[i - 1];
        char newChar = realDNA[i + windowSize - 1];
        h = rh.rollHash(h, oldChar, newChar, windowSize);

        string curr = realDNA.substr(i, windowSize);
        cout << "Window: " << curr << " | Hash: " << h << endl;
    }

    cout << "BASE^5 % MOD = " << rh.power(windowSize) << endl;

    cout << "\n=====================================\n\n";

    // ================= MOTIF FINDER =================
    cout << "===== MOTIF FINDER =====\n\n";

    MotifFinder finder;
    int k = 3;
    int minFreq = 2;

    vector<MotifResult> motifs = finder.findFrequentMotifs(realDNA, k, minFreq);

    cout << "Motifs of length " << k << " with frequency >= " << minFreq << endl;

    for (int i = 0; i < motifs.size(); i++) {
        cout << motifs[i].motif
             << " | Count: " << motifs[i].count
             << " | Frequency: " << motifs[i].freq << "%\n";
    }

    cout << "\n=====================================\n\n";

    // ================= QUERY ENGINE =================
    cout << "===== QUERY ENGINE =====\n\n";

    QueryEngine engine(&store, &trie);

    cout << "--- Exact Search ---\n";
    vector<SearchResult> exact = engine.exactSearch("GTC");

    for (int i = 0; i < exact.size(); i++) {
        cout << "SeqID: " << exact[i].seqId
             << " | Name: " << exact[i].seqName
             << " | Pos: " << exact[i].position
             << " | Match: " << exact[i].match << endl;
    }

    cout << "\n--- Approximate Search (edit distance <= 1) ---\n";
    vector<SearchResult> approx = engine.approximateSearch("GTT", 1);

    for (int i = 0; i < approx.size(); i++) {
        cout << "SeqID: " << approx[i].seqId
             << " | Name: " << approx[i].seqName
             << " | Pos: " << approx[i].position
             << " | Match: " << approx[i].match
             << " | Distance: " << approx[i].distance << endl;
    }

    cout << "\n========== END OF TEST ==========\n";

    return 0;
}
