/**
 * typedef enables you to create synonyms (or aliases)
 * for previously defined types. It’s commonly used to
 * create shorter names for struct types and simplify
 * declarations of types like function pointers.
 */
#include <stdio.h>
#include <string.h>

// Card structure definition
struct card {
    char *face;     // Define pointer face
    char *suit;     // Define pointer suit
};

// Using typedef to create a new type name for struct card
typedef struct card Card;

int main(){
    // Define one struct card member
    Card myCard;
    
    // Place strings into myCard
    myCard.face = "Ace";
    myCard.suit = "Spades";

    // assign myCard
    Card *cardPtr = &myCard;
    
    // Accessing structure members in different ways
    printf("%s of %s\n", myCard.face, myCard.suit);
    printf("%s of %s\n", cardPtr->face, cardPtr->suit);
    printf("%s of %s\n", (*cardPtr).face, (*cardPtr).suit);

    return 0;
}