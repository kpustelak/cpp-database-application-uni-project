//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKREPOSITORY_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKREPOSITORY_H

#include <libpq-fe.h>
#include <vector>

#include "../../Helpers/Header/RepositoryHelpers.h"
#include "../../Models/Book.h"
#include "../../Models/BookCopy.h"

class BookRepository {
private:
    PGconn* Conn ;
    RepositoryHelpers helpers;
public:
    void add(Book book);
    std::vector<Book> findAll();
    Book findById(int id);
    void update(Book book);
    void deleteById(int id);
    bool doesBookExist(int id);

    void updateCopyCondition(int copy_id, std::string condition);
    void deleteCopy(int copy_id);
    bool isConditionValid(std::string condition);
    bool doesCopyExist(int copy_id);

    void addCopy(int book_id, std::string condition);
    std::vector<BookCopy> findCopiesByBookId(int book_id);

    BookRepository(PGconn* conn) {
        Conn = conn;
    }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKREPOSITORY_H