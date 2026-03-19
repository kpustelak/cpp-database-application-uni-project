//
// Created by kornel on 3/19/26.
//

#include "LoanRepository.h"

#include <iostream>
#include <ostream>

void LoanRepository::add(int reader_id, int book_copies_id) {
    std::string readerId = std::to_string(reader_id);
    std::string copyOfBookId = std::to_string(book_copies_id);
    const char* param[2] = {
        readerId.c_str(),
        copyOfBookId.c_str()
    };

    PGresult* res = PQexecParams(Conn,"INSERT INTO loans (reader_id, book_copies_id) VALUES ($1, $2)",
                                      2,NULL,param,NULL,NULL,0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}
void LoanRepository::returnBook(int loan_id) {
    std::string idString = std::to_string(loan_id);
    const char* param[1] = {

        idString.c_str()
    };

    PGresult* res = PQexecParams(Conn,"UPDATE loans SET is_returned = TRUE, return_date = CURRENT_DATE WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
       std::cerr<<"Błąd: "<< PQresultErrorMessage(res) << std::endl;
    }

    PQclear(res);
}
bool LoanRepository::isCopyAvailable(int book_copy_id) {
    std::string copyOfBookId = std::to_string(book_copy_id);
    const char* param[1] = {
        copyOfBookId.c_str()
    };
    PGresult* res = PQexecParams(Conn,"SELECT * FROM book_copies WHERE id = $1",
        1, NULL, param, NULL, NULL, 0);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr<<"Błąd: "<< PQresultErrorMessage(res) << std::endl;
    }
    PQclear(res);
    if (PQntuples(res) == 0 ) {
        return false;
    }
    return true;
}

std::vector<Loan> LoanRepository::findAllActive() {

}

std::vector<Loan> LoanRepository::findOverdue() {

}
std::vector<Loan> LoanRepository::findByReaderId(int reader_id) {

}