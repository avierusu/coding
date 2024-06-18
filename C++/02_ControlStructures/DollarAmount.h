// Dollar amount stores dollar amounts as a whole number of pennies

#include <string>
#include <cmath>
#include <cstdint>

class DollarAmount {
    private:
        int64_t amount{0};
    public:
        // Initialize the amount from an int64_t value
        explicit DollarAmount(int64_t value) :amount{value} {}

        // Add right's amount to this object's amount
        void add(DollarAmount right){
            amount += right.amount;
        }

        // Subtract right's amount from this object's amount
        void subtract(DollarAmount right){
            amount -= right.amount;
        }

        // Calculates interest amount, then calls add with interest amount
        void addInterest(int rate, int divisor){
            DollarAmount interest{
                (amount * rate + divisor / 2) / divisor
            };

            add(interest);
        }

        // Return a string representation of a DollarAmount object
        std::string toString() const {
            std::string dollars{std::to_string(amount/100)};
            std::string cents{std::to_string(amount % 100)};
            return dollars + "." + (cents.size() == 1 ? "0" : "" + cents);
        }
};