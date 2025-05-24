// Display a pyramid that is the size of the value the user provides

#include <stdio.h>

int main(){
    int size;

    printf("\nEnter an integer between 0 and 7: ");
    scanf("%d", &size);

    switch(size){
        case 7:
            printf("  7 7 7 7 7 7 7\n");
        case 6:
            printf("   6 6 6 6 6 6\n");
        case 5:
            printf("    5 5 5 5 5\n");
        case 4:
            printf("     4 4 4 4\n");
        case 3:
            printf("      3 3 3\n");
        case 2:
            printf("       2 2\n");
        case 1:
            printf("        1\n");
        case 0:
            printf("00000000000000000\n");
        default:
            printf("-----------------\n");
    }

    return 0;
}