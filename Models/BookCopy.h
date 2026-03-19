//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKCOPY_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKCOPY_H
#include <string>


class BookCopy {
public:
    int Id;
    std::string Condition;
    int BookId;

    BookCopy(int id, std::string condition, int bookId): Id(id), Condition(condition), BookId(bookId) {  }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOKCOPY_H