//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOK_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOK_H
#include <string>


class Book {
public:
    int Id;
    std::string Title;
    std::string Author;
    int YearOfRelease;
    std::string LocationCode;
    int GenreId;

    Book(int id, std::string title, std::string author, int year_of_release, std::string location_code, int genre_id)
        : Id(id), Title(title), Author(author), YearOfRelease(year_of_release), LocationCode(location_code), GenreId(genre_id) {}
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_BOOK_H