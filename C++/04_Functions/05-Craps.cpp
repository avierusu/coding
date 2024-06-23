// Simulating a game of craps
/**
 * Each turn, the player rolls 2 dice
 * On turn 1: 
 *   - If the sum of each dice is 7 or 11, the player wins
 *   - If the sum of each dice is 2, 3, or 12, the player loses
 *   - Otherwise, remember the player's number
 * For each of the following turns:
 *   - If the sum is their number again, the player wins
 *   - If the sum is 7, the player loses
 *   - The player's number does not change
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned int rollDice();

int main(){
    enum class Status {CONTINUE, WON, LOST};

    srand(static_cast<unsigned int>(time(0)));

    unsigned int myPoint{0};
    Status gameStatus;
    unsigned int sum{rollDice()};

    switch(sum){
        // Win on first roll
        case 7:
        case 11:
            gameStatus = Status::WON;
            break;
        // Lost on first roll
        case 2:
        case 3:
        case 12:
            gameStatus = Status::LOST;
            break;
        // Remember point
        default:
            gameStatus = Status::CONTINUE;
            myPoint = sum;
            cout << "Point is " << myPoint << endl;
            break;
    }

    while(Status::CONTINUE == gameStatus){
        sum = rollDice();

        if(sum == myPoint){
            gameStatus = Status::WON;
        } else {
            if(sum == 7){
                gameStatus = Status::LOST;
            }
        }
    }

    if(gameStatus == Status::WON){
        cout << "Player wins" << endl;
    } else {
        cout << "Player loses" << endl;
    }
}

unsigned int rollDice(){
    int die1{1 + rand() % 6};
    int die2{1 + rand() % 6};
    int sum{die1 + die2};

    cout << "Player rolled " << die1 << " + " << die2 << " = " << sum << endl;

    return sum;
}