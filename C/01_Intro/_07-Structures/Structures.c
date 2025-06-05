/**
 * A structure (struct) is a collection of related variables
 * under one name. Structures may contain many variables
 * of different types, unlike arrays
 */
#include <stdio.h>
#include <string.h>

// Card structure definition
struct card {
    char *face;     // Define pointer face
    char *suit;     // Define pointer suit
};

int main(){
    // Define one struct card member
    struct card myCard;
    
    // Place strings into myCard
    myCard.face = "Ace";
    myCard.suit = "Spades";

    // assign myCard
    struct card *cardPtr = &myCard;
    
    // Accessing structure members in different ways
    printf("%s of %s\n", myCard.face, myCard.suit);
    printf("%s of %s\n", cardPtr->face, cardPtr->suit);
    printf("%s of %s\n", (*cardPtr).face, (*cardPtr).suit);

    return 0;
}