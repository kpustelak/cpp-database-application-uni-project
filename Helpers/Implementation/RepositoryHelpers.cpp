//
// Created by kornel on 4/6/26.
//

#include "../Header/RepositoryHelpers.h"

#include <iostream>

void RepositoryHelpers::PGResCommandHandler(PGresult* res) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
}

void RepositoryHelpers::PGResCommandTuple(PGresult* res) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Błąd: " << PQresultErrorMessage(res) << std::endl;
    }
}