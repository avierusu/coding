#include "AnotherAccount.h"

void AnotherAccount::setName(std::string accName){
    name = accName;
}

std::string AnotherAccount::getName() const {
    return name;
}