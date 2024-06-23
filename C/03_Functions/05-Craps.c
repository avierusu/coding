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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Status {CONTINUE, WON, LOST};

int rollDice(void);

int main(void){
    srand(time(NULL));

    int myPoint = 0;
    enum Status gameStatus = CONTINUE;
    int sum = rollDice();

    switch(sum){
        // Win on first roll
        case 7:
        case 11:
            gameStatus = WON;
            break;
        // Lost on first roll
        case 2:
        case 3:
        case 12:
            gameStatus = LOST;
            break;
        // Remember point
        default:
            gameStatus = CONTINUE;
            myPoint = sum;
            printf("Point is %d\n", myPoint);
            break;
    }

    while(gameStatus == CONTINUE){
        sum = rollDice();

        if(sum == myPoint){
            gameStatus = WON;
        } else if(sum == 7){
            gameStatus = LOST;
        }
    }

    if(gameStatus == WON){
        puts("Player wins");
    } else {
        puts("Player loses");
    }
}

int rollDice(void){
    int die1 = 1 + (rand() % 6);
    int die2 = 1 + (rand() % 6);

    printf("Player rolled %d + %d = %d\n", die1, die2, die1+die2);
    return die1 + die2;
}