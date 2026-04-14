#include <iostream>
#include <libpq-fe.h>
#include "Menus/Header/GenreMenu.h"
#include "Menus/Header/BookMenu.h"
#include "Menus/Header/ReaderMenu.h"
#include "Menus/Header/LoanMenu.h"
#include "Service/Header/GenreService.h"
#include "Service/Header/BookService.h"
#include "Service/Header/ReaderService.h"
#include "Service/Header/LoanService.h"
#include "Helpers/Header/Helpers.h"

int main() {
    PGconn* conn = PQconnectdb("host=localhost port=5433 dbname=library user=root password=password");

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection error: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    GenreService genreService(conn);
    BookService bookService(conn);
    ReaderService readerService(conn);
    LoanService loanService(conn);

    GenreMenu genreMenu;
    BookMenu bookMenu;
    ReaderMenu readerMenu;
    LoanMenu loanMenu;
    Helpers helpers;

    int choice;
    do {
        helpers.ClearScreen();
        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Genres\n";
        std::cout << "2. Books\n";
        std::cout << "3. Readers\n";
        std::cout << "4. Loans\n";
        std::cout << "0. Exit\n";

        choice = helpers.EnterInt("Pick one");

        switch (choice) {
            case 1: genreMenu.Show(genreService); break;
            case 2: bookMenu.Show(bookService, genreService); break;
            case 3: readerMenu.Show(readerService); break;
            case 4: loanMenu.Show(loanService, readerService, bookService); break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Undefined option.\n";
        }
    } while (choice != 0);

    PQfinish(conn);
    return 0;
}