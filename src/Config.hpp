//
// Created by rokas on 3/11/22.
//

#ifndef WUSEMEDIASERVER_CONFIG_HPP
#define WUSEMEDIASERVER_CONFIG_HPP

#include <string>
#include <tao/json.hpp>

class Config {
    public:
        void Open(std::string File);
        tao::json::value Read();
        bool Write(tao::json::value Data);
    private:
        std::string DefaultConfig =
R""""({
    "DatabaseFile":"Database.db"
})"""";
        std::string Path;
};

#endif //WUSEMEDIASERVER_CONFIG_HPP
