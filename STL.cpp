#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <ctime>
std::string x;
std::string keyword;
int main() {

    std::cout << "Please enter a word: ";// accept user input
    std::cin >> x;
    std::vector<std::string> wordVector;//declare word dictionary vector
    const int NWORDS = 81483;// initializing the pseudo random number generator
    std::default_random_engine dre(time(nullptr));   // Seed the engine 
    std::uniform_int_distribution<int> di(0, NWORDS); // Use uniform distribution 
    int number = di(dre);// Get a random int 
    std::ifstream file("words.txt");// getting the word to form the subwords of
    std::string element;
    while (file >> element) {
        wordVector.emplace_back(std::move(element));//create vector of total words
    }
    if (x.length() > 2) { //determine if user input is acceptable
    	keyword = x;
    } 
    else {keyword = wordVector[number];}
    std::cout << "Your word is: " << keyword << std::endl;
    const auto comparator = // formation of subwords
        [](const std::string& firstWord, const std::string& secondWord) { //organizing subwords
        if (firstWord.length() < secondWord.length()) { //check length of words
        	return true;
        }  else if (firstWord.length() > secondWord.length()) { //check length of words
        	return false;
        }
        return firstWord < secondWord;
    };
    std::set<std::string, decltype(comparator)> subWords(comparator);
    std::sort(keyword.begin(), keyword.end());
    do {
    	for (int q = 3; q <= keyword.length(); ++q) {
    		subWords.insert(keyword.substr(0, q));
    	}
    } 
    while (std::next_permutation(keyword.begin(), keyword.end()));
    for (const std::string& subword : subWords) {// display to the console the subwords
        if (std::count(wordVector.begin(), wordVector.end(), subword)) { //if subword in words.txt
            std::cout << subword << std::endl;//output subword to console
        }
    } return 0; // end
}