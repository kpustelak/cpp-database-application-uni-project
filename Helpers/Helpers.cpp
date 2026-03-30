//
// Created by kornel on 3/30/26.
//

#include "Helpers.h"

#include <iostream>
#include <limits>
#include <string>

std::string Helpers::EnterData(std::string text) {
    std::string textToReturn;
    while (textToReturn.empty()) {
        std::cout << text << std::endl;
        std::getline(std::cin, textToReturn);
    }
    return textToReturn;
}

int Helpers::EnterInt(std::string text) {
    int value;
    while (true) {
        std::cout << text << std::endl;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, enter a number" << std::endl;
    }
}

bool Helpers::Confirm(std::string text) {
    std::string answer;
    while (true) {
        std::cout << text << " (y/n): ";
        std::getline(std::cin, answer);
        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;
        std::cout << "Enter y or n" << std::endl;
    }
}

int Helpers::PickFromList(std::vector<std::string> options, std::string title) {
    std::cout << "\n" << title << std::endl;
    for (int i = 0; i < options.size(); i++) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }
    return EnterInt("Choose");
}

void Helpers::PressEnterToContinue() {
    std::cout << "\nPress enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Helpers::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
