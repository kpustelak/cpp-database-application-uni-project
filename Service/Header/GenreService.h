//
// Created by kornel on 3/24/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H

#include <string>
#include <vector>
#include "../../Repositories/Header/GenreRepository.h"

class GenreService {
private:
    GenreRepository _repository;

public:
    GenreService(PGconn* conn) : _repository(conn) {}

    void Add(const std::string& name, const std::string& description);
    Genre GetById(int id);
    std::vector<Genre> GetAll();
    void Update(const Genre& existingGenre);
    void Delete(int id);
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRESERVICE_H