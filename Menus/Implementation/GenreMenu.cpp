//
// Created by kornel on 3/29/26.
//

#include "../Header/GenreMenu.h"

#include <iostream>
#include <limits>
#include <ostream>

void GenreMenu::AddGenre(GenreService &s) {
    std::string genreName = helpers.EnterData("Enter genre name");
    std::string genreDescription = helpers.EnterData("Enter genre description");
    try {
        s.Add(genreName, genreDescription);
        std::cout << "Genre added" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void GenreMenu::FindById(GenreService &s) {
    int genreId = helpers.EnterInt("Enter genre id");
    try {
        Genre genre = s.GetById(genreId);
        if (genre.Name.empty()) {
            std::cout << "No genre found" << std::endl;
        } else {
            std::cout << "ID:" << genre.Id << ", NAME:" << genre.Name << ", DESCRIPTION:" << genre.Description << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void GenreMenu::EditGenre(GenreService &s) {
    helpers.ClearScreen();
    std::vector<Genre> genres = s.GetAll();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }

    int id = helpers.EnterInt("Pick genre id number");
    try {
        Genre genreToEdit = s.GetById(id);
        if (genreToEdit.Id == 0) {
            std::cout << "Genre not found" << std::endl;
            helpers.PressEnterToContinue();
            return;
        }

        std::string genreNewName = genreToEdit.Name;
        std::string genreNewDescription = genreToEdit.Description;
        bool isDoneEditing = false;

        while (!isDoneEditing) {
            helpers.ClearScreen();
            std::cout << "Editing: " << genreToEdit.Name << std::endl;
            std::cout << "1. Name\n2. Description\n3. Save\n";
            int pickEdit = helpers.EnterInt("Choose");
            switch (pickEdit) {
                case 1:
                    genreNewName = helpers.EnterData("Enter new name");
                    break;
                case 2:
                    genreNewDescription = helpers.EnterData("Enter new description");
                    break;
                case 3:
                    isDoneEditing = true;
                    break;
                default:
                    std::cout << "Unknown option" << std::endl;
            }
        }
        genreToEdit.Name = genreNewName;
        genreToEdit.Description = genreNewDescription;
        s.Update(genreToEdit);
        std::cout << "Genre updated" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void GenreMenu::ShowAllGenres(GenreService &s) {
    helpers.ClearScreen();
    std::vector<Genre> genres = s.GetAll();
    for (auto genre : genres) {
        std::cout << "ID:" << genre.Id << ", NAME:" << genre.Name << ", DESCRIPTION:" << genre.Description << std::endl;
    }
    helpers.PressEnterToContinue();
}

void GenreMenu::DeleteGenre(GenreService &s) {
    helpers.ClearScreen();
    std::vector<Genre> genres = s.GetAll();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }

    int id = helpers.EnterInt("Pick genre id number to DELETE");
    if (!helpers.Confirm("Are you sure you want to delete this genre?")) {
        std::cout << "Cancelled" << std::endl;
        helpers.PressEnterToContinue();
        return;
    }
    try {
        s.Delete(id);
        std::cout << "Genre deleted" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    helpers.PressEnterToContinue();
}

void GenreMenu::Show(GenreService &s) {
    int choice;
    do {
        helpers.ClearScreen();
        std::cout << "\n=== GENRE MENU ===\n";
        std::cout << "1. Add genre\n";
        std::cout << "2. Show all genres\n";
        std::cout << "3. Find by id\n";
        std::cout << "4. Edit genre\n";
        std::cout << "5. Delete genre\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: AddGenre(s); break;
            case 2: ShowAllGenres(s); break;
            case 3: FindById(s); break;
            case 4: EditGenre(s); break;
            case 5: DeleteGenre(s); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}