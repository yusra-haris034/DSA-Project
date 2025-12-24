//header file
#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct SequenceMetaData{
	int id;
	string name;
	int length;
};

class SequenceStore{
	vector <string> sequences; //for dna sequence
	vector <SequenceMetaData> metaData; // stores meta data
	
	public:
		SequenceStore();
		int addSequence(const string& seq ,const string& name);
		string getSequence (int id) const;
		const vector<string>& getAllSequences();
		int getSequenceCount() const;
		void clear();
		string cleanSequence(const string& seq);
		const vector <SequenceMetaData>& getMetaData() const;
};