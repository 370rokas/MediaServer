//
// Created by rokas on 3/12/22.
//

#include "DatabaseControl.hpp"

#include <filesystem>
#include <iostream>
#include <random>

using namespace DB;

using std::filesystem::path;
using std::filesystem::copy;
using std::filesystem::exists;
using std::filesystem::create_directories;

using std::pair;
using std::make_pair;

static std::string random_id(std::size_t len)
{
    static const std::string_view hex_chars = "0123456789abcdef";
    using Generator = std::mt19937;

    Generator gen{std::random_device{}()};

    std::string uuid;
    uuid.reserve(len);

    while (uuid.size() < len) {
        auto n = gen();
        for (auto i = Generator::max();  i & 0x8 && uuid.size() < len;  i >>= 4) {
            uuid += hex_chars[n & 0xf];
            n >>= 4;
        }
    }

    return uuid;
}

std::pair<DBActionState, int> DB::CreateFile(Database db, const std::string& Path, const std::string& Location) {
    const path FilePath = Path;
    const path FileDestination = Location;

    if (!exists(FilePath)) {
        return make_pair(DBActionState::FileError, 0);
    }

    if (!db.GetInitializationState()) {
        return make_pair(DBActionState::DatabaseUninitialized, 0);
    }

    if (!exists(FileDestination)) {
        if (!create_directories(FileDestination)) {
            return make_pair(DBActionState::FileError, 0);
        }
    }

    std::string NewFilename;
    while (NewFilename.empty()) {
        path GeneratedFilename = random_id(36) + FilePath.extension().string();
        if (!exists(GeneratedFilename)) {
            NewFilename = GeneratedFilename.string();
        }
    }

    path CopiedFile = Location + NewFilename;
    copy(FilePath, CopiedFile);

    std::string SQLQuery = "INSERT INTO Files (location, filename) VALUES ('"+FileDestination.string()+"','"+NewFilename+"');";
    if (!db.ExecMultiple(SQLQuery)) {
        return make_pair(DBActionState::SQLError, 0);
    }

    auto Results = db.GetValueByRowId("Files", db.GetLastInsertRowId(), "file_id");

    return make_pair(DBActionState::Success, std::stoi(Results));
}
