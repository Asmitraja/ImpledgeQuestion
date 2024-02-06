#include <bits/stdc++.h>		// Include necessary header files

 using namespace std;

using namespace std::chrono;

 
struct Node
{
  
	Node *
	children[26];				// Array to store children nodes
  bool
	isEndFlag;					// Flag to mark end of a word
  
	// Check if a node has children with given character
	bool
  hasChildren (char ch)
  {
	
return children[ch - 'a'] != NULL;
  
}
   

	// Get child node corresponding to given character
	Node *
  getChild (char ch)
  {
	
return children[ch - 'a'];
  
}
  
 
	// Insert a child node with given character
	void
  insert (char ch, Node * childNode)
  {
	
children[ch - 'a'] = childNode;
  
} 
 
	// Check if the node marks end of a word
	bool
  isEnd ()
  {
	
return isEndFlag;
  
}
  
 
	// Set the node as end of a word
	void
  setEnd ()
  {
	
isEndFlag = true;
  
} 
 
	// Unset the node as end of a word
	void
  unsetEnd ()
  {
	
isEndFlag = false;

} 
};


 
class CompoundWordFinder
{
  
Node * root;					// Root node of the trie

public:
CompoundWordFinder ()
  {
	
root = new Node ();		// Initialize root node
  } 
 
	// Comparator function for sorting strings by length
	static bool
  comparator (string str1, string str2)
  {
	
if (str1.length () == str2.length ())
	  {
		
return str1 < str2;
	  
}
	
return str1.length () > str2.length ();
  
}
  
 
	// Insert a word into the trie
	void
  pushWord (string word)
  {
	
Node * node = root;
	
for (int i = 0; i < word.length (); i++)
	  {
		
if (!node->hasChildren (word[i]))
		  {
			
node->insert (word[i], new Node ());
		  
}
		
node = node->getChild (word[i]);
	  
}
	
node->setEnd ();			// Mark end of the word
  }
  
 
	// Reset end flag for a word in the trie
	void
  resetFlag (string str, int index, Node * tempNode)
  {
	
if (index == str.length ())
	  {
		
tempNode->unsetEnd ();	// Unset end flag if end of word is reached
		return;
	  
}
	
resetFlag (str, index + 1, tempNode->getChild (str[index]));
  
}
  
 
	// Check if a string can be formed by concatenating other words in the trie
	bool
  compoundTrue (string str, int index, Node * tempNode)
  {
	
if (index == str.length ())
	  {
		
return tempNode->isEnd ();	// Check if current node marks end of a word
	  }
	
if (tempNode->isEnd ())
	  {
		
if (compoundTrue (str, index, root))
		  {
			
return true;		// Check if remaining string can be formed from root
		  }
	  
}
	
if (tempNode->hasChildren (str[index]))
	  {
		
return compoundTrue (str, index + 1,
							  tempNode->getChild (str[index]));
	  
}
	
	else
	  {
		
return false;			// No matching child found
	  }
  
}
  
 
	// Find and display the longest and second longest compound words
	void
  findLongestWords (vector < string > &words)
  {
	
vector < string > answer;
	
for (int i = 0; i < words.size (); i++)
	  {
		
answer.push_back (words[i]);
		
pushWord (words[i]);	// Insert word into trie
	  } 
sort (answer.begin (), answer.end (), comparator);	// Sort words by length
	string
	  longestWord = "", secondLongestWord = "";
	
for (int i = 0; i < answer.size (); i++)
	  {
		
resetFlag (answer[i], 0, root);	// Reset end flag for current word
		if (compoundTrue (answer[i], 0, root))
		  {						// Check if word is compound
			if (longestWord.empty ())
			  {
				
longestWord = answer[i];
			  
}
			
			else
			  {
				
secondLongestWord = answer[i];
				
break;
			  
}
		  
}
		
pushWord (answer[i]);	// Reinsert word into trie
	  }
	
	  // Display longest and second longest compound words
	  cout << "Longest_word : " << longestWord << endl;
	
cout << "Second_longest_word : " << secondLongestWord << endl;
  
}

};


 
int
main ()
{
  
CompoundWordFinder finder;
  
fstream file;
  
vector < string > wordList;
  
file.open ("Input_01.txt", ios::in);	// Open input file
  if (file.fail ())
	{
	  
cout << "Failed to open the file.";	// Handle file opening failure
	}
  
  else
	{
	  
string word;
	  
while (file >> word)
		{
		  
wordList.push_back (word);	// Read words from file
		}
	  
file.close ();			// Close file
	  
auto start_timer = high_resolution_clock::now ();	// Start time measurement
	  finder.findLongestWords (wordList);	// Find longest and second longest compound words
	  auto
		end_timer = high_resolution_clock::now ();	// End time measurement
	  auto
		total_time = duration_cast < milliseconds > (end_timer - start_timer);
	  
cout << "Time for executing the input file:: " << total_time.count () << " ms" << endl;	// Display time taken
	}
  
return 0;

}


