//
// Created by kornel on 3/19/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_READER_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_READER_H
#include <string>


class Reader {
public:
    int Id = 0;
    std::string Name;
    std::string Surname;
    std::string PhoneNumber;
    std::string Email;
    Reader(int id, std::string name, std::string surname, std::string phoneNumber, std::string email)
    : Id(id), Name(name),Surname(surname), PhoneNumber(phoneNumber), Email(email){}
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_READER_H