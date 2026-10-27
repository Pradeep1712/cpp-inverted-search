#include "Header.h"

void insert_at_last(FileNode*& head, const std::string& data) {
    FileNode* newNode = new FileNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    FileNode* temp = head;
    while (temp->link != nullptr) temp = temp->link;
    temp->link = newNode;
}

void remove_duplicates(FileNode*& headCLA, const std::string& filename, FileNode*& updatedFiles, int& dupCount) {
    FileNode* temp = headCLA;
    FileNode* prev = nullptr;

    while (temp != nullptr) {
        if (temp->fileName == filename) {
            dupCount++;
            insert_at_last(updatedFiles, temp->fileName);
            
            FileNode* toDelete = temp;
            if (!prev) { 
                headCLA = temp->link;
                temp = headCLA;
            } else { 
                prev->link = temp->link;
                temp = prev->link;
            }
            delete toDelete;
        } else {
            prev = temp;
            temp = temp->link;
        }
    }
}

void update_database(MainNode* arr[], FileNode*& headCLA, FileNode*& updatedFiles, int& dupCount) {
    for (int i = 0; i < 27; i++) {
        if (arr[i] != nullptr) {
            std::cout << "Warning: Hash table already initialized. Cannot rebuild from backup.\n";
            return;
        }
    }

    std::string backupFile;
    std::cout << "Enter backup file name: ";
    std::cin >> backupFile;

    if (backupFile.length() < 4 || backupFile.substr(backupFile.length() - 4) != ".txt") {
        std::cout << "Invalid format. Target must be a .txt extension.\n";
        return;
    }

    std::ifstream file(backupFile);
    if (!file.is_open()) {
        std::cout << "Error locating backup file.\n";
        return;
    }

    std::string line;
    if (!std::getline(file, line) || line.empty() || line.front() != '#' || line.back() != '#') {
        std::cout << "File parsing failure: Invalid backup file format.\n";
        return;
    }

    // Safely parse the header payload tracking processed files
    std::string headerData = line.substr(1, line.length() - 2);
    std::stringstream ss(headerData);
    std::string token;
    
    std::getline(ss, token, ';');
    int fileCount = std::stoi(token);
    
    for (int i = 0; i < fileCount; i++) {
        if (std::getline(ss, token, ';')) {
            remove_duplicates(headCLA, token, updatedFiles, dupCount);
        }
    }

    // Parse specific index and word occurrence payloads
    while (std::getline(file, line)) {
        if (line.empty() || line.front() != '#' || line.back() != '#') continue;
        
        std::string recordData = line.substr(1, line.length() - 2);
        std::stringstream rss(recordData);
        
        std::getline(rss, token, ';');
        int index = std::stoi(token);
        
        std::getline(rss, token, ';');
        std::string word = token;
        
        std::getline(rss, token, ';');
        int fc = std::stoi(token);
        
        MainNode* mainNode = new MainNode(word);
        mainNode->fileCount = fc;
        
        SubNode* prevSub = nullptr;
        for (int i = 0; i < fc; i++) {
            std::getline(rss, token, ';');
            std::string fname = token;
            
            std::getline(rss, token, ';');
            int wc = std::stoi(token);
            
            SubNode* subNode = new SubNode(fname);
            subNode->wordCount = wc;
            
            if (i == 0) mainNode->subLink = subNode;
            else prevSub->link = subNode;
            
            prevSub = subNode;
        }
        
        if (!arr[index]) {
            arr[index] = mainNode;
        } else {
            MainNode* temp = arr[index];
            while (temp->mainLink != nullptr) temp = temp->mainLink;
            temp->mainLink = mainNode;
        }
    }
    std::cout << "Database successfully re-established from backup.\n";
}