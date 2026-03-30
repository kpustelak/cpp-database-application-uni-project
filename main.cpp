#include <iostream>
#include <libpq-fe.h>
#include "Menus/GenreMenu.h"
#include "Menus/BookMenu.h"
#include "Service/GenreService.h"
#include "Service/BookService.h"

int main() {
    PGconn* conn = PQconnectdb("host=localhost port=5433 dbname=library user=root password=password");

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Błąd połączenia: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    std::cout << "Połączono z bazą!" << std::endl;

    GenreService genreService(conn);
    BookService bookService(conn);
    GenreMenu genreMenu;
    BookMenu bookMenu;

    int choice;
    do {
        std::cout << "\n=== MENU GŁÓWNE ===\n";
        std::cout << "1. Gatunki\n";
        std::cout << "2. Książki\n";
        std::cout << "0. Wyjście\n";
        std::cout << "Wybierz: ";
        std::cin >> choice;

        switch (choice) {
            case 1: genreMenu.Show(genreService); break;
            case 2: bookMenu.Show(bookService, genreService); break;
            case 0: std::cout << "Do widzenia!\n"; break;
            default: std::cout << "Nieznana opcja.\n";
        }
    } while (choice != 0);

    PQfinish(conn);
    return 0;
}