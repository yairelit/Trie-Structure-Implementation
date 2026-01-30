#include "Book.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

Book::Book(const string& filepath) {
    ifstream file(filepath);

    if (file.is_open()) {
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        file.close();

        transform(content.begin(), content.end(), content.begin(), ::tolower);
        regex pattern("\\s+");
        content = regex_replace(content, pattern, " ");

        processContent();
    }
    else {
        throw invalid_argument("Unable to open file");
    }
}

void Book::processContent() {
    vector<int> wordStarts;
    bool inWord = false;
    for (size_t i = 0; i < content.length(); ++i) {
        if (content[i] != ' ') {
            if (!inWord) {
                wordStarts.push_back((int)i);
                inWord = true;
            }
        }
        else {
            inWord = false;
        }
    }

    if (wordStarts.size() < 3) return;

    for (size_t i = 0; i < wordStarts.size() - 2; ++i) {
        int startIdx = wordStarts[i];
        int endIdx;
        if (i + 3 < wordStarts.size()) {
            endIdx = wordStarts[i + 3] - 1;
        }
        else {
            endIdx = content.length();
        }

        string triplet = content.substr(startIdx, endIdx - startIdx);

        // === FINAL FIX 1: Trim trailing space from triplet ===
        // This ensures "prince of denmark " becomes "prince of denmark".
        // It prevents creating an extra node for the space, fixing the node count (19 -> 18).
        if (!triplet.empty() && triplet.back() == ' ') {
            triplet.pop_back();
        }

        trie.insert(triplet, startIdx);
    }
}

void Book::searchAndPrint(const string& query) {
    list<int> locations = trie.search(query);

    if (locations.empty()) {
        cout << "No results" << endl;
        return;
    }

    cout << "Sentences matching the prefix:" << endl;
    for (int loc : locations) {
        cout << extractSentence(loc) << endl;
    }
}

void Book::censorQuery(const string& query) {
    trie.deleteString(query);
}

string Book::extractSentence(int location) {
    int startPos = location;
    int endPos = location;
    int wordsCount = 0;
    bool cutStart = false;
    bool cutEnd = false;
    bool inWord = false;

    // --- Backward Scan ---
    for (int i = location - 1; i >= 0; --i) {
        if (content[i] == '.') {
            startPos = i + 1;
            if (startPos < content.length() && content[startPos] == ' ') {
                startPos++;
            }
            if (inWord) wordsCount++;

            cutStart = false;
            inWord = false;
            break;
        }

        if (content[i] != ' ') {
            inWord = true;
        }
        else {
            if (inWord) {
                wordsCount++;
                inWord = false;
            }
        }

        if (wordsCount >= 5) {
            startPos = i + 1;
            cutStart = true;
            break;
        }

        if (i == 0) {
            startPos = 0;
            if (inWord) wordsCount++;
        }
    }

    if (cutStart) wordsCount = 5;

    // --- Forward Scan ---
    for (size_t i = location; i < content.length(); ++i) {
        if (content[i] == '.') {
            endPos = i + 1;
            break;
        }

        if (content[i] == ' ') {
            wordsCount++;
        }

        if (wordsCount >= 10) {
            cutEnd = true;
            endPos = i;
            break;
        }

        endPos = i + 1;
    }

    // --- Assemble Result ---
    string result = "";
    if (cutStart) result += "...";

    if (startPos < location) {
        result += content.substr(startPos, location - startPos);
    }

    result += "*";
    result += content.substr(location, endPos - location);

    // === FINAL FIX 2: Remove trailing space from output ===
    // If the content had a space at the end (due to regex replace), we remove it here.
    if (!cutEnd && !result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    if (cutEnd) result += "...";

    return result;
}