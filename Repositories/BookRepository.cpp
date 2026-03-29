//
// Created by kornel on 3/19/26.
//

#include "BookRepository.h"

#include <iostream>

void BookRepository::add(Book book) {
    std::string idString = std::to_string(book.Id);
    std::string yearOfReleaseString = std::to_string(book.YearOfRelease);
    std::string genreIdString = std::to_string(book.GenreId);
    const char* params[5] = {
        book.Title.c_str(),
        book.Author.c_str(),
        yearOfReleaseString.c_str(),
        book.LocationCode.c_str(),
        genreIdString.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "INSERT INTO books (title, author,year_of_release,location_code,id_genre) VALUES ($1, $2, $3, $4, $5)",
            5, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

std::vector<Book> BookRepository::findAll() {
    PGresult* res = PQexec(Conn,
            "SELECT * FROM books"
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
    std::vector<Book> books;
    const char* params[PQnfields(res)];
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        books.push_back(Book(std::stoi(params[0]), params[1], params[2],
            std::stoi(params[3]), params[4], std::stoi(params[5])));
    }
    PQclear(res);
    return books;
}
Book BookRepository::findById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "SELECT * FROM books WHERE id = $1",
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
    return Book(std::stoi(params[0]), params[1], params[2],
            std::stoi(params[3]), params[4], std::stoi(params[5]));
}
void BookRepository::update(Book book) {
    std::string idString = std::to_string(book.Id);
    std::string yearOfReleaseString = std::to_string(book.YearOfRelease);
    std::string genreIdString = std::to_string(book.GenreId);
    const char* params[6] = {
        book.Title.c_str(),
        book.Author.c_str(),
        yearOfReleaseString.c_str(),
        book.LocationCode.c_str(),
        genreIdString.c_str(),
        idString.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "UPDATE books SET title = $1, author = $2, "
            "year_of_release = $3, location_code = $4, id_genre = $5 WHERE id = $6",
            6, NULL, params, NULL, NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}
void BookRepository::deleteById(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "DELETE FROM books WHERE id = $1",
            1, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

void BookRepository::addCopy(int book_id, std::string condition) {
    std::string originalBookString = std::to_string(book_id);
    const char* param[2] = {
        condition.c_str(),
        originalBookString.c_str()
    };

    PGresult* res = PQexecParams(Conn,
            "INSERT INTO book_copies (condition, id_book) VALUES ($1, $2)",
            2, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

void BookRepository::updateCopyCondition(int copy_id, std::string condition) {
    std::string copyIdString = std::to_string(copy_id);
    const char* param[2] = {
        condition.c_str(),
        copyIdString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
        "UPDATE book_copies SET condition = $1 WHERE id = $2",
        2, NULL, param, NULL , NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
    PQclear(res);
}
void BookRepository::deleteCopy(int copy_id) {
    std::string copyIdString = std::to_string(copy_id);
    const char* param[1] = {
        copyIdString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "DELETE FROM book_copies WHERE id = $1",
            1, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}

std::vector<BookCopy> BookRepository::findCopiesByBookId(int book_id) {
    std::string idString = std::to_string(book_id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
        "SELECT * FROM book_copies WHERE id_book = $1",
        1, NULL, param, NULL , NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    std::vector<BookCopy> bookCopies;
    const char* params[PQnfields(res)];
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        bookCopies.push_back(BookCopy(std::stoi(params[0]), params[1], std::stoi(params[2])));
    }
    PQclear(res);
    return bookCopies;
}

bool BookRepository::doesBookExist(int id) {
    std::string idString = std::to_string(id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
            "SELECT * FROM books WHERE id = $1",
            1, NULL, param, NULL , NULL, 0
        );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
    PQclear(res);
    if (param[0] == 0) {
        return false;
    }
    return true;
}

bool BookRepository::isConditionValid(std::string condition) {
    std::string conditionString[4] = {"poor", "average", "good", "new"};
    for (int i = 0; i < 4; i++) {
        if (conditionString[i] == condition) {
            return true;
        }
    }
    return false;
}

bool BookRepository::doesCopyExist(int copy_id) {
    std::string idString = std::to_string(copy_id);
    const char* param[1] = {
        idString.c_str()
    };
    PGresult* res = PQexecParams(Conn,
        "SELECT * FROM book_copies WHERE id = $1",
        1, NULL, param, NULL , NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
    PQclear(res);
    if (param[0] == 0) {
        return false;
    }
    return true;
}