//
// Created by kornel on 3/29/26.
//

#include "LoanService.h"

#include <stdexcept>

void LoanService::Add(int reader_id, int book_copies_id) {
    _repository.add(reader_id, book_copies_id);
}
void LoanService::ReturnBook(int loan_id) {
    if (_repository.isLoanExistingById(loan_id)) {
        _repository.returnBook(loan_id);
    }else {
        throw std::runtime_error("No book found");
    }

}
bool LoanService::IsCopyAvailable(int book_copy_id) {
    return _repository.isCopyAvailable(book_copy_id);
}

std::vector<Loan> LoanService::FindAllActive() {
    return _repository.findAllActive();
}
std::vector<Loan> LoanService::FindOverdue() {
    return _repository.findOverdue();
}
std::vector<Loan> LoanService::FindByReaderId(int reader_id) {
    return _repository.findByReaderId(reader_id);
}