//
// Created by rokas on 3/11/22.
//

#ifndef WUSEMEDIASERVER_DATABASE_HPP
#define WUSEMEDIASERVER_DATABASE_HPP

#include <string>
#include <sqlite3.h>
#include <vector>

class Database {
    public:
        void Initialize(const std::string& filename);
        bool GetInitializationState();
        std::string GetInitializationMessage();

        std::pair<bool, std::vector<std::string>> Query(const std::string& Query);
        bool ExecMultiple(const std::string& Query);
        long long GetLastInsertRowId();
        std::string GetValueByRowId(std::string Table, long long RowId, std::string Value);

        std::string GetLastError();
        void Close();
    private:
        bool InitializationState = false;
        std::string InitializationMessage;

        std::string LastError;

        sqlite3 *db;
};

#endif //WUSEMEDIASERVER_DATABASE_HPP
