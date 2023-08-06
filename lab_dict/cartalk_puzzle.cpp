/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    map<string, string> words;
    string word;
    // get all words in a map
    if(wordsFile.is_open()){
        while(getline(wordsFile, word)){
            // check 2 char special case
            if(word.length() <= 2){
                continue;
            }
            if(words.find(word) == words.end()){
                words[word] = word;
            }
        }
    }

    // check each word in the vector
    for(const std::pair<string, string> pair : words){
        word = pair.first;
        string potential_word1 = word.substr(0,1) + word.substr(2);
        string potential_word2 = word.substr(1);
        if(d.homophones(word, potential_word1) && d.homophones(word, potential_word2)){
            tuple<string, string, string> ans(word, potential_word1, potential_word2);
            ret.push_back(ans); 
        }
    }
    wordsFile.close();
    return ret;
}
