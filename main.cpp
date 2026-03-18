#include <iostream>
#include <libpq-fe.h>

int main() {
    PGconn* conn = PQconnectdb("host=localhost port=5433 dbname=library user=root password=password");

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Błąd połączenia: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    std::cout << "Połączono z bazą!" << std::endl;
    PQfinish(conn);
    return 0;
}