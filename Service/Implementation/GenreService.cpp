//
// Created by kornel on 3/24/26.
//

#include "../Header/GenreService.h"

#include <iostream>

void GenreService::AddNewGenre(std::string name, std::string description) {
    if (name.size() <= 2 || description.size() <= 1)
        throw std::invalid_argument("Nazwa musi mieć >2 znaki, opis >1 znak");

    auto genre = Genre(0,name,description);
    _repository.add(genre);

}

Genre GenreService::GetGenreById(int id) {
    if (id > 0 ) {
        return _repository.findById(id);
    }
    throw std::invalid_argument("Id must be greater than 0");
}

std::vector<Genre> GenreService::GetAllGenres() {
    return _repository.findAll();
}

void GenreService::DeleteGenreById(int id) {
    Genre genre = _repository.findById(id);
    if (genre.Id != 0 && !_repository.doesGenreHaveBooks(id)) {
        _repository.deleteById(id);
    }else {
        std::cerr<<"Genre is not existing or books are still connected with this genre."<< std::endl;
    }
}

void GenreService::UpdateGenreById(Genre existingGenre) {
    if (existingGenre.Id != 0) {
        _repository.update(existingGenre);
    }
}