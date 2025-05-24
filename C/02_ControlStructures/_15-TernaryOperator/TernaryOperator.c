// Ternary Operator is a shortcut to an if/else statement when assigning or returning a value
// (condition) ? value if true : value if false

#include <stdio.h>

int findMax(int num1, int num2);

int main(){
    // Find the maximum of two integers
    int max = findMax(5, 4);

    printf("\nThe biggest number is %d\n", max);

    /**
     * My example:
     * Prompt the user to enter two integers,
     * and determine if the first is evenly divisible by the second
     */
    int dividend, divisor = 0;
    printf("\nEnter a dividend (int): ");
    scanf("%d", &dividend);

    // Validate to ensure the divisor is not 0
    do {
        printf("Enter a divisor (int): ");
        scanf("%d", &divisor);

        if (divisor == 0){
            printf("\nDivisor cannot be 0.\n");
        }

    } while (divisor == 0);

    // Create a string that contains whether or not the integers are evenly divisible
    char *resultMsg = (dividend % divisor == 0) ? "is" : "is not";

    // Display the result
    printf("\n%d %s divisible by %d\n", dividend, resultMsg, divisor);

    return 0;
}

int findMax(int num1, int num2){
    // Using an if/else to determine which is bigger, num1 or num2
    // if (num1 > num2){
    //     return num1;
    // } else {
    //     return num2;
    // }

    // Shortcut using the ternary operator:
    return (num1 > num2) ? num1 : num2;
}