#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKMENU_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKMENU_H
#include "../Helpers/Helpers.h"
#include "../Service/BookService.h"
#include "../Service/GenreService.h"


class BookMenu {
private:
    Helpers helpers;

    void AddBook(BookService &b, GenreService &g);
    void GetBookById(BookService &b);
    void GetAllBooks(BookService &b);
    void GetBookByName(BookService &b);
    void EditBook(BookService &b, GenreService &g);
    void DeleteBook(BookService &b);

    void AddBookCopy(BookService &b);
    void EditBookCopy(BookService &b);
    void DeleteBookCopy(BookService &b);

    void ShowBooksMenu(BookService &b, GenreService &g);
    void ShowCopiesMenu(BookService &b);

public:
    void Show(BookService &b, GenreService &g);
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKMENU_H