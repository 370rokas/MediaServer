#include <iostream>

#include "Config.hpp"
#include "Database/Database.hpp"

bool run = true;

int main() {
    using namespace tao;

    Config configuration;
    configuration.Open("config.json");
    json::value Settings = configuration.Read();

    Database db;
    db.Initialize(Settings.at("DatabaseFile").get_string());

    if (!db.GetInitializationState()) {
        std::cout << "Failed opening database: " << db.GetInitializationMessage() << std::endl;
        return 1;
    }

    while (run) {
        std::string input;
        std::cin >> input;

        if (input == "exit") run=false;
    }

    return 0;
}
