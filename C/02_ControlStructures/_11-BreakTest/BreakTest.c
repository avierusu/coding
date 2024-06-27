// Using break to exit a for loop

#include <stdio.h>

int main(void){
    int x = 1;

    for(; x <= 10; ++x){
        if(x == 5){
            break;
        }

        printf("%d ", x);
    }

    printf("\nBroke out of loop at x = %d\n", x);
}