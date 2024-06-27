#include <stdio.h>

int main(void){
    printf("Enter a size: ");
    int size = 0;
    scanf("%d", &size);

    int vertCounter = 0;
    int horzCounter = 0;

    while(vertCounter < size){
        while(horzCounter < size){
            printf("*");
            horzCounter++;
        }
        printf("\n");
        vertCounter++;
        horzCounter = 0;
    }

    printf("Enter a size: ");
    size = 0;
    scanf("%d", &size);

    vertCounter = 1;
    horzCounter = 1;

    while(vertCounter <= size){
        while(horzCounter <= size){
            if(horzCounter == 1){
                printf("*");
            } else if(horzCounter == size){
                printf("*");
            } else {
                if(vertCounter == 1){
                    printf("*");
                } else if(vertCounter == size){
                    printf("*");
                } else {
                    printf(" ");
                }
            }
            
            horzCounter++;
        }
        printf("\n");
        vertCounter++;
        horzCounter = 1;
    }
}