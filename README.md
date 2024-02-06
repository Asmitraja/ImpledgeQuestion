# ImpledgeQuestion : Longest Compound Word Finder

# Abstract
The Longest Compound Word Finder is a C++ program that efficiently identifies the longest and second-longest compound words within a given list of words. Utilizing a Trie data structure, the program sorts words by length and lexicographic order, facilitating optimized compound word detection. This document presents a concise summary of the program's execution steps, approach, implementation, time complexity analysis, and code execution flow.
# Execution Steps
1. Clone the repository to the local machine.
2. Open the project in a C++ development environment.
3. Compile and execute the LongestCompoundWordMain.cpp file.
4. Ensure input files are in the same directory.
5. Update the input file name in LongestCompoundWordMain.cpp.
6. Run the program to display output in the console.
# Approach
1. Sorting input words by length and lexicographic order.
2. Iteratively identifying the longest compound word by checking its formation from other words in the sorted list.
3. Replicating the process to find the second-longest compound word.
# Implementation
1. Reading input from a file and storing it in a vector.
2. Using the findLongestCompoundWords function to identify compound words.
3. Employing a Trie data structure for efficient word management.
4. Setting flags to track word suitability for compound word formation.
# Time Complexity
The average time complexity of the solution is approximately O(N * L), where N is the number of words and L is the average word length.
# Code Execution Flow
1. Initializing a Trie data structure to manage words efficiently.
2. Reading words from an input file and inserting them into the Trie.
3. Sorting the word list based on length and lexicographic order.
4. Iterating through the sorted list to check compound word formation.
5. Identifying the longest and second-longest compound words.
6. Recording processing time and displaying results.

