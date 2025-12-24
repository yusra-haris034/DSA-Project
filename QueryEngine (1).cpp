#include "QueryEngine (1).h"

// constructor
QueryEngine::QueryEngine(SequenceStore* s, SuffixTrie* idx)
{
    store = s;
    index = idx;
}

// edit distance using dynamic programming
int QueryEngine::editDistance(const string& s1, const string& s2)
{
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // base cases
    for(int i = 0; i <= m; i++)
        dp[i][0] = i;

    for(int j = 0; j <= n; j++)
        dp[0][j] = j;

    // fill dp table
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(
                    dp[i - 1][j],          // delete
                    min(dp[i][j - 1],      // insert
                        dp[i - 1][j - 1])  // replace
                );
        }
    }

    return dp[m][n];
}

// exact pattern search
vector<SearchResult> QueryEngine::exactSearch(const string& pattern)
{
    vector<SearchResult> results;
    string pat = pattern;

    // convert to uppercase
    for(int i = 0; i < pat.length(); i++)
        pat[i] = toupper(pat[i]);
        
     const vector<string>& seqs = store->getAllSequences();
	 const vector<SequenceMetaData>& meta = store->getMetaData();

	for (int s =0 ; s < seqs.size(); s++){
		vector<int> pos = index->search(pat);
	
	for ( int p : pos){
		SearchResult r;
		r.seqId = meta[s].id;
		r.seqName = meta[s].name;
		r.position = p;
		r.match = pat;
		r.distance = 0;
		results.push_back(r);
	}
}
return results;
}


// approximate pattern search
vector<SearchResult> QueryEngine::approximateSearch(const string& pattern, int maxDistance)
{
    vector<SearchResult> results;
    string pat = pattern;

    // convert pattern to uppercase
    for(int i = 0; i < pat.length(); i++)
        pat[i] = toupper(pat[i]);

    const vector<string>& seqs = store->getAllSequences();
    const vector<SequenceMetaData>& meta = store->getMetaData();

    for (int s = 0; s < seqs.size(); s++) {
        const string& seq = seqs[s];

        for (int i = 0; i <= seq.length() - pat.length(); i++) {
            string window = seq.substr(i, pat.length());
            int dist = editDistance(pat, window);

            if (dist <= maxDistance) {
                SearchResult r;
                r.seqId = meta[s].id;
                r.seqName = meta[s].name;
                r.position = i;
                r.match = window;
                r.distance = dist;
                results.push_back(r);
            }
        }
    }
    return results;
}

