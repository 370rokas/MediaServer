#include <iostream>

#include <lua.hpp>

#include "Config.hpp"
#include "GUI/Console.hpp"
#include "Database/DatabaseControl.hpp"

int main() {
    using namespace tao;

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    Config configuration;
    configuration.Open("config.json");
    json::value Settings = configuration.Read();

    Database db;
    db.Initialize(Settings.at("DatabaseFile").get_string());

    if (!db.GetInitializationState()) {
        std::cout << "Failed opening database: " << db.GetInitializationMessage() << std::endl;
        return 1;
    }

    auto CreatedFile = DB::CreateFile(db, "config.json", Settings.at("FileStorageLocation").get_string());
    std::cout << CreatedFile.second << std::endl;

    Console console;
    console.Run();

    lua_close(L);
}
