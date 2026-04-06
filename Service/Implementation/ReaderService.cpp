//
// Created by kornel on 3/26/26.
//

#include "../Header/ReaderService.h"

#include <stdexcept>

void ReaderService::Add(const std::string& name, const std::string& surname, const std::string& phoneNumber, const std::string& email) {
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
    return _repository.findByPhrase(phraseToLookFor);
}