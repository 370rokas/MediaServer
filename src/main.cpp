#include <iostream>
#include <sqlite3.h>

#include "Database.hpp"

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);

    if( rc ) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return(0);
    } else {
        std::cout << "Database works :) " << std::endl;
    }

    sqlite3_close(db);
    return 0;
}
