//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREREPOSITORY_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREREPOSITORY_H
#include <libpq-fe.h>
#include <vector>
#include "../Models/Genre.h"

class GenreRepository {
private:
    PGconn* Conn ;
public:
    void add(Genre genre);
    std::vector<Genre> findAll();
    Genre findById(int id);
    void update(Genre reader);
    void deleteById(int id);
    bool doesGenreHaveBooks(int id);

    GenreRepository(PGconn* conn) {
        Conn = conn;
    }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_GENREREPOSITORY_H