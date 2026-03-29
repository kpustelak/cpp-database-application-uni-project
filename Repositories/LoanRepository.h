//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANREPOSITORY_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANREPOSITORY_H
#include <libpq-fe.h>
#include <vector>

#include "../Models/Loan.h"

class LoanRepository {
private:
    PGconn* Conn;
public:
    void add(int reader_id, int book_copies_id);
    void returnBook(int loan_id);
    bool isCopyAvailable(int book_copy_id);

    bool isLoanExistingById(int loan_id);


    std::vector<Loan> findAllActive();
    std::vector<Loan> findOverdue();
    std::vector<Loan> findByReaderId(int reader_id);

    LoanRepository(PGconn* conn) {
        Conn = conn;
    }
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANREPOSITORY_H