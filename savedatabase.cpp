#include "Header.h"

void save_database(MainNode* arr[], FileNode* headCLA, FileNode* updatedFiles, int createCount, int dupCount) {
    std::string fileName;
    std::cout << "Enter backup file name: ";
    std::cin >> fileName;

    std::ifstream checkFile(fileName);
    if (checkFile.is_open()) {
        checkFile.seekg(0, std::ios::end);
        if (checkFile.tellg() > 0) {
            char option;
            std::cout << "Target file is not empty. Overwrite? (y/n): ";
            std::cin >> option;
            if (tolower(option) != 'y') return;
        }
        checkFile.close();
    }

    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error establishing stream to target save file.\n";
        return;
    }

    int totalFiles = dupCount + createCount;
    file << "#" << totalFiles << ";";

    FileNode* tempUpdate = updatedFiles;
    while (tempUpdate != nullptr) {
        file << tempUpdate->fileName;
        if (tempUpdate->link == nullptr && headCLA == nullptr) file << "#\n";
        else file << ";";
        tempUpdate = tempUpdate->link;
    }

    FileNode* tempCLA = headCLA;
    while (tempCLA != nullptr) {
        file << tempCLA->fileName;
        if (tempCLA->link == nullptr) file << "#\n";
        else file << ";";
        tempCLA = tempCLA->link;
    }

    for (int i = 0; i < 27; i++) {
        MainNode* tempMain = arr[i];
        while (tempMain != nullptr) {
            file << "#" << i << ";" << tempMain->word << ";" << tempMain->fileCount;
            
            SubNode* tempSub = tempMain->subLink;
            while (tempSub != nullptr) {
                file << ";" << tempSub->fileName << ";" << tempSub->wordCount;
                tempSub = tempSub->link;
            }
            file << "#\n";
            tempMain = tempMain->mainLink;
        }
    }
    std::cout << "Database successfully saved to " << fileName << "\n";
}