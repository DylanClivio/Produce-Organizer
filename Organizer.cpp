#include <iostream>
#include <fstream>
#include <map>
#include <string>

void printFrequency(const std::map<std::string, int>& frequencyMap) {
    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

void printHistogram(const std::map<std::string, int>& frequencyMap) {
    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}

int main() {
    // Map to store the frequency of each grocery item
    std::map<std::string, int> frequencyMap;

    // Open the text file
    std::ifstream inputFile("grocery_list.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read each line from the file
    std::string item;
    while (getline(inputFile, item)) {
        // Increment the frequency count for the current item
        frequencyMap[item]++;
    }

    // Close the file
    inputFile.close();

    // Create and write to frequency.dat for backup
    std::ofstream outputFile("frequency.dat");

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the output file for backup." << std::endl;
        return 1;
    }

    // Write the frequency data to the output file
    for (const auto& pair : frequencyMap) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    // Close the output file
    outputFile.close();

    // Menu loop
    int choice;

    do {
        std::cout << "\nMenu Options:\n"
                  << "1. Find the frequency of a specific item\n"
                  << "2. Print the frequency of all items\n"
                  << "3. Print a histogram of item frequencies\n"
                  << "4. Exit\n"
                  << "Enter your choice: ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();             // clear input buffer to restore cin to a usable state
            std::cin.ignore(10000, '\n'); // ignore last input
            choice = 0; // set choice to an invalid value
        }

        switch (choice) {
            case 1: {
                // Find and display the frequency of a specific item
                std::string userInput;
                std::cout << "Enter a grocery item: ";
                std::cin >> userInput;

                if (frequencyMap.find(userInput) != frequencyMap.end()) {
                    std::cout << "Frequency: " << frequencyMap[userInput] << std::endl;
                } else {
                    std::cout << "Item not found in the list." << std::endl;
                }
                break;
            }

            case 2:
                // Print the frequency of all items
                printFrequency(frequencyMap);
                break;

            case 3:
                // Print a histogram of item frequencies
                printHistogram(frequencyMap);
                break;

            case 4:
                // Exit the program
                std::cout << "Exiting the program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}