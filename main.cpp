/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>  // Include necessary header files
#include <chrono>          // Include for timing

using namespace std;
using namespace std::chrono;

// Trie Node structure
struct Node {
    Node* children[26]; // Array to store children nodes
    bool isEndFlag;     // Flag to mark end of a word

    // Constructor
    Node() {
        // Initialize children array to NULL
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        // Initialize isEndFlag to false
        isEndFlag = false;
    }

    // Check if a node has children with given character
    bool hasChildren(char ch) {
        return children[ch - 'a'] != nullptr;
    }

    // Get child node corresponding to given character
    Node* getChild(char ch) {
        return children[ch - 'a'];
    }

    // Insert a child node with given character
    void insert(char ch, Node* childNode) {
        children[ch - 'a'] = childNode;
    }

    // Check if the node marks end of a word
    bool isEnd() {
        return isEndFlag;
    }

    // Set the node as end of a word
    void setEnd() {
        isEndFlag = true;
    }

    // Unset the node as end of a word
    void unsetEnd() {
        isEndFlag = false;
    }
};

// Class for finding longest compound words
class CompoundWordFinder {
    Node* root; // Root node of the trie

public:
    // Constructor
    CompoundWordFinder() {
        root = new Node(); // Initialize root node
    }

    // Comparator function for sorting strings by length
    static bool comparator(string str1, string str2) {
        if (str1.length() == str2.length()) {
            return str1 < str2;
        }
        return str1.length() > str2.length();
    }

    // Insert a word into the trie
    void pushWord(string word) {
        Node* node = root;
        // Traverse through the word
        for (char ch : word) {
            // If current character is not present in trie, insert it
            if (!node->hasChildren(ch)) {
                node->insert(ch, new Node());
            }
            // Move to the child node
            node = node->getChild(ch);
        }
        // Mark end of the word
        node->setEnd();
    }

    // Reset end flag for a word in the trie
    void resetFlag(string str, int index, Node* tempNode) {
        // If end of word is reached, unset end flag
        if (index == str.length()) {
            tempNode->unsetEnd();
            return;
        }
        // Recursively call for next character
        resetFlag(str, index + 1, tempNode->getChild(str[index]));
    }

    // Check if a string can be formed by concatenating other words in the trie
    bool compoundTrue(string str, int index, Node* tempNode) {
        // If end of string is reached, check if current node marks end of a word
        if (index == str.length()) {
            return tempNode->isEnd();
        }
        // If current node marks end of a word
        if (tempNode->isEnd()) {
            // Check if remaining string can be formed from root
            if (compoundTrue(str, index, root)) {
                return true;
            }
        }
        // If current character has children
        if (tempNode->hasChildren(str[index])) {
            // Recursively check for next character
            return compoundTrue(str, index + 1, tempNode->getChild(str[index]));
        } else {
            // No matching child found
            return false;
        }
    }

    // Find and display the longest and second longest compound words
    void findLongestWords(vector<string>& words) {
        vector<string> answer;
        // Iterate through the words
        for (int i = 0; i < words.size(); i++) {
            answer.push_back(words[i]);
            // Insert word into trie
            pushWord(words[i]);
        }
        // Sort words by length
        sort(answer.begin(), answer.end(), comparator);
        string longestWord = "", secondLongestWord = "";
        // Iterate through sorted words
        for (int i = 0; i < answer.size(); i++) {
            // Reset end flag for current word
            resetFlag(answer[i], 0, root);
            // Check if word is compound
            if (compoundTrue(answer[i], 0, root)) {
                // If longest word is not set
                if (longestWord.empty()) {
                    longestWord = answer[i];
                } else {
                    // Set second longest word and break loop
                    secondLongestWord = answer[i];
                    break;
                }
            }
            // Reinsert word into trie
            pushWord(answer[i]);
        }
        // Display longest and second longest compound words
        cout << "Longest_word : " << longestWord << endl;
        cout << "Second_longest_word : " << secondLongestWord << endl;
    }
};

int main() {
    // Create instance of CompoundWordFinder
    CompoundWordFinder finder;
    // Read input from file
    fstream file;
    vector<string> wordList;
    file.open("Input_01.txt", ios::in);
    if (file.fail()) {
        cout << "Failed to open the file."; // Handle file opening failure
    } else {
        string word;
        // Read words from file
        while (file >> word) {
            wordList.push_back(word);
        }
        // Close file
        file.close();
        // Start time measurement
        auto start_timer = high_resolution_clock::now();
        // Find longest and second longest compound words
        finder.findLongestWords(wordList);
        // End time measurement
        auto end_timer = high_resolution_clock::now();
        auto total_time = duration_cast<milliseconds>(end_timer - start_timer);
        // Display time taken
        cout << "Time for executing the input file:: " << total_time.count() << " ms" << endl;
    }
    return 0;
}
