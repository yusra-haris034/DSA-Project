#pragma once
#include "RollingHash.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct MotifResult{
	string motif;
	int count;
	double freq;
};

class MotifFinder{
	private:
		RollingHash hasher;
	public:
		MotifFinder();
		
		vector<MotifResult> findFrequentMotifs(
			const string& sequence,
			int k,
			int minFreq = 2
		);
};