#include <iostream>

#include <lua.hpp>

#include "Config.hpp"
#include "GUI/Console.hpp"
#include "Database/DatabaseControl.hpp"

bool* run_cli = new bool(true);

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
    /*int err;

    Console console;
    console.RunConsole(run_cli);

    while (run_cli) {};
    while (run_cli) {
        std::string input;
        std::cin >> input;

        if (input == "exit") {run = false;} else {
            err = luaL_loadstring(L, input.c_str()) || lua_pcall(L, 0, 0, 0);
            if (err) {
                std::cout << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }
    }*/

    lua_close(L);
}
