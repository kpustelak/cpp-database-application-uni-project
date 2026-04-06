//
// Created by kornel on 3/26/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H

#include <string>
#include <vector>
#include <libpq-fe.h>
#include "../../Models/Reader.h"
#include "../../Repositories/Header/ReaderRepository.h"

class ReaderService {
private:
    ReaderRepository _repository;

public:
    // --- Konstruktor ---
    ReaderService(PGconn* conn) : _repository(conn) {}

    // --- Bazowe operacje CRUD ---
    void Add(const std::string& name, const std::string& surname, const std::string& phoneNumber, const std::string& email);
    Reader GetById(int id);
    std::vector<Reader> GetAll();
    void Update(int id, const std::string& name, const std::string& surname, const std::string& phoneNumber, const std::string& email);
    void Delete(int id);

    // --- Kwerendy zaawansowane ---
    std::vector<Reader> GetByPhrase(const std::string& phraseToLookFor);
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H