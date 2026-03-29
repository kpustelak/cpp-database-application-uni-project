//
// Created by kornel on 3/19/26.
//

#include "GenreRepository.h"

#include <iostream>

void GenreRepository::add(Genre genre) {
    const char* params[2] = {
        genre.Name.c_str(),
        genre.Description.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "INSERT INTO genres (name, description) VALUES ($1, $2)",
            2, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

std::vector<Genre> GenreRepository::findAll() {
    PGresult* res = PQexec(Conn, "SELECT * FROM genres");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    std::vector<Genre> genres;
    std::vector<std::string> params(PQnfields(res));
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        genres.push_back(Genre(std::stoi(params[0]), params[1], params[2]));
    }
    PQclear(res);
    return genres;
}

Genre GenreRepository::findById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = { idString.c_str() };

    PGresult* res = PQexecParams(Conn,
            "SELECT * FROM genres WHERE id = $1",
            1, NULL, param, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    if (PQntuples(res) == 0) {
        PQclear(res);
        return Genre(0, "", "");
    }

    std::vector<std::string> params(PQnfields(res));
    for (int i = 0; i < PQnfields(res); i++) {
        params[i] = PQgetvalue(res, 0, i);
    }
    PQclear(res);
    return Genre(std::stoi(params[0]), params[1], params[2]);
}

void GenreRepository::update(Genre genre) {
    std::string idString = std::to_string(genre.Id);
    const char* params[3] = {
        genre.Name.c_str(),
        genre.Description.c_str(),
        idString.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "UPDATE genres SET name = $1, description = $2 WHERE id = $3",
            3, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

void GenreRepository::deleteById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = { idString.c_str() };

    PGresult* res = PQexecParams(Conn,
            "DELETE FROM genres WHERE id = $1",
            1, NULL, param, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

bool GenreRepository::doesGenreHaveBooks(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = { idString.c_str() };

    PGresult* res = PQexecParams(Conn,
            "SELECT 1 FROM books WHERE id_genre = $1",
            1, NULL, param, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    if (PQntuples(res) != 0) {
        PQclear(res);
        return true;
    }
    PQclear(res);
    return false;
}