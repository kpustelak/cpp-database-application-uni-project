//
// Created by kornel on 3/29/26.
//

#include "GenreMenu.h"

#include <iostream>
#include <limits>
#include <ostream>

void GenreMenu::AddGenre(GenreService &s) {
    std::string genreName = helpers.EnterData("Enter genre name");
    std::string genreDescription = helpers.EnterData("Enter genre description");
    try {
        s.AddNewGenre(genreName, genreDescription);
        std::cout << "Genre added" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::FindById(GenreService &s) {
    int genreId = helpers.EnterInt("Enter genre id");
    try {
        Genre genre = s.GetGenreById(genreId);
        if (genre.Name.empty()) {
            std::cout << "No genre found" << std::endl;
        } else {
            std::cout << "ID:" << genre.Id << ", NAME:" << genre.Name << ", DESCRIPTION:" << genre.Description << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::EditGenre(GenreService &s) {
    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }

    int id = helpers.EnterInt("Pick genre id number");
    try {
        Genre genreToEdit = s.GetGenreById(id);
        if (genreToEdit.Id == 0) {
            std::cout << "Genre not found" << std::endl;
            return;
        }

        std::string genreNewName = genreToEdit.Name;
        std::string genreNewDescription = genreToEdit.Description;
        bool isDoneEditing = false;

        while (!isDoneEditing) {
            std::cout << "Edit: 1.Name \n 2.Description \n 3.Save" << std::endl;
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
        s.UpdateGenreById(genreToEdit);
        std::cout << "Genre updated" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::ShowAllGenres(GenreService &s) {
    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << "ID:" << genre.Id << ", NAME:" << genre.Name << ", DESCRIPTION:" << genre.Description << std::endl;
    }
}

void GenreMenu::DeleteGenre(GenreService &s) {
    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }

    int id = helpers.EnterInt("Pick genre id number to DELETE");
    try {
        s.DeleteGenreById(id);
        std::cout << "Genre deleted" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::Show(GenreService &s) {
    int choice;
    do {
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