//
// Created by kornel on 3/30/26.
//

#include "../Header/ReaderMenu.h"

#include <iostream>

void ReaderMenu::AddReader(ReaderService &r) {
    helpers.ClearScreen();
    std::string Name = helpers.EnterData("Enter reader name");
    std::string Surname = helpers.EnterData("Enter reader surname");
    std::string PhoneNumber = helpers.EnterData("Enter reader phone number");
    std::string Email = helpers.EnterData("Enter reader email");

    r.Add(Name, Surname, PhoneNumber, Email);
    std::cout<<"User was added to database"<<std::endl;
    helpers.PressEnterToContinue();
}
void ReaderMenu::ShowAllReaders(ReaderService &r) {
    std::vector<Reader> readers = r.GetAll();
    for (auto reader : readers) {
        std::cout<<reader.Id<<". "<<reader.Name<<" "<<reader.Surname<<" "<<reader.PhoneNumber<<" "<<reader.Email<<std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::GetReaderById(ReaderService &r) {
    int readerId = helpers.EnterInt("Enter reader id to find him");
    Reader reader = r.GetById(readerId);
    if (!reader.Name.empty()) {
        std::cout<<reader.Id<<". "<<reader.Name<<" "<<reader.Surname<<" "<<reader.PhoneNumber<<" "<<reader.Email<<std::endl;
    }else {
        std::cout<<"We cant find any matching user"<<std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::GetReaderByNameOrSurname(ReaderService &r) {
    std::string dataToMatch = helpers.EnterData("Enter name or surname to find reader");
    std::vector<Reader> readers = r.GetByPhrase(dataToMatch);
    for (auto reader : readers) {
        std::cout<<reader.Id<<". "<<reader.Name<<" "<<reader.Surname<<" "<<reader.PhoneNumber<<" "<<reader.Email<<std::endl;
    }
    helpers.PressEnterToContinue();
}
void ReaderMenu::EditReader(ReaderService &r) {
    helpers.ClearScreen();
    std::vector<Reader> readers = r.GetAll();
    for (auto reader : readers) {
        std::cout<<reader.Id<<". "<<reader.Name<<" "<<reader.Surname<<std::endl;
    }
    int readerToEditInt = helpers.EnterInt("Enter reader id to edit");
    try {
        Reader reader = r.GetById(readerToEditInt);
        if (reader.Id == 0) {
            std::cout << "Reader not found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }
        std::string Name = reader.Name;
        std::string Surname = reader.Surname;
        std::string PhoneNumber = reader.PhoneNumber;
        std::string Email = reader.Email;
        bool isDoneEditing = false;

        while (!isDoneEditing) {
            helpers.ClearScreen();
            std::cout << "Editing: " << Name<< std::endl;
            std::cout << "1. Name\n2. Surname\n3. Phone number \n4. Email \n 0. Save\n";
            int pickEdit = helpers.EnterInt("Choose");
            switch (pickEdit) {
                case 1:
                    Name = helpers.EnterData("Enter new name");
                    break;
                case 2:
                    Surname = helpers.EnterData("Enter new surname");
                    break;
                case 3:
                    PhoneNumber = helpers.EnterData("Enter new phone number");
                    break;
                case 4:
                    Email = helpers.EnterData("Enter new email");
                    break;
                case 0:
                    isDoneEditing = true;
                    break;
                default:
                    std::cout << "Unknown option" << std::endl;
            }
        }
        r.Update(reader.Id, Name, Surname, PhoneNumber, Email);
        helpers.PressEnterToContinue();
    }catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
}
void ReaderMenu::DeleteReader(ReaderService &r) {
    helpers.ClearScreen();
    std::vector<Reader> readers = r.GetAll();
    for (auto reader : readers) {
        std::cout<<reader.Id<<". "<<reader.Name<<" "<<reader.Surname<<std::endl;
    }
    int readerToDeleteInt = helpers.EnterInt("Enter reader id to delete");
    Reader reader = r.GetById(readerToDeleteInt);
    if (reader.Name.empty()) {
        std::cout << "Reader not found" << std::endl;
        return;
    }else {
        if (helpers.Confirm("Are you sure you want to delete reader?")) {
            r.Delete(reader.Id);
        }
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