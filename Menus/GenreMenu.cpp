//
// Created by kornel on 3/29/26.
//

#include "GenreMenu.h"

#include <iostream>
#include <ostream>

void GenreMenu::AddGenre(GenreService &s) {
    std::string genreName;
    std::string genreDescription;
    while (genreName.empty()) {
        std::cout << "Enter genre name" << std::endl;
        std::cin >> genreName;
    }

    while (genreDescription.empty()) {
        std::cout << "Enter genre description" << std::endl;
        std::cin >> genreDescription;
    }
    try {
        s.AddNewGenre(genreName, genreDescription);
        std::cout << "Genre added" << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::FindById(GenreService &s) {
    std::string genreId;
    while (genreId.empty()) {
        std::cout << "Enter genre id" << std::endl;
        std::cin >> genreId;
    }
    try {
         Genre genre = s.GetGenreById(std::stoi(genreId));
        if (genre.Name.empty()) {
            std::cout << "No genre found" << std::endl;
        }else {
            std::cout << "ID:" <<genre.Id << ", NAME:" << genre.Name<<", DESCRIPTION:" << genre.Description << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::EditGenre(GenreService &s) {
    std::string genreNewName;
    std::string genreNewDescription;
    bool isDoneEditing = false;
    int idString;

    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }
    std::cout << "Pick genre id number" << std::endl;
    std::cin >> idString;
    try {
        Genre genreToEdit = s.GetGenreById(idString);
        if (genreToEdit.Id == 0) {
            std::cout << "Genre not found" << std::endl;
            return;
        }
        genreNewName = genreToEdit.Name;
        genreNewDescription = genreToEdit.Description;
        while (!isDoneEditing) {
            std::cout << "Edit: 1.Name \n 2.Description \n 3.Save" << std::endl;
            int pickEdit;
            std::cin >> pickEdit;
            switch (pickEdit) {
                case 1:
                    std::cout << "Enter new name:" << std::endl;
                    std::cin >> genreNewName;
                    break;
                case 2:
                    std::cout << "Enter new description:" << std::endl;
                    std::cin >> genreNewDescription;
                    break;
                case 3:
                    isDoneEditing = true;
                    break;
            }
        }
        genreToEdit.Name = genreNewName;
        genreToEdit.Description = genreNewDescription;
        s.UpdateGenreById(genreToEdit);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GenreMenu::ShowAllGenres(GenreService &s) {
    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << "ID:" <<genre.Id << ", NAME:" << genre.Name<<", DESCRIPTION:" << genre.Description << std::endl;
    }
}

void GenreMenu::DeleteGenre(GenreService &s) {
    int idString;

    std::vector<Genre> genres = s.GetAllGenres();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }

    std::cout << "Pick genre id number to DELETE" << std::endl;
    std::cin >> idString;

    try {
        s.DeleteGenreById(idString);
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
        std::cout << "Choose: ";
        std::cin >> choice;

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