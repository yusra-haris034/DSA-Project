#include <iostream>
#include <vector>
#include <string>
#include "SuffixTrie.h"
#include "RollingHash.h"
#include "SequenceStore.h"
#include "MotifFinder.h"

using namespace std;

int main() {

    // ================= SuffixTrie Demo =================
    cout << "===== SUFFIX TRIE PATTERN SEARCH =====" << endl << endl;

    SuffixTrie trie;
    string text;
    cout << "Enter DNA Sequence for SuffixTrie (A C G T only): ";
    cin >> text;

    // Insert all suffixes
    for (int i = 0; i < text.length(); i++) {
        trie.insert(text.substr(i), i);
    }

    string pattern;
    cout << "Enter pattern to search: ";
    cin >> pattern;

    vector<int> positions = trie.search(pattern);
    if (positions.empty()) {
        cout << "Pattern NOT found.\n";
    } else {
        cout << "Pattern found at positions: ";
        for (int p : positions) cout << p << " ";
        cout << endl;
    }

    cout << endl << "================================" << endl << endl;


    // ================= RollingHash Demo =================
    cout << "===== ROLLING HASH =====" << endl << endl;

    RollingHash rh;
    string dna = "ACGTAC";
    int window = 3;

    cout << "DNA string: " << dna << endl;
    cout << "Window size: " << window << endl << endl;

    string firstWindow = dna.substr(0, window);
    long long h = rh.computeHash(firstWindow);

    cout << "Initial window: " << firstWindow << " | Hash: " << h << endl;

    for (int i = 1; i <= dna.length() - window; i++) {
        char oldChar = dna[i - 1];
        char newChar = dna[i + window - 1];

        h = rh.rollHash(h, oldChar, newChar, window);
        string current = dna.substr(i, window);
        cout << "Window: " << current << " | Hash: " << h << endl;
    }

    cout << endl << "BASE^5 % MOD = " << rh.power(5) << endl;

    cout << endl << "================================" << endl << endl;


    // ================= SequenceStore Demo =================
    cout << "===== SEQUENCE STORE =====" << endl << endl;

    SequenceStore store;
    int id1 = store.addSequence("aCgTxx12", "Sample 1");
    int id2 = store.addSequence("TTAGGC", "Sample 2");
    int id3 = store.addSequence("ccgatta", "Sample 3");

    cout << "Stored sequences count: " << store.getSequenceCount() << endl;
    cout << "Sequence with ID " << id1 << ": " << store.getSequence(id1) << endl;
    cout << "Sequence with ID " << id2 << ": " << store.getSequence(id2) << endl;
    cout << "Sequence with ID " << id3 << ": " << store.getSequence(id3) << endl;

    cout << "All sequences:" << endl;
    const vector<string>& allSeq = store.getAllSequences();
    for (int i = 0; i < allSeq.size(); i++) {
        cout << i << ": " << allSeq[i] << endl;
    }

    store.clear();
    cout << "Sequences after clear: " << store.getSequenceCount() << endl;

    cout << endl << "================================" << endl << endl;


    // ================= MotifFinder Demo =================
    cout << "===== MOTIF FINDER =====" << endl << endl;

    string seq = "ACGTACGTACGTAC";
    int k = 3;
    int minFreq = 2;

    MotifFinder finder;
    vector<MotifResult> motifs = finder.findFrequentMotifs(seq, k, minFreq);

    cout << "Sequence: " << seq << endl;
    cout << "Motifs of length " << k << " occurring at least " << minFreq << " times:" << endl;

    for (auto &m : motifs) {
        cout << m.motif << " | Count: " << m.count << " | Frequency: " << m.freq << "%" << endl;
    }

    cout << endl << "===== END OF TEST =====" << endl;

    return 0;
}
