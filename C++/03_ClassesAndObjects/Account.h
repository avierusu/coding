// Contains a name and functions to set and get name

#include <string>

class Account {
    public:
        void setName(std::string accName){
            name = accName;
        }

        std::string getName() const {
            return name;
        }
    private:
        std::string name;
};