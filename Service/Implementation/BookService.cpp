//
// Created by kornel on 3/26/26.
//

#include "../Header/BookService.h"

#include <stdexcept>

void BookService::AddNewBook(std::string title, std::string author, int yearOfRelease, std::string locationCode, int genreId) {
    Genre g = _genreRepository.findById(genreId);
    if (g.Id == 0) { throw std::runtime_error("No genre found");}

    Book bookToAdd = Book(0, title, author, yearOfRelease, locationCode, genreId );
    _repository.add(bookToAdd);

}
Book BookService::GetBook(int id) {
    return _repository.findById(id);
}
std::vector<Book> BookService::GetAllBooks() {
    return _repository.findAll();
}

void BookService::UpdateBook(int id, std::string title, std::string author, int yearOfRelease, std::string locationCode, int genreId) {
    if (!_repository.doesBookExist(id)) {
        throw std::runtime_error("No book found");
    }else {
        Book newBookVersion = Book(id,title,author,yearOfRelease,locationCode,genreId);
        _repository.update(newBookVersion);
    }
}
void BookService::DeleteBook(int id) {
    _repository.deleteById(id);
}

void BookService::AddBookCopy(int book_id, std::string condition) {
    if (!_repository.doesBookExist(book_id)) {
        throw std::runtime_error("No book found");
    }
    _repository.addCopy(book_id, condition);
}
void BookService::UpdateBookCopy(int copy_id, std::string condition) {
    if (_repository.isConditionValid(condition) && _repository.doesCopyExist(copy_id)) {
        _repository.updateCopyCondition(copy_id, condition);
    } else {
        throw std::runtime_error("No copy found or invalid condition");
    }
}
void BookService::DeleteBookCopy(int copy_id) {
    _repository.deleteCopy(copy_id);
}
std::vector<BookCopy> BookService::FindBookCopies(int book_id) {
    return _repository.findCopiesByBookId(book_id);
}

std::vector<Book> BookService::GetBooksByDataMatch(std::string phraseToLookFor) {
    std::vector<Book> allBooks = _repository.findAll();
    std::vector<Book> matches;
    for (auto book : allBooks) {
        if (book.Author.find(phraseToLookFor) != std::string::npos ||
            book.Title.find(phraseToLookFor) != std::string::npos) {
            matches.push_back(book);
            }
    }
    return matches;
}