#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>

// Singly linked list for tracking file occurrences of a specific word
struct SubNode {
    int wordCount;
    std::string fileName;
    SubNode* link;
    SubNode(const std::string& fname) : wordCount(1), fileName(fname), link(nullptr) {}
};

// Singly linked list for words mapped to a specific hash table index
struct MainNode {
    std::string word;
    int fileCount;
    MainNode* mainLink;
    SubNode* subLink;
    MainNode(const std::string& w) : word(w), fileCount(1), mainLink(nullptr), subLink(nullptr) {}
};

// Singly linked list for managing command-line arguments and input files
struct FileNode {
    std::string fileName;
    FileNode* link;
    FileNode(const std::string& name) : fileName(name), link(nullptr) {}
};

// Core functionality prototypes
bool validate_file(const std::string& filename, FileNode*& head);
void create_database(MainNode* arr[], FileNode* headCLA, int& createCount);
void print_database(MainNode* arr[]);
void search_database(MainNode* arr[]);
void save_database(MainNode* arr[], FileNode* headCLA, FileNode* updatedFiles, int createCount, int dupCount);
void update_database(MainNode* arr[], FileNode*& headCLA, FileNode*& updatedFiles, int& dupCount);

// Utility prototypes
void clean_word(std::string& word);
void insert_at_last(FileNode*& head, const std::string& data);
void remove_duplicates(FileNode*& headCLA, const std::string& filename, FileNode*& updatedFiles, int& dupCount);
void free_hash_table(MainNode* arr[]);
void free_file_list(FileNode* head);

#endif