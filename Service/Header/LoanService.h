//
// Created by kornel on 3/29/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANSERVICE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANSERVICE_H

#include <vector>
#include "../../Repositories/Header/LoanRepository.h"

class LoanService {
private:
    LoanRepository _repository;

public:
    // --- Konstruktor ---
    LoanService(PGconn* conn) : _repository(conn) {}

    // --- Operacje dziedzinowe wypożyczeń ---
    void Add(int reader_id, int book_copies_id);
    void ReturnBook(int loan_id);

    // --- Kwerendy stanu i weryfikacji ---
    bool IsCopyAvailable(int book_copy_id);
    std::vector<Loan> GetActive();
    std::vector<Loan> GetOverdue();
    std::vector<Loan> GetByReaderId(int reader_id);
};

#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_LOANSERVICE_H