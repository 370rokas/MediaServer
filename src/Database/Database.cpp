//
// Created by rokas on 3/11/22.
//

#include "Database.hpp"
#include <iostream>
#include <fstream>

std::string ConstCharPtrToString(const char* Source) {
    return reinterpret_cast<const char*>(Source);
}

std::pair<bool, std::vector<std::string>> Database::Query(const std::string& Query) {
    std::vector<std::string> Results;
    sqlite3_stmt* Statement;
    int ReturnCode;

    if (sqlite3_prepare_v2(db, Query.c_str(), -1, &Statement, nullptr) != SQLITE_OK) {
        LastError = "Failed to compile query: " + Query + "\n" + ConstCharPtrToString(sqlite3_errmsg(db));
        return std::make_pair(false, Results);
    }

    while ((ReturnCode = sqlite3_step(Statement)) == SQLITE_ROW) {
        std::string ColumnText(reinterpret_cast<const char*>(
                sqlite3_column_text(Statement, 0)));

        Results.push_back(ColumnText);
    }

    if (ReturnCode != SQLITE_DONE) {
        LastError = "Failed to complete query: " + Query + ", with ReturnCode: " + std::to_string(ReturnCode) + "\n"  + ConstCharPtrToString(sqlite3_errmsg(db));
        return std::make_pair(false, Results);
    }

    return std::make_pair(true, Results);
}

bool Database::ExecMultiple(const std::string& Query) {
    int ReturnCode = 0;

    if (SQLITE_OK != (ReturnCode = sqlite3_exec(db, Query.c_str(), nullptr, nullptr, nullptr))) {
        LastError = "Failed to execute query: " + Query + ", with ReturnCode: " + std::to_string(ReturnCode) + "\n" + ConstCharPtrToString(sqlite3_errmsg(db));
        return false;
    }
    return true;
}

void Database::Initialize(const std::string& filename) {
    if(sqlite3_open(filename.c_str(), &db)) {
        InitializationState = false;
        InitializationMessage = sqlite3_errmsg(db);
        return;
    } else {
        InitializationState = true;
        InitializationMessage = "Success";
    }

    auto TableQuery = Query("SELECT * FROM sqlite_master where type='table'");
    if (!TableQuery.first) {
        InitializationState = false;
        InitializationMessage = GetLastError();

        Close();
        return;
    }

    if (TableQuery.second.empty()) {
        std::ifstream QueryFile("Queries/Initialization.sql");
        if (!QueryFile.is_open()) {
            InitializationState = false;
            InitializationMessage = "Unable to open 'Queries/Initialization.sql'";

            Close();
            return;
        }

        std::string RawQuery((std::istreambuf_iterator<char>(QueryFile)), std::istreambuf_iterator<char>());
        auto CreateTableQuery = ExecMultiple(RawQuery);
        if (!CreateTableQuery) {
            InitializationState = false;
            InitializationMessage = GetLastError();
            std::cout << GetLastError() << std::endl;

            Close();
            return;
        }
    }
}

bool Database::GetInitializationState() {
    return InitializationState;
}

std::string Database::GetInitializationMessage() {
    return InitializationMessage;
}

std::string Database::GetLastError() {
    return LastError;
}

void Database::Close() {
    sqlite3_close(db);
}