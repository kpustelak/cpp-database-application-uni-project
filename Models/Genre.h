//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRE_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRE_H
#include <string>


class Genre {
public:
    int Id;
    std::string Name;
    std::string Description;

    Genre(int id, std::string name, std::string description)
        : Id(id), Name(name), Description(description){}
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_GENRE_H