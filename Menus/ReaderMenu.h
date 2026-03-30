//
// Created by kornel on 3/30/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_READERMENU_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_READERMENU_H
#include "../Helpers/Helpers.h"
#include "../Service/ReaderService.h"


class ReaderMenu {
private:
    Helpers helpers;
public:
    void AddReader(ReaderService &r);
    void ShowAllReaders(ReaderService &r);
    void GetReaderById(ReaderService &r);
    void GetReaderByNameOrSurname(ReaderService &r);
    void EditReader(ReaderService &r);
    void DeleteReader(ReaderService &r);

    void Show(ReaderService &r);
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_READERMENU_H