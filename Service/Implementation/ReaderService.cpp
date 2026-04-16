//
// Created by kornel on 3/26/26.
//

#include "../Header/ReaderService.h"

#include <regex>
#include <stdexcept>

void ReaderService::Add(const std::string& name, const std::string& surname, const std::string& phoneNumber, const std::string& email) {
    static const std::regex emailRegex(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
    static const std::regex phoneRegex(R"(^[0-9+\-\s]{6,20}$)");
    if (name.empty() || surname.empty()) {
        throw std::invalid_argument("Name and surname cannot be empty");
    }
    if (!std::regex_match(email, emailRegex)) {
        throw std::invalid_argument("Invalid email format");
    }
    if (!std::regex_match(phoneNumber, phoneRegex)) {
        throw std::invalid_argument("Invalid phone number format");
    }

    Reader r = Reader(0, name, surname, phoneNumber, email);
    _repository.add(r);
}

std::vector<Reader> ReaderService::GetAll() {
    return _repository.findAll();
}

Reader ReaderService::GetById(int id) {
    if (id <= 0 ) {
        throw std::out_of_range("Cannot find the id of the reader service");
    }
    return _repository.findById(id);
}

void ReaderService::Update(int id, const std::string& name, const std::string& surname, const std::string& phoneNumber, const std::string& email) {
    static const std::regex emailRegex(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
    static const std::regex phoneRegex(R"(^[0-9+\-\s]{6,20}$)");
    if (id <= 0) {
        throw std::invalid_argument("Reader id must be greater than 0");
    }
    if (!_repository.doesReaderExist(id)) {
        throw std::runtime_error("No reader found");
    }
    if (name.empty() || surname.empty()) {
        throw std::invalid_argument("Name and surname cannot be empty");
    }
    if (!std::regex_match(email, emailRegex)) {
        throw std::invalid_argument("Invalid email format");
    }
    if (!std::regex_match(phoneNumber, phoneRegex)) {
        throw std::invalid_argument("Invalid phone number format");
    }

    Reader r = Reader(id, name, surname, phoneNumber, email);
    _repository.update(r);
}

void ReaderService::Delete(int id) {
    if (id <= 0 ) {
        throw std::out_of_range("Cannot find the id of the reader service");
    }
    _repository.deleteById(id);
}

std::vector<Reader> ReaderService::GetByPhrase(const std::string& phraseToLookFor) {
    if (phraseToLookFor.empty()) {
        throw std::invalid_argument("Search phrase cannot be empty");
    }
    return _repository.findByPhrase(phraseToLookFor);
}