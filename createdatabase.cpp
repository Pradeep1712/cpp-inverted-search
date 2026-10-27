#include "Header.h"

// Sanitizes input words to ensure consistent hashing and searching
void clean_word(std::string& word) {
    std::string cleaned;
    for (char c : word) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    word = cleaned;
}

// Validates file extension, verifies accessibility, and prevents duplicate processing
bool validate_file(const std::string& filename, FileNode*& head) {
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") return false;
    
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    // Check if the file is empty
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) return false; 
    
    FileNode* temp = head;
    FileNode* record = nullptr;
    while (temp != nullptr) {
        if (temp->fileName == filename) return false; 
        record = temp;
        temp = temp->link;
    }
    
    FileNode* newNode = new FileNode(filename);
    if (!head) head = newNode;
    else record->link = newNode;
    
    return true;
}

void create_database(MainNode* arr[], FileNode* headCLA, int& createCount) {
    static bool isCreated = false;
    if (isCreated) {
        std::cout << "Database generation already completed.\n";
        return;
    }
    if (!headCLA) {
        std::cout << "No valid files available for database generation.\n";
        return;
    }
    
    FileNode* tempFile = headCLA;
    while (tempFile != nullptr) {
        std::ifstream file(tempFile->fileName);
        if (!file.is_open()) {
            tempFile = tempFile->link;
            continue;
        }
        
        createCount++;
        std::string word;
        while (file >> word) {
            clean_word(word);
            if (word.empty()) continue;
            
            // Hash index calculation: 0-25 for a-z, 26 for special/numeric start
            int index = (isalpha(word[0])) ? (word[0] - 'a') : 26;
            
            if (!arr[index]) {
                MainNode* newMain = new MainNode(word);
                newMain->subLink = new SubNode(tempFile->fileName);
                arr[index] = newMain;
            } else {
                MainNode* tempMain = arr[index];
                MainNode* prevMain = nullptr;
                bool wordFound = false;
                
                while (tempMain != nullptr) {
                    if (tempMain->word == word) {
                        wordFound = true;
                        break;
                    }
                    prevMain = tempMain;
                    tempMain = tempMain->mainLink;
                }
                
                if (wordFound) {
                    SubNode* tempSub = tempMain->subLink;
                    SubNode* prevSub = nullptr;
                    bool fileFound = false;
                    
                    while (tempSub != nullptr) {
                        if (tempSub->fileName == tempFile->fileName) {
                            tempSub->wordCount++;
                            fileFound = true;
                            break;
                        }
                        prevSub = tempSub;
                        tempSub = tempSub->link;
                    }
                    
                    if (!fileFound) {
                        prevSub->link = new SubNode(tempFile->fileName);
                        tempMain->fileCount++;
                    }
                } else {
                    MainNode* newMain = new MainNode(word);
                    newMain->subLink = new SubNode(tempFile->fileName);
                    prevMain->mainLink = newMain;
                }
            }
        }
        tempFile = tempFile->link;
    }
    isCreated = true;
    std::cout << "Database successfully created.\n";
}