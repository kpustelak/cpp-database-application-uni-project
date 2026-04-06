//
// Created by kornel on 3/26/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H

#include <string>
#include <vector>

#include "../../Models/Book.h"
#include "../../Repositories/Header/BookRepository.h"
#include "../../Repositories/Header/GenreRepository.h"

class BookService {
private:
    BookRepository _repository;
    GenreRepository _genreRepository;

public:
    BookService(PGconn* conn) : _repository(conn), _genreRepository(conn) {}

    void Add(const std::string& title, const std::string& author, int yearOfRelease, const std::string& locationCode, int genreId);
    Book GetById(int id);
    std::vector<Book> GetAll();
    void Update(int id, const std::string& title, const std::string& author, int yearOfRelease, const std::string& locationCode, int genreId);
    void Delete(int id);

    std::vector<Book> GetByPhrase(const std::string& phraseToLookFor);

    void AddCopy(int book_id, const std::string& condition);
    void UpdateCopy(int copy_id, const std::string& condition);
    void DeleteCopy(int copy_id);
    std::vector<BookCopy> GetCopies(int book_id);
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKSERVICE_H