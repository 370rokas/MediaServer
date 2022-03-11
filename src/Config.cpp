//
// Created by rokas on 3/11/22.
//

#include "Config.hpp"

#include <filesystem>
#include <fstream>

using namespace tao;

using std::filesystem::path;
using std::filesystem::exists;

void Config::Open(std::string File) {
    const path ConfigPath = File;

    if (exists(ConfigPath)) {
        (void) json::from_file(File); // Check if JSON is Valid.

        Path = File;
    } else {
        std::ofstream NewFile(ConfigPath.string(), std::ofstream::trunc);
        NewFile << DefaultConfig;
        NewFile.close();

        Path = File;
    }
}

tao::json::value Config::Read() {
    return json::from_file(Path);
}

bool Config::Write(tao::json::value Data) {
    std::string StringifiedData = json::to_string(Data);

    try {
        std::ofstream JsonFile(Path, std::ofstream::trunc);
        JsonFile << Data;
        JsonFile.close();
    } catch (...) {
        return false;
    }

    return true;
}

