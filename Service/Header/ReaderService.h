//
// Created by kornel on 3/26/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H
#include <format>
#include <libpq-fe.h>
#include <string>
#include <vector>
#include "../../Models/Reader.h"
#include "../../Repositories/Header/ReaderRepository.h"


class ReaderService {
private:
    ReaderRepository _repository;
public:
    void Add(std::string name, std::string surname, std::string phoneNumber, std::string email);
    std::vector<Reader> GetAll();
    Reader GetById(int id);
    void Update(int id, std::string name, std::string surname, std::string phoneNumber, std::string email);
    void Delete(int id);
    std::vector<Reader> GetByNameOrSurnameMatch(std::string name);

    ReaderService(PGconn* conn): _repository(conn) {  }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_READERSERVICE_H