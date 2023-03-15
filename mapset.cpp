#include <fstream>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include "SetList.h"
#include "MapArray.h"

using namespace std;

string to_lower(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main(){
    ifstream stopwords_file("stopwords.txt");
    set<string> stopwords;
    SetList<string> stopwords;
    transform(istream_iterator<string>(stopwords_file), istream_iterator<string>(), inserter(stopwords, stopwords.end()), to_lower);

    ifstream document("sample_doc.txt");map<string, int> word_counts;
    MapArray<string, int> word_counts;
    for_each(istream_iterator<string>(document), istream_iterator<string>(), [&](string word){
        word = to_lower(word);
        if (stopwords.find(word) == stopwords.end()){
            word_counts[word]++;
        }
    });

    ofstream output("frequency.txt");
    for (auto const& [word, count] : word_counts){
        output << word << ' ' << count << '\n';
    }
}