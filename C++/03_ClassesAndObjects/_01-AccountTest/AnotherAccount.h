// Contains a name and functions to set and get name

#include <string>

#pragma once

class AnotherAccount {
    public:
        void setName(std::string);

        std::string getName() const;
    private:
        std::string name;
};