/**
 * This program will take a deck of 52 unique cards
 * and shuffle them and deal them out
 * 
 * We will accomplish this using struct
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES 13

// Card structure definition
struct card {
    const char *face;
    const char *suit;
};

// Define new name for card struct
typedef struct card Card;

// Function prototypes
void fillDeck(Card * const deck, const char *faces[], const char *suits[]);
void shuffle(Card * const deck);
void deal(const Card * const deck);

int main(){
    // Define an array of cards
    Card deck[CARDS];

    // Initialize faces and suits arrays
    const char *faces[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King"};
    const char *suits[] = {"Spades", "Clubs", "Diamonds", "Hearts"};

    // Randomize
    srand(time(NULL));

    // Load the deck with Cards
    fillDeck(deck, faces, suits);
    // Put Cards in a random order
    shuffle(deck);
    // deal all 52 cards
    deal(deck);

    return 0;
}

// Place strings into Card structures
void fillDeck(Card * const deck, const char *faces[], const char *suits[]){
    // Loop through the deck
    for (size_t index = 0; index < CARDS; index++){
        deck[index].face = faces[index % FACES];
        deck[index].suit = suits[index / FACES];
    }
}

// Shuffle all cards
void shuffle(Card * const deck){
    // Loop through the deck, randomly swapping Cards
    for (size_t index = 0; index < CARDS; index++){
        // Select a random position to swap the Card to
        size_t swap = rand() % CARDS;
        // Swap cards
        Card temp = deck[index];
        deck[index] = deck[swap];
        deck[swap] = temp;
    }
}

// Deal the cards (display to the console)
void deal(const Card * const deck){
    // Loop through the deck
    for (size_t index = 0; index < CARDS; index++){
        // Display each card
        printf("%5s of %-8s", deck[index].face, deck[index].suit);
        
        // Every 4 cards, go to a new line
        if ( (index + 1) % 4 == 0 ){
            printf("\n");
        } else {
            printf("   ");
        }
    }
}