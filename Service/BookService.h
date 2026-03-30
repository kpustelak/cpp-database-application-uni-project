//
// Created by kornel on 3/26/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H
#include <string>
#include <vector>

#include "../Models/Book.h"
#include "../Repositories/BookRepository.h"
#include "../Repositories/GenreRepository.h"

class BookService {
private:
    GenreRepository _genreRepository;
    BookRepository _repository;
public:
    void AddNewBook(std::string title, std::string author, int yearOfRelease, std::string locationCode, int genreId);
    Book GetBook(int id);
    std::vector<Book> GetAllBooks();
    void UpdateBook(int id, std::string Title, std::string Author, int YearOfRelease, std::string LocationCode, int genreId);
    void DeleteBook(int id);

    std::vector<Book> GetBooksByDataMatch(std::string phraseToLookFor);

    void AddBookCopy(int book_id, std::string condition);
    void UpdateBookCopy(int copy_id, std::string condition);
    void DeleteBookCopy(int copy_id);
    std::vector<BookCopy> FindBookCopies(int book_id);

    BookService(PGconn* conn): _repository(conn), _genreRepository(conn) {  }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H