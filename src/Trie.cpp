#include "Trie.h"

Trie::Trie() {
    _root = new Node();
}

Trie::~Trie() {
    delete _root;
}

void Trie::insert(std::string str, int location) {
    Node* current = _root;
    for (char c : str) {
        Node* next = current->getChild(c);
        if (next == nullptr) {
            next = new Node();
            current->addChild(c, next);
        }
        current = next;
    }
    current->setEndPoint(true);
    current->addLocation(location);
}

Node* Trie::findNode(std::string str) const {
    Node* current = _root;
    for (char c : str) {
        current = current->getChild(c);
        if (current == nullptr) {
            return nullptr;
        }
    }
    return current;
}

void Trie::searchRecursive(Node* current, std::list<int>& results, int& visitedNodes) {
    if (results.size() >= 3 || current == nullptr) {
        return;
    }

    visitedNodes++;

    if (current->isEndPoint()) {
        std::list<int>& locs = current->getLocations();
        for (int loc : locs) {
            if (results.size() < 3) {
                results.push_back(loc);
            }
            else {
                break;
            }
        }
    }

    if (results.size() >= 3) return;

    const std::map<char, Node*>& children = current->getChildren();
    for (auto const& pair : children) {
        searchRecursive(pair.second, results, visitedNodes);
        if (results.size() >= 3) return;
    }
}

std::list<int> Trie::search(std::string str) {
    std::list<int> results;
    int visitedNodes = 0;

    Node* current = _root;
    visitedNodes++;

    bool foundPrefix = true;
    for (char c : str) {
        current = current->getChild(c);
        if (current == nullptr) {
            foundPrefix = false;
            break;
        }
        visitedNodes++;
    }

    if (foundPrefix) {
        visitedNodes--;
        searchRecursive(current, results, visitedNodes);
    }

    std::cout << "The search required visiting " << visitedNodes << " nodes." << std::endl;
    return results;
}

void Trie::deleteString(std::string str) {
    if (_root == nullptr) return;
    removeRecursive(_root, str, 0);
}

bool Trie::removeRecursive(Node* current, std::string& str, int index) {
    if (index == str.length()) {
        if (current->isEndPoint()) {
            current->setEndPoint(false);
        }
        return current->getChildren().empty();
    }

    char c = str[index];
    Node* child = current->getChild(c);

    if (child == nullptr) {
        return false;
    }

    bool shouldDeleteChild = removeRecursive(child, str, index + 1);

    if (shouldDeleteChild) {
        current->removeChild(c);
        delete child;
        return current->getChildren().empty() && !current->isEndPoint();
    }

    return false;
}