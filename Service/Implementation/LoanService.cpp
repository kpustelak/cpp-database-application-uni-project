//
// Created by kornel on 3/29/26.
//

#include "../Header/LoanService.h"

#include <stdexcept>

void LoanService::Add(int reader_id, int book_copies_id) {
    if (reader_id <= 0 || book_copies_id <= 0) {
        throw std::invalid_argument("Reader id and copy id must be greater than 0");
    }
    if (!_readerRepository.doesReaderExist(reader_id)) {
        throw std::runtime_error("No reader found");
    }
    if (!_bookRepository.doesCopyExist(book_copies_id)) {
        throw std::runtime_error("No copy found");
    }
    if (!_repository.isCopyAvailable(book_copies_id)) {
        throw std::runtime_error("Book copy is already borrowed");
    }
    _repository.add(reader_id, book_copies_id);
}

void LoanService::ReturnBook(int loan_id) {
    if (loan_id <= 0) {
        throw std::invalid_argument("Loan id must be greater than 0");
    }
    if (_repository.isLoanExistingById(loan_id)) {
        _repository.returnBook(loan_id);
    } else {
        throw std::runtime_error("No book found");
    }
}

bool LoanService::IsCopyAvailable(int book_copy_id) {
    if (book_copy_id <= 0) {
        throw std::invalid_argument("Copy id must be greater than 0");
    }
    if (!_bookRepository.doesCopyExist(book_copy_id)) {
        throw std::runtime_error("No copy found");
    }
    return _repository.isCopyAvailable(book_copy_id);
}

std::vector<Loan> LoanService::GetActive() {
    return _repository.findAllActive();
}

std::vector<Loan> LoanService::GetOverdue() {
    return _repository.findOverdue();
}

std::vector<Loan> LoanService::GetByReaderId(int reader_id) {
    if (reader_id <= 0) {
        throw std::invalid_argument("Reader id must be greater than 0");
    }
    if (!_readerRepository.doesReaderExist(reader_id)) {
        throw std::runtime_error("No reader found");
    }
    return _repository.findByReaderId(reader_id);
}