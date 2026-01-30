#pragma once
#include <list>
#include <map>
#include <iostream>
using namespace std;

class Node {
private:
	bool _isEndOfString;
	list<int> _locations;
	map<char, Node*> _children;

public:
	Node() : _isEndOfString(false) {};

	~Node() {
		for (auto const& pair : _children) {
			delete pair.second; 
		}
		_children.clear();
	}

	bool isEndPoint() const { return _isEndOfString; }
	void setEndPoint(bool isEnd) { _isEndOfString = isEnd; }

	list<int>& getLocations() { return _locations; }
	void addLocation(int location) {
		_locations.push_back(location);
	}

	Node* getChild(char c) const {
		auto it = _children.find(c);
		if (it != _children.end()) {
			return it->second;
		}
		return nullptr;

	};
	const map<char, Node*>& getChildren() const { return _children; }
	void addChild(char c, Node* child) { _children[c] = child; }
	void removeChild(char c) {
		_children.erase(c);
	}
};