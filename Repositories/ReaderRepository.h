#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_READERREPOSITORY_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_READERREPOSITORY_H
#include <libpq-fe.h>
#include <vector>
#include <string>
#include "../Models/Reader.h"

class ReaderRepository {
private:
    PGconn* Conn;
public:
    void add(Reader reader);
    std::vector<Reader> findAll();
    Reader findById(int id);
    void update(Reader reader);
    void deleteById(int id);
    std::vector<Reader> findByPhrase(std::string phrase);
    bool doesReaderExist(int id);

    ReaderRepository(PGconn* conn) { Conn = conn; }
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_READERREPOSITORY_H