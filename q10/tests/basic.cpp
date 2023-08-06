#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "../lphashtable.h"
#include "../schashtable.h"

#include "../textfile.h"

#include "catchlib.h"

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

	TextFile infile( filename );

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

void testInsert() {

	LPHashTable<string, int> *hashTable;

	ofstream testEasyFile;
	testEasyFile.open("yourTestEasyFile.txt",ios::trunc);

	testEasyFile << "testing Insert with textEasy.txt" << endl;
	hashTable = makeLPHTable<string, int>("textEasy.txt", 16);
	hashTable->printTable(testEasyFile);
	delete hashTable;
	testEasyFile.close();

	ofstream testHardFile;
	testHardFile.open("yourTestHardFile.txt",ios::trunc);
	testHardFile << "testing Insert with textHard.txt" << endl;
	hashTable = makeLPHTable<string, int>("textHard.txt", 25);
	hashTable->printTable(testHardFile);
	delete hashTable;
	testHardFile.close();

	ofstream testVeryHardFile;
	testVeryHardFile.open("yourTestVeryHardFile.txt",ios::trunc);
	testVeryHardFile << "testing Insert with textVeryHard.txt" << endl;
	hashTable = makeLPHTable<string, int>("textVeryHard.txt", 16);
	hashTable->printTable(testVeryHardFile);
	delete hashTable;
	testVeryHardFile.close();
}

void testFindIndex() {

	LPHashTable<string, int> *hashTable;

	ofstream testFindIndexFile;
	testFindIndexFile.open("yourTestFindIndexFile.txt",ios::trunc);

	testFindIndexFile << "testing FindIndex with textEasy.txt" << endl;
	hashTable = makeLPHTable<string, int>("textEasy.txt", 16);
	//hashTable->printTable();
	testFindIndexFile << "Key: 'to' Value: " << hashTable->find("to") << endl;
	testFindIndexFile << "Key: 'belong' Value: " << hashTable->find("belong") << endl;
	delete hashTable;
	testFindIndexFile << endl;

	testFindIndexFile << "testing FindIndex with textHard.txt" << endl;
	hashTable = makeLPHTable<string, int>("textHard.txt", 25);
	//hashTable->printTable();
	testFindIndexFile << "Key: 'has' Value: " << hashTable->find("has") << endl;
	testFindIndexFile << "Key: 'been' Value: " << hashTable->find("been") << endl;
	testFindIndexFile << "Key: 'even' Value: " << hashTable->find("even") << endl;
	delete hashTable;
	testFindIndexFile << endl;

	testFindIndexFile << "testing FindIndex with textVeryHard.txt" << endl;
	hashTable = makeLPHTable<string, int>("textVeryHard.txt", 25);
	//hashTable->printTable();
	testFindIndexFile << "Key: 'threet' Value: " << hashTable->find("threet") << endl;
	testFindIndexFile << "Key: 'ten' Value: " << hashTable->find("ten") << endl;
	testFindIndexFile << "Key: 'enu' Value: " << hashTable->find("enu") << endl;
	delete hashTable;
	testFindIndexFile << endl;

	testFindIndexFile.close();
}

void testResize() {

	LPHashTable<string, int> *hashTable;

	ofstream testResizeFile;
	testResizeFile.open("yourTestResizeFile.txt",ios::trunc);

	hashTable = makeLPHTable<string, int>("textResize.txt", 5);
	hashTable->printTable(testResizeFile);
    testResizeFile << "Table size: " << hashTable->tableSize() << endl;
	testResizeFile << "Key: 'even' Value: " << hashTable->find("even") << endl;
	testResizeFile << "Key: 'further' Value: " << hashTable->find("further") << endl;
	delete hashTable;
	testResizeFile.close();
}

void testDuplicate() {

	LPHashTable<string, int> *hashTable;
	ofstream testDuplicateFile;
	testDuplicateFile.open("yourTestDuplicateFile.txt",ios::trunc);

	hashTable = makeLPHTable<string, int>("textLong.txt", 300);
	hashTable->printTable(testDuplicateFile);
    testDuplicateFile << "Table size: " << hashTable->tableSize() << endl;
	testDuplicateFile << "Key: 'even' Value: " << hashTable->find("even") << endl;
	testDuplicateFile << "Key: 'further' Value: " << hashTable->find("further") << endl;
	delete hashTable;
    testDuplicateFile.close();
}

void testPrintTable() {
	SCHashTable<string, int> *hashTable;
	ofstream testPrintTableFile;
	testPrintTableFile.open("yourTestPrintTableFile.txt",ios::trunc);

	testPrintTableFile << "testing printTable in SCHashTable class" << endl;
	hashTable = makeSCHTable<string, int>("textVeryHard.txt", 16);
	hashTable->printTable(testPrintTableFile);
	delete hashTable;
	testPrintTableFile.close();
}

string readFileIntoString(const char * filename)
{
    ifstream ifile(filename);
    ostringstream buf;
    char ch;
    while(buf&&ifile.get(ch))
        buf.put(ch);
    return buf.str();
}

TEST_CASE("TEST INSERT", "[weight=10]"){
    testInsert();
    string str1 = readFileIntoString("testEasyFile.txt");
    string str2 = readFileIntoString("yourTestEasyFile.txt");
    REQUIRE(str1 == str2);

    str1 = readFileIntoString("testHardFile.txt");
    str2 = readFileIntoString("yourTestHardFile.txt");
    REQUIRE(str1 == str2);

    str1 = readFileIntoString("testVeryHardFile.txt");
    str2 = readFileIntoString("yourTestVeryHardFile.txt");
    REQUIRE(str1 == str2);
}

TEST_CASE("TEST FIND INDEX", "[weight=10]"){
    testFindIndex();
    string str1 = readFileIntoString("testFindIndexFile.txt");
    string str2 = readFileIntoString("yourTestFindIndexFile.txt");
    REQUIRE(str1 == str2);
}

TEST_CASE("TEST RESIZE", "[weight=5]"){
    testResize();
    string str1 = readFileIntoString("testResizeFile.txt");
    string str2 = readFileIntoString("yourTestResizeFile.txt");
    REQUIRE(str1 == str2);
}

TEST_CASE("TEST DUPLICATE", "[weight=5]"){
    testDuplicate();
    string str1 = readFileIntoString("testDuplicateFile.txt");
    string str2 = readFileIntoString("yourTestDuplicateFile.txt");
    REQUIRE(str1.size() == str2.size());
    REQUIRE(str1.compare(str2) == 0);
    
}

TEST_CASE("TEST PRINT TABLE", "[weight=10]"){
    testPrintTable();
    string str1 = readFileIntoString("testPrintTableFile.txt");
    string str2 = readFileIntoString("yourTestPrintTableFile.txt");
    REQUIRE(str1 == str2);
}

int main(int argc, char* argv[])
{
    chdir("tests");

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
}