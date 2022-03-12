//
// Created by rokas on 3/12/22.
//

#ifndef WUSEMEDIASERVER_DATABASECONTROL_HPP
#define WUSEMEDIASERVER_DATABASECONTROL_HPP

#include "Database.hpp"

namespace DB {
    enum DBActionState {
        Fail = 0,
        Success = 1,
        FileError = 2,
        DatabaseUninitialized = 3
    };

    std::pair<DBActionState, int> CreateFile(Database db, std::string Path, std::string Location);
}

#endif //WUSEMEDIASERVER_DATABASECONTROL_HPP
