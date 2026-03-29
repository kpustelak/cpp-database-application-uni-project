//
// Created by kornel on 3/26/26.
//

#include "ReaderService.h"

#include <stdexcept>

void ReaderService::Add(std::string name, std::string surname, std::string phoneNumber, std::string email) {
    Reader r = Reader(0,name,surname,phoneNumber,email);
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
void ReaderService::Update(int id, std::string name, std::string surname, std::string phoneNumber, std::string email) {
    Reader r = Reader(0,name,surname,phoneNumber,email);
    _repository.update(r);
}
void ReaderService::Delete(int id) {
    if (id <= 0 ) {
        throw std::out_of_range("Cannot find the id of the reader service");
    }
    return _repository.deleteById(id);
}