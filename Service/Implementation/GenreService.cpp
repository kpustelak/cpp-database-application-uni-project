//
// Created by kornel on 3/24/26.
//

#include "../Header/GenreService.h"

#include <stdexcept>

void GenreService::Add(const std::string& name, const std::string& description) {
    if (name.size() <= 2 || description.size() <= 1)
        throw std::invalid_argument("Nazwa musi mieć >2 znaki, opis >1 znak");

    auto genre = Genre(0, name, description);
    _repository.add(genre);
}

Genre GenreService::GetById(int id) {
    if (id > 0) {
        return _repository.findById(id);
    }
    throw std::invalid_argument("Id must be greater than 0");
}

std::vector<Genre> GenreService::GetAll() {
    return _repository.findAll();
}

void GenreService::Delete(int id) {
    if (id <= 0) {
        throw std::invalid_argument("Id must be greater than 0");
    }
    Genre genre = _repository.findById(id);
    if (genre.Id != 0 && !_repository.doesGenreHaveBooks(id)) {
        _repository.deleteById(id);
    } else {
        throw std::runtime_error("Genre does not exist or still has related books");
    }
}

void GenreService::Update(const Genre& existingGenre) {
    if (existingGenre.Id <= 0) {
        throw std::invalid_argument("Id must be greater than 0");
    }
    if (existingGenre.Name.size() <= 2 || existingGenre.Description.size() <= 1) {
        throw std::invalid_argument("Nazwa musi mieć >2 znaki, opis >1 znak");
    }
    Genre existing = _repository.findById(existingGenre.Id);
    if (existing.Id == 0) {
        throw std::runtime_error("No genre found");
    }
    _repository.update(existingGenre);
}