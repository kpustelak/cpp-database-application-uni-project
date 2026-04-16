//
// Created by kornel on 3/30/26.
//

#include "../Header/ReaderMenu.h"

#include <iostream>

void ReaderMenu::AddReader(ReaderService &r) {
    helpers.ClearScreen();
    std::string name = helpers.EnterData("Enter reader name");
    std::string surname = helpers.EnterData("Enter reader surname");
    std::string phoneNumber = helpers.EnterData("Enter reader phone number");
    std::string email = helpers.EnterData("Enter reader email");

    try {
        r.Add(name, surname, phoneNumber, email);
        std::cout << "Reader added" << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::ShowAllReaders(ReaderService &r) {
    helpers.ClearScreen();
    std::vector<Reader> readers = r.GetAll();
    if (readers.empty()) {
        std::cout << "No readers found" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    for (auto reader : readers) {
        std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname << " "
                  << reader.PhoneNumber << " " << reader.Email << std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::GetReaderById(ReaderService &r) {
    helpers.ClearScreen();
    std::string dataToMatch = helpers.EnterData("Enter name or surname to narrow down reader");
    try {
        std::vector<Reader> readers = r.GetByPhrase(dataToMatch);
        if (readers.empty()) {
            std::cout << "No readers found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        for (auto reader : readers) {
            std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname << " "
                      << reader.PhoneNumber << " " << reader.Email << std::endl;
        }

        int readerId = helpers.EnterInt("Enter reader id");
        Reader reader = r.GetById(readerId);
        if (!reader.Name.empty()) {
            std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname << " "
                      << reader.PhoneNumber << " " << reader.Email << std::endl;
        } else {
            std::cout << "No reader found with this id" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::GetReaderByNameOrSurname(ReaderService &r) {
    helpers.ClearScreen();
    std::string dataToMatch = helpers.EnterData("Enter name or surname to find reader");
    try {
        std::vector<Reader> readers = r.GetByPhrase(dataToMatch);
        if (readers.empty()) {
            std::cout << "No readers found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        for (auto reader : readers) {
            std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname << " "
                      << reader.PhoneNumber << " " << reader.Email << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::EditReader(ReaderService &r) {
    helpers.ClearScreen();
    try {
        std::string phrase = helpers.EnterData("Enter name or surname to find reader");
        std::vector<Reader> readers = r.GetByPhrase(phrase);
        if (readers.empty()) {
            std::cout << "No readers found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        for (auto existingReader : readers) {
            std::cout << existingReader.Id << ". " << existingReader.Name << " " << existingReader.Surname << std::endl;
        }

        int readerToEditInt = helpers.EnterInt("Enter reader id to edit");
        Reader reader = r.GetById(readerToEditInt);
        if (reader.Id == 0) {
            std::cout << "Reader not found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        std::string name = reader.Name;
        std::string surname = reader.Surname;
        std::string phoneNumber = reader.PhoneNumber;
        std::string email = reader.Email;
        bool isDoneEditing = false;

        while (!isDoneEditing) {
            helpers.ClearScreen();
            std::cout << "Editing: " << name << std::endl;
            std::cout << "1. Name\n2. Surname\n3. Phone number \n4. Email \n 0. Save\n";
            int pickEdit = helpers.EnterInt("Choose");
            switch (pickEdit) {
                case 1:
                    name = helpers.EnterData("Enter new name");
                    break;
                case 2:
                    surname = helpers.EnterData("Enter new surname");
                    break;
                case 3:
                    phoneNumber = helpers.EnterData("Enter new phone number");
                    break;
                case 4:
                    email = helpers.EnterData("Enter new email");
                    break;
                case 0:
                    isDoneEditing = true;
                    break;
                default:
                    std::cout << "Unknown option" << std::endl;
            }
        }
        r.Update(reader.Id, name, surname, phoneNumber, email);
        std::cout << "Reader updated" << std::endl;
    }catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::DeleteReader(ReaderService &r) {
    helpers.ClearScreen();
    try {
        std::string phrase = helpers.EnterData("Enter name or surname to find reader");
        std::vector<Reader> readers = r.GetByPhrase(phrase);
        if (readers.empty()) {
            std::cout << "No readers found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        for (auto reader : readers) {
            std::cout << reader.Id << ". " << reader.Name << " " << reader.Surname << std::endl;
        }

        int readerToDeleteInt = helpers.EnterInt("Enter reader id to delete");
        Reader reader = r.GetById(readerToDeleteInt);
        if (reader.Name.empty()) {
            std::cout << "Reader not found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }

        if (!helpers.Confirm("Are you sure you want to delete reader?")) {
            std::cout << "Cancelled" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }

        r.Delete(reader.Id);
        std::cout << "Reader deleted" << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void ReaderMenu::Show(ReaderService &r) {
    int choice;
    do {
        helpers.ClearScreen();
        std::cout << "\n=== READER MENU ===\n";
        std::cout << "1. Add reader\n";
        std::cout << "2. Show all readers\n";
        std::cout << "3. Find by id\n";
        std::cout << "4. Find by name/surname\n";
        std::cout << "5. Edit reader\n";
        std::cout << "6. Delete reader\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: AddReader(r); break;
            case 2: ShowAllReaders(r); break;
            case 3: GetReaderById(r); break;
            case 4: GetReaderByNameOrSurname(r); break;
            case 5: EditReader(r); break;
            case 6: DeleteReader(r); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}