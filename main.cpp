#include "Header.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./a.out <file1.txt> <file2.txt> ...\n";
        return 1;
    }

    int createCount = 0;
    int dupCount = 0;

    FileNode* headCLA = nullptr;
    FileNode* updatedFiles = nullptr;
    MainNode* arr[27] = {nullptr}; // Hash table of size 27

    // Validate and load files passed via command line
    for (int i = 1; i < argc; i++) {
        validate_file(argv[i], headCLA);
    }

    int choice;
    do {
        std::cout << "\n===== MENU =====\n"
                  << "1. Update Database\n"
                  << "2. Create Database\n"
                  << "3. Print Database\n"
                  << "4. Search Database\n"
                  << "5. Save Database\n"
                  << "6. Exit\n"
                  << "Enter your choice: ";
        
        // Input validation block
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch(choice) {
            case 1:
                update_database(arr, headCLA, updatedFiles, dupCount);
                break;
            case 2:
                create_database(arr, headCLA, createCount);
                break;
            case 3:
                print_database(arr);
                break;
            case 4:
                search_database(arr);
                break;
            case 5:
                save_database(arr, headCLA, updatedFiles, createCount, dupCount);
                break;
            case 6:
                std::cout << "Cleaning up memory allocations and exiting...\n";
                free_hash_table(arr);
                free_file_list(headCLA);
                free_file_list(updatedFiles);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 6);

    return 0;
}

// Releases all dynamically allocated memory in the hash table
void free_hash_table(MainNode* arr[]) {
    for (int i = 0; i < 27; ++i) {
        MainNode* currMain = arr[i];
        while (currMain) {
            SubNode* currSub = currMain->subLink;
            while (currSub) {
                SubNode* tempSub = currSub;
                currSub = currSub->link;
                delete tempSub;
            }
            MainNode* tempMain = currMain;
            currMain = currMain->mainLink;
            delete tempMain;
        }
    }
}

// Releases dynamically allocated memory for file tracking lists
void free_file_list(FileNode* head) {
    while (head) {
        FileNode* temp = head;
        head = head->link;
        delete temp;
    }
}