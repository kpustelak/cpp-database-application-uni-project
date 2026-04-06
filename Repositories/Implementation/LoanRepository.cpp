#include "../Header/LoanRepository.h"
#include <iostream>

void LoanRepository::add(int reader_id, int book_copies_id) {
    std::string readerId = std::to_string(reader_id);
    std::string copyOfBookId = std::to_string(book_copies_id);
    const char* param[2] = {
        readerId.c_str(),
        copyOfBookId.c_str()
    };
    PGresult* res = PQexecParams(Conn,
        "INSERT INTO loans (reader_id, book_copies_id) VALUES ($1, $2)",
        2, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandHandler(res);
    PQclear(res);
}

void LoanRepository::returnBook(int loan_id) {
    std::string idString = std::to_string(loan_id);
    const char* param[1] = { idString.c_str() };
    PGresult* res = PQexecParams(Conn,
        "UPDATE loans SET is_returned = TRUE, return_date = CURRENT_DATE WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandHandler(res);
    PQclear(res);
}

bool LoanRepository::isCopyAvailable(int book_copy_id) {
    std::string copyId = std::to_string(book_copy_id);
    const char* param[1] = { copyId.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT 1 FROM loans WHERE book_copies_id = $1 AND is_returned = false",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);
    bool borrowed = PQntuples(res) > 0;
    PQclear(res);
    return !borrowed;
}

bool LoanRepository::isLoanExistingById(int loan_id) {
    std::string loanId = std::to_string(loan_id);
    const char* param[1] = { loanId.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT 1 FROM loans WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);
    bool exists = PQntuples(res) > 0;
    PQclear(res);
    return exists;
}

std::vector<Loan> LoanRepository::findAllActive() {
    PGresult* res = PQexec(Conn, "SELECT * FROM loans WHERE is_returned = false");

    helpers.PGResCommandTuple(res);

    std::vector<Loan> loans;
    std::vector<std::string> params(PQnfields(res));
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        loans.emplace_back(
            std::stoi(params[0]),
            std::stoi(params[1]),
            std::stoi(params[2]),
            params[3],
            params[4],
            params[5] == "t"
        );
    }
    PQclear(res);
    return loans;
}

std::vector<Loan> LoanRepository::findOverdue() {
    PGresult* res = PQexec(Conn,
        "SELECT * FROM loans WHERE is_returned = false AND loan_date + INTERVAL '21 days' < CURRENT_DATE");

    helpers.PGResCommandTuple(res);

    std::vector<Loan> loans;
    std::vector<std::string> params(PQnfields(res));
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        loans.emplace_back(
            std::stoi(params[0]),
            std::stoi(params[1]),
            std::stoi(params[2]),
            params[3],
            params[4],
            params[5] == "t"
        );
    }
    PQclear(res);
    return loans;
}

std::vector<Loan> LoanRepository::findByReaderId(int reader_id) {
    std::string readerId = std::to_string(reader_id);
    const char* param[1] = { readerId.c_str() };
    PGresult* res = PQexecParams(Conn,
        "SELECT * FROM loans WHERE reader_id = $1",
        1, NULL, param, NULL, NULL, 0);

    helpers.PGResCommandTuple(res);

    std::vector<Loan> loans;
    std::vector<std::string> params(PQnfields(res));
    for (int i = 0; i < PQntuples(res); i++) {
        for (int j = 0; j < PQnfields(res); j++) {
            params[j] = PQgetvalue(res, i, j);
        }
        loans.emplace_back(
            std::stoi(params[0]),
            std::stoi(params[1]),
            std::stoi(params[2]),
            params[3],
            params[4],
            params[5] == "t"
        );
    }
    PQclear(res);
    return loans;
}