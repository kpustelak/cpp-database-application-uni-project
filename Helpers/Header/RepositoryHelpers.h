//
// Created by kornel on 4/6/26.
//

#ifndef CPP_DATABASE_APPLICATION_UNI_PROJECT_REPOSITORYHELPERS_H
#define CPP_DATABASE_APPLICATION_UNI_PROJECT_REPOSITORYHELPERS_H
#include <libpq-fe.h>


class RepositoryHelpers {
public:
    void PGResCommandHandler(PGresult* res);
    void PGResCommandTuple(PGresult* res);
};


#endif //CPP_DATABASE_APPLICATION_UNI_PROJECT_REPOSITORYHELPERS_H