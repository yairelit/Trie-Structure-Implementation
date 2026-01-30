# 📚 Trie-Based Book Search Engine

![Language](https://img.shields.io/badge/language-C++-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A high-performance C++ application designed to index and search through book contents using a **Trie (Prefix Tree)** data structure. The system supports efficient phrase searching, context-aware sentence extraction, and dynamic memory pruning.

## 🚀 Features

* **Trie Data Structure:** Implements a custom Trie for $O(L)$ search complexity (where $L$ is the query length), ensuring fast lookups regardless of book size.
* **Triplet Indexing:** Parses text using a "sliding window" approach, indexing every sequence of three consecutive words to optimize storage and retrieval.
* **Smart Context Extraction:**
    * Retrieves sentences with context (up to 5 words backward, 10 words total).
    * Handles sentence boundaries (periods) and complex whitespace normalization.
    * Marks the exact match location with an asterisk (`*`).
* **Memory Pruning:** Features a robust deletion mechanism that physically removes "dead" nodes and branches from memory when phrases are censored, preventing memory leaks.

## 🛠️ Project Structure

| File | Description |
| :--- | :--- |
| `main.cpp` | Entry point. Handles the interactive user menu (Search/Censor/Exit). |
| `Book.cpp` | Manages file reading, text normalization, and the logic for extracting sentences. |
| `Trie.cpp` | Core data structure implementation, including recursive search and pruning logic. |
| `Node.cpp` | Represents a single node in the tree, managing children pointers and location lists. |

## ⚙️ Build & Run

### Prerequisites
* A C++ Compiler (GCC, Clang, or MSVC) supporting C++11 or later.

### Compilation
Run the following command in your terminal to compile the project:

```bash
g++ -std=c++11 -o search_engine main.cpp Book.cpp Trie.cpp Node.cpp
