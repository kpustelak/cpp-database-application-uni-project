//
// Created by kornel on 3/30/26.
//

#include "BookMenu.h"

#include <iostream>
#include "../Helpers/Helpers.h"
#include "../Service/GenreService.h"


void BookMenu::AddBook(BookService &b, GenreService &g) {
    std::string bookTitle = helpers.EnterData("Enter book title");
    std::string bookAuthor = helpers.EnterData("Enter book author");
    int bookYearOfRelease = std::stoi(helpers.EnterData("Enter book year of release"));
    std::string bookLocationCode = helpers.EnterData("Enter book location");
    int genreId;

    std::vector<Genre> genres = g.GetAllGenres();
    for (auto genre : genres) {
        std::cout << genre.Id << ". " << genre.Name << std::endl;
    }
    std::cout << "Pick genre id " << std::endl;
    std::cin >> genreId;

    try {
        b.AddNewBook(bookTitle, bookAuthor, bookYearOfRelease, bookLocationCode, genreId);
        std::cout << "Book added" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::GetBookById(BookService &b) {
    int bookId = std::stoi(helpers.EnterData("Enter book id"));
    Book book = b.GetBook(bookId);
    if (book.Id <= 0) {
        std::cout << "There is no book with this id" << std::endl;
    } else {
        std::cout << book.Id << ". " << book.Title << ". " << book.Author << ". " << book.YearOfRelease << std::endl;
    }
}

void BookMenu::GetAllBooks(BookService &b) {
    std::vector<Book> books = b.GetAllBooks();
    for (auto book : books) {
        std::cout << book.Id << ". " << book.Title << ". " << book.Author << ". " << book.YearOfRelease << std::endl;
    }
}

void BookMenu::EditBook(BookService &b, GenreService &g) {
    std::cout << "Find book to edit" << std::endl;
    GetBookByName(b);

    int bookId = std::stoi(helpers.EnterData("Enter book id"));
    Book book = b.GetBook(bookId);

    if (book.Id <= 0 || book.Title.empty()) {
        std::cout << "There is no book with this id" << std::endl;
        return;
    }

    std::string bookTitle = book.Title;
    std::string bookAuthor = book.Author;
    int bookYearOfRelease = book.YearOfRelease;
    std::string bookLocationCode = book.LocationCode;
    int genreId = book.GenreId;

    bool isStillEditing = true;
    while (isStillEditing) {
        std::cout << "Which one you want to edit:\n"
                  << "1. Title\n"
                  << "2. Author\n"
                  << "3. Year of release\n"
                  << "4. Location\n"
                  << "5. Genre\n"
                  << "6. Save\n"
                  << "Choose: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookTitle = helpers.EnterData("Enter new title");
                break;
            case 2:
                bookAuthor = helpers.EnterData("Enter new author");
                break;
            case 3:
                bookYearOfRelease = std::stoi(helpers.EnterData("Enter new year of release"));
                break;
            case 4:
                bookLocationCode = helpers.EnterData("Enter new location");
                break;
            case 5: {
                std::vector<Genre> genres = g.GetAllGenres();
                for (auto genre : genres) {
                    std::cout << genre.Id << ". " << genre.Name << std::endl;
                }
                std::cout << "Pick genre id: ";
                std::cin >> genreId;
                break;
            }
            case 6:
                isStillEditing = false;
                break;
            default:
                std::cout << "Unknown option" << std::endl;
        }
    }

    try {
        b.UpdateBook(bookId, bookTitle, bookAuthor, bookYearOfRelease, bookLocationCode, genreId);
        std::cout << "Book updated" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::DeleteBook(BookService &b) {
    GetBookByName(b);
    int bookId = std::stoi(helpers.EnterData("Enter book id to DELETE"));
    try {
        b.DeleteBook(bookId);
        std::cout << "Book deleted" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::GetBookByName(BookService &b) {
    std::string phraseToLookFor = helpers.EnterData("Enter book title or part of it to find");
    std::vector<Book> books = b.GetBooksByDataMatch(phraseToLookFor);
    if (books.empty()) {
        std::cout << "No books found" << std::endl;
        return;
    }
    for (auto book : books) {
        std::cout << book.Id << ". " << book.Title << ". " << book.Author << ". " << book.YearOfRelease << std::endl;
    }
}

void BookMenu::AddBookCopy(BookService &b) {
    GetBookByName(b);
    int bookId = std::stoi(helpers.EnterData("Enter book id"));
    std::cout << "Conditions: poor, average, good, new" << std::endl;
    std::string condition = helpers.EnterData("Enter condition");
    try {
        b.AddBookCopy(bookId, condition);
        std::cout << "Copy added" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::EditBookCopy(BookService &b) {
    GetBookByName(b);
    int bookId = std::stoi(helpers.EnterData("Enter book id to see copies"));

    std::vector<BookCopy> copies = b.FindBookCopies(bookId);
    if (copies.empty()) {
        std::cout << "No copies found" << std::endl;
        return;
    }
    for (auto copy : copies) {
        std::cout << copy.Id << ". Condition: " << copy.Condition << std::endl;
    }

    int copyId = std::stoi(helpers.EnterData("Enter copy id"));
    std::cout << "Conditions: poor, average, good, new" << std::endl;
    std::string condition = helpers.EnterData("Enter new condition");

    try {
        b.UpdateBookCopy(copyId, condition);
        std::cout << "Copy updated" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::DeleteBookCopy(BookService &b) {
    GetBookByName(b);
    int bookId = std::stoi(helpers.EnterData("Enter book id to see copies"));

    std::vector<BookCopy> copies = b.FindBookCopies(bookId);
    if (copies.empty()) {
        std::cout << "No copies found" << std::endl;
        return;
    }
    for (auto copy : copies) {
        std::cout << copy.Id << ". Condition: " << copy.Condition << std::endl;
    }

    int copyId = std::stoi(helpers.EnterData("Enter copy id to DELETE"));
    try {
        b.DeleteBookCopy(copyId);
        std::cout << "Copy deleted" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void BookMenu::Show(BookService &b, GenreService &g) {
    int choice;
    do {
        std::cout << "\n=== BOOK MENU ===\n";
        std::cout << "1. Books\n";
        std::cout << "2. Copies\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: ShowBooksMenu(b, g); break;
            case 2: ShowCopiesMenu(b); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}

void BookMenu::ShowBooksMenu(BookService &b, GenreService &g) {
    int choice;
    do {
        std::cout << "\n=== BOOKS ===\n";
        std::cout << "1. Add book\n";
        std::cout << "2. Show all books\n";
        std::cout << "3. Find by id\n";
        std::cout << "4. Find by name\n";
        std::cout << "5. Edit book\n";
        std::cout << "6. Delete book\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: AddBook(b, g); break;
            case 2: GetAllBooks(b); break;
            case 3: GetBookById(b); break;
            case 4: GetBookByName(b); break;
            case 5: EditBook(b, g); break;
            case 6: DeleteBook(b); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}

void BookMenu::ShowCopiesMenu(BookService &b) {
    int choice;
    do {
        std::cout << "\n=== COPIES ===\n";
        std::cout << "1. Add copy\n";
        std::cout << "2. Show copies of book\n";
        std::cout << "3. Edit copy condition\n";
        std::cout << "4. Delete copy\n";
        std::cout << "0. Back\n";

        choice = helpers.EnterInt("Choose");

        switch (choice) {
            case 1: AddBookCopy(b); break;
            case 2: {
                GetBookByName(b);
                int bookId = helpers.EnterInt("Enter book id");
                auto copies = b.FindBookCopies(bookId);
                for (auto copy : copies) {
                    std::cout << copy.Id << ". Condition: " << copy.Condition << std::endl;
                }
                break;
            }
            case 3: EditBookCopy(b); break;
            case 4: DeleteBookCopy(b); break;
            case 0: break;
            default: std::cout << "Unknown option\n";
        }
    } while (choice != 0);
}