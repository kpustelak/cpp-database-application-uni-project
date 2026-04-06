//
// Created by kornel on 3/26/26.
//

#include "../Header/BookService.h"

#include <stdexcept>

void BookService::Add(const std::string& title, const std::string& author, int yearOfRelease, const std::string& locationCode, int genreId) {
    Genre g = _genreRepository.findById(genreId);
    if (g.Id == 0) { throw std::runtime_error("No genre found"); }

    Book bookToAdd = Book(0, title, author, yearOfRelease, locationCode, genreId);
    _repository.add(bookToAdd);
}

Book BookService::GetById(int id) {
    return _repository.findById(id);
}

std::vector<Book> BookService::GetAll() {
    return _repository.findAll();
}

void BookService::Update(int id, const std::string& title, const std::string& author, int yearOfRelease, const std::string& locationCode, int genreId) {
    if (!_repository.doesBookExist(id)) {
        throw std::runtime_error("No book found");
    } else {
        Book newBookVersion = Book(id, title, author, yearOfRelease, locationCode, genreId);
        _repository.update(newBookVersion);
    }
}

void BookService::Delete(int id) {
    _repository.deleteById(id);
}

void BookService::AddCopy(int book_id, const std::string& condition) {
    if (!_repository.doesBookExist(book_id)) {
        throw std::runtime_error("No book found");
    }
    _repository.addCopy(book_id, condition);
}

void BookService::UpdateCopy(int copy_id, const std::string& condition) {
    if (_repository.isConditionValid(condition) && _repository.doesCopyExist(copy_id)) {
        _repository.updateCopyCondition(copy_id, condition);
    } else {
        throw std::runtime_error("No copy found or invalid condition");
    }
}

void BookService::DeleteCopy(int copy_id) {
    _repository.deleteCopy(copy_id);
}

std::vector<BookCopy> BookService::GetCopies(int book_id) {
    return _repository.findCopiesByBookId(book_id);
}

std::vector<Book> BookService::GetByPhrase(const std::string& phraseToLookFor) {
    std::vector<Book> allBooks = _repository.findAll();
    std::vector<Book> matches;
    for (const auto& book : allBooks) {
        if (book.Author.find(phraseToLookFor) != std::string::npos ||
            book.Title.find(phraseToLookFor) != std::string::npos) {
            matches.push_back(book);
        }
    }
    return matches;
}