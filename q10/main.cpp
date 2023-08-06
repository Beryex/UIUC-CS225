#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include <string>

#include "textfile.h"

using namespace std;

template <class K, class V>
LPHashTable<K, V> *makeLPHTable(const string filename, const unsigned ts) {

	TextFile infile( filename );

	LPHashTable<K, V> *hashTable = new LPHashTable<K, V>(ts);

	int val = 0;
	while( infile.good() ) {
		string word = infile.getNextWord();
		if (word != "") {
			val++;
			hashTable->insert(word, val);
		}
	}

	return hashTable;
}


template <class K, class V>
SCHashTable<K, V> *makeSCHTable(const string filename, const unsigned ts) {

	TextFile infile(filename);

	SCHashTable<K, V> *hashTable = new SCHashTable<K, V>(ts);

	int val = 0;
	while( infile.good() ) {
		string word = infile.getNextWord();
		if (word != "") {
			val++;
			hashTable->insert(word, val);
		}
	}

	return hashTable;
}

int main() {
	// Do anything you want here
}


