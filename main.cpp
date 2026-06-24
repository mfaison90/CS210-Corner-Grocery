// CornerGrocery.cpp
// CS 210 Project Three - Corner Grocer Item Tracker
//
// This program reads a list of grocery items from a text file, counts how
// often each item appears, and lets the user look up an item, print all
// item counts, or print a histogram. It also writes a backup file
// (frequency.dat) automatically when the program starts.

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

// ============================================================
// The GroceryTracker class reads the input file, counts each
// item, and provides ways to query and display that data.
// ============================================================
class GroceryTracker {
private:
    // Maps each item name to the number of times it was purchased.
    std::map<std::string, int> itemFrequencies;

    // Name of the input file that lists the day's purchases.
    std::string inputFileName;

    // Reads the input file and builds the frequency map. Private because
    // it is an internal helper used only by the constructor.
    void LoadItemsFromFile() {
        std::ifstream inputFile(inputFileName);

        // If the file can't be opened, warn the user and stop.
        if (!inputFile.is_open()) {
            std::cout << "Error: could not open file " << inputFileName << std::endl;
            return;
        }

        std::string item;
        // Read one word at a time until the end of the file.
        while (inputFile >> item) {
            // Adds 1 to the item's count (creating it at 0 first if new).
            itemFrequencies[item]++;
        }

        inputFile.close();
    }

public:
    // Constructor: stores the file name and loads the data right away.
    GroceryTracker(const std::string& fileName) {
        inputFileName = fileName;
        LoadItemsFromFile();
    }

    // Menu Option 1: returns how many times a single item was purchased.
    int GetFrequencyOfItem(const std::string& item) const {
        auto it = itemFrequencies.find(item);
        if (it != itemFrequencies.end()) {
            return it->second;
        }
        return 0;
    }

    // Menu Option 2: prints every item paired with its count.
    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    // Menu Option 3: prints every item as a histogram of asterisks.
    void PrintHistogram() const {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    // Writes the item/count data to a backup file (frequency.dat).
    void WriteBackupFile(const std::string& backupFileName) const {
        std::ofstream backupFile(backupFileName);
        if (!backupFile.is_open()) {
            std::cout << "Error: could not create backup file " << backupFileName << std::endl;
            return;
        }
        for (const auto& pair : itemFrequencies) {
            backupFile << pair.first << " " << pair.second << std::endl;
        }
        backupFile.close();
    }
};

// Displays the four menu options to the user.
void DisplayMenu() {
    std::cout << "\n===== Corner Grocer Item Tracker =====" << std::endl;
    std::cout << "1. Search for an item's frequency" << std::endl;
    std::cout << "2. Print all item frequencies" << std::endl;
    std::cout << "3. Print histogram of item frequencies" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice (1-4): ";
}

int main() {
    // Create the tracker; the constructor reads the input file automatically.
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");

    // Data File Creation requirement: write the backup as soon as the
    // program starts, with no user action needed.
    tracker.WriteBackupFile("frequency.dat");

    int choice = 0;

    // Keep showing the menu until the user picks option 4 (Exit).
    do {
        DisplayMenu();
        std::cin >> choice;

        // Input validation: if the user typed something that isn't a number,
        // clear the error and discard the bad input so we don't loop forever.
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number from 1 to 4." << std::endl;
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                std::string searchItem;
                std::cout << "Enter the item to search for: ";
                std::cin >> searchItem;
                int frequency = tracker.GetFrequencyOfItem(searchItem);
                std::cout << searchItem << " was purchased " << frequency << " time(s)." << std::endl;
                break;
            }
            case 2:
                std::cout << "\nItem Frequencies:" << std::endl;
                tracker.PrintAllFrequencies();
                break;
            case 3:
                std::cout << "\nItem Frequency Histogram:" << std::endl;
                tracker.PrintHistogram();
                break;
            case 4:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number from 1 to 4." << std::endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
