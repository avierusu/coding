// Logical operators

#include <stdio.h>
#include <stdbool.h>

int main(void){
    printf("Logical AND (&&)");
    printf("\nfalse && false: %s", ((false && false) ? "true" : "false") );
    printf("\nfalse && true: %s", ((false && true) ? "true" : "false") );
    printf("\ntrue && false: %s", ((true && false) ? "true" : "false") );
    printf("\ntrue && true: %s", ((true && true) ? "true" : "false") );

    printf("\n\n");
    printf("Logical OR (||)");
    printf("\nfalse || false: %s", ((false || false) ? "true" : "false") );
    printf("\nfalse || true: %s", ((false || true) ? "true" : "false") );
    printf("\ntrue || false: %s", ((true || false) ? "true" : "false") );
    printf("\ntrue || true: %s", ((true || true) ? "true" : "false") );

    printf("\n\n");
    printf("Logical negation (!)");
    printf("\n!false: %s", (!false ? "true" : "false") );
    printf("\n!true: %s", (!true ? "true" : "false") );
}