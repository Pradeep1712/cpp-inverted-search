#include "Header.h"

void print_database(MainNode* arr[]) {
    std::cout << std::left << std::setw(10) << "Index" 
              << std::setw(20) << "Word" 
              << std::setw(15) << "FileCount" 
              << std::setw(20) << "FileName" 
              << "WordCount\n";
    std::cout << std::string(80, '-') << "\n";

    for (int i = 0; i < 27; i++) {
        MainNode* tempMain = arr[i];
        while (tempMain != nullptr) {
            std::cout << std::left << std::setw(10) << i 
                      << std::setw(20) << tempMain->word 
                      << std::setw(15) << tempMain->fileCount;
            
            SubNode* tempSub = tempMain->subLink;
            bool first = true;
            
            while (tempSub != nullptr) {
                if (!first) {
                    std::cout << std::setw(45) << " "; 
                }
                std::cout << std::setw(20) << tempSub->fileName 
                          << tempSub->wordCount << "\n";
                first = false;
                tempSub = tempSub->link;
            }
            tempMain = tempMain->mainLink;
        }
    }
}