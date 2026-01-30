#pragma once
#include "Node.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

class Trie {
public:
    // Constructor: Creates the root node representing the empty string
    Trie();

    // Destructor: Deletes the entire tree and frees memory
    ~Trie();

    // Insert: Adds a string and its location in the text to the Trie
    void insert(string str, int location);

    // Search: Returns a list of locations (max 3) for strings starting with the given prefix.
    // Also prints the number of nodes visited during the search.
    list<int> search(string str);

    // Delete (Censor): Removes the "end of string" marker for a specific phrase.
    // Does not delete the nodes to preserve other longer phrases (Assignment Stage 4).
    void deleteString(string str);

private:
    Node* _root;

    // Helper function: Finds the node representing the specific string/prefix.
    // Returns nullptr if the path does not exist.
    Node* findNode(string str) const;

    // Helper function: Recursive pre-order traversal to collect search results.
    // Stops collecting after 3 results are found.
    void searchRecursive(Node* current, list<int>& results, int& visitedNodes);
    
    bool removeRecursive(Node* current, string& str, int index);
};
