#include "rollingHash.h"

RollingHash::RollingHash(){
			baseMap['A'] = 0;
			baseMap['C'] = 1;
			baseMap['G'] = 2;
			baseMap['T'] = 3;
}
		
long long RollingHash::computeHash(const string& str){
			long long hash =0;
	    for(char c: str){
	        c = toupper(c);
	        hash = (hash * BASE + baseMap[c]) % MOD;
	    }
	    return hash;
}
		
long long RollingHash::rollHash(long long oldHash , char oldChar, char newChar, int windowSize){
			oldChar = toupper(oldChar);
    newChar = toupper(newChar);
    long long oldVal = baseMap[oldChar];
    long long newVal = baseMap[newChar];
    long long basePow = 1;
    
    for (int i = 0; i < windowSize - 1; i++) {
        basePow = (basePow * BASE) % MOD;
    }
    
    oldHash = (oldHash - (oldVal * basePow) % MOD + MOD) % MOD;
    oldHash = (oldHash * BASE + newVal) % MOD;
    
    return oldHash;
}
		
long long RollingHash::power(int exp){
			long long result = 1;
    long long b = BASE;
    
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * b) % MOD;
        b = (b * b) % MOD;
        exp /= 2;
    }
    return result;
}