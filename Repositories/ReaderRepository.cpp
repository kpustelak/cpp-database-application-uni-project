//
// Created by kornel on 3/19/26.
//

#include "ReaderRepository.h"

#include <iostream>

void ReaderRepository::add(Reader reader) {
    const char* params[4] = {
        reader.Name.c_str(),
        reader.Surname.c_str(),
        reader.PhoneNumber.c_str(),
        reader.Email.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "INSERT INTO readers (Name, Surname, PhoneNumber, Email) VALUES ($1, $2, $3, $4)",
            4, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}
std::vector<Reader> ReaderRepository::findAll() {
    PGresult* res = PQexec(Conn,
            "SELECT * FROM readers"
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
    std::vector<Reader> readers;
    const char* params[PQnfields(res)];
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        readers.push_back(Reader(std::stoi(params[0]), params[1], params[2], params[3], params[4]));
    }
    PQclear(res);
    return readers;
}
Reader ReaderRepository::findById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "SELECT * FROM readers WHERE id = $1",
            1, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    const char* params[PQnfields(res)];
    for (int i = 0; i < PQnfields(res); i++) {
        params[i] = PQgetvalue(res, 0, i);
    }

    PQclear(res);
    return Reader(std::stoi(params[0]), params[1], params[2], params[3], params[4]);
}
void ReaderRepository::update(Reader reader) {
    std::string idString = std::to_string(reader.Id);
    const char* params[5] = {
        reader.Name.c_str(),
        reader.Surname.c_str(),
        reader.PhoneNumber.c_str(),
        reader.Email.c_str(),
        idString.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "UPDATE readers SET Name = $1, Surname = $2, PhoneNumber = $3, Email = $4 WHERE id = $5",
            5, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}
void ReaderRepository::deleteById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "DELETE FROM readers WHERE id = $1",
            1, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}