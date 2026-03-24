//
// Created by kornel on 3/24/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H
#include "../Repositories/GenreRepository.h"


class GenreService {
private:
    GenreRepository _repository;
public:
    void AddNewGenre(std::string name, std::string description);
    Genre GetGenreById(int id);
    std::vector<Genre> GetAllGenres();
    void UpdateGenreById(Genre existingGenre);
    void DeleteGenreById(int id);

    GenreService(PGconn* conn) : _repository(conn) {}

};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H