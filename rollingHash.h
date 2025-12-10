#include<iostream>
#include <string>
#include <cmath>
#include <unordered_map>

using namespace std;

class RollingHash{
	static const int BASE = 4; //for 4 dna bases - A,C,T,G 
	static const long long MOD = 1000000007; //to prevent overflow
	unordered_map<char , int> baseMap; //A-0 , C-1 , G-2 , T-3
	
	public:
		RollingHash();
		
		long long computeHash(const string& str);
		
		long long rollHash(long long oldHash , char oldChar, char newChar, int windowSize);
		
		long long power(int exp);
};