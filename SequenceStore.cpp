#include "SequenceStore.h"
#include <cctype>

SequenceStore::SequenceStore(){}
	
int SequenceStore::addSequence(const string& seq , const string& name){
	string cleaned = cleanSequence(seq);
		int id = sequences.size();
			
		sequences.push_back(cleaned);
			
		SequenceMetaData meta;
		meta.id= id;
		meta.name = name;
		meta.length = cleaned.length();
			
		metaData.push_back(meta);
	return id;
			
}
	
const vector<SequenceMetaData>& SequenceStore :: getMetaData() const{
	return metaData;
}
	
string SequenceStore::getSequence (int id) const{
	if (id < 0 || id >= sequences.size())
		return "";
		
	return sequences[id];	
}


const vector<string>& SequenceStore::getAllSequences(){
	return sequences;
}

int SequenceStore::getSequenceCount() const{
	return sequences.size();
}

void SequenceStore::clear(){
	sequences.clear();
	metaData.clear();
}
	
string SequenceStore::cleanSequence(const string& seq){
	string result;
	for (char c: seq){
		char u = toupper(c);
		
		if ( u == 'A' || u == 'C' || u =='G' || u == 'T'){
			result += u;
		}
	}
	
	return result;
}		
		
	