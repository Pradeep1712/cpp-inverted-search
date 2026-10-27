#include "Header.h"

void search_database(MainNode* arr[]) {
    std::string word;
    std::cout << "Enter word to search: ";
    std::cin >> word;
    clean_word(word);
    
    if (word.empty()) return;
    
    int index = (isalpha(word[0])) ? (word[0] - 'a') : 26;
    MainNode* tempMain = arr[index];
    
    while (tempMain != nullptr) {
        if (tempMain->word == word) {
            std::cout << "\nSearch Result:\n";
            std::cout << "Target Word: " << tempMain->word << " | Total Files Containing Word: " << tempMain->fileCount << "\n\n";
            
            SubNode* tempSub = tempMain->subLink;
            while (tempSub != nullptr) {
                std::cout << "-> File: " << tempSub->fileName 
                          << " | Occurrences: " << tempSub->wordCount << "\n";
                tempSub = tempSub->link;
            }
            return;
        }
        tempMain = tempMain->mainLink;
    }
    std::cout << "Query not found in the indexed database.\n";
}