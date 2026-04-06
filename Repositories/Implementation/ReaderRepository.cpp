#include "../Header/ReaderRepository.h"
#include <iostream>

void ReaderRepository::add(Reader reader) {
    const char* params[4] = {
        reader.Name.c_str(),
        reader.Surname.c_str(),
        reader.PhoneNumber.c_str(),
        reader.Email.c_str()
    };
    PGresult* res = PQexecParams(Conn,
        "INSERT INTO readers (name, surname, phone_number, email) VALUES ($1, $2, $3, $4)",
        4, NULL, params, NULL, NULL, 0);

    helpers.PGResCommandHandler(res);
    PQclear(res);
}

std::vector<Reader> ReaderRepository::findAll() {
    PGresult* res = PQexec(Conn, "SELECT * FROM readers");

    helpers.PGResCommandTuple(res);

    std::vector<Reader> readers;
    std::vector<std::string> params(PQnfields(res));
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
    const char* param[1] = { idString.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT * FROM readers WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);

    if (PQntuples(res) == 0) {
        PQclear(res);
        return Reader(0, "", "", "", "");
    }
    std::vector<std::string> params(PQnfields(res));
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
        "UPDATE readers SET name = $1, surname = $2, phone_number = $3, email = $4 WHERE id = $5",
        5, NULL, params, NULL, NULL, 0);

    helpers.PGResCommandHandler(res);
    PQclear(res);
}

void ReaderRepository::deleteById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = { idString.c_str() };
    PGresult* res = PQexecParams(Conn,
        "DELETE FROM readers WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandHandler(res);
    PQclear(res);
}

std::vector<Reader> ReaderRepository::findByPhrase(std::string phrase) {
    std::string likePhrase = "%" + phrase + "%";
    const char* params[2] = { likePhrase.c_str(), likePhrase.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT * FROM readers WHERE name ILIKE $1 OR surname ILIKE $2",
        2, NULL, params, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);

    std::vector<Reader> readers;
    std::vector<std::string> row(PQnfields(res));
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            row[j] = PQgetvalue(res, i, j);
        }
        readers.push_back(Reader(std::stoi(row[0]), row[1], row[2], row[3], row[4]));
    }
    PQclear(res);
    return readers;
}

bool ReaderRepository::doesReaderExist(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = { idString.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT 1 FROM readers WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);
    bool exists = PQntuples(res) > 0;
    PQclear(res);
    return exists;
}