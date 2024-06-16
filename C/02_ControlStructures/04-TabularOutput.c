#include <stdio.h>

int main(void){
    printf("Enter a number: ");
    int n = 0;
    scanf("%d", &n);

    printf("N\t10*N\t100*N\t1000*N\n\n");
    int counter = 1;

    while(counter <= n){
        printf("%d\t%d\t%d\t%d\n", counter, counter*10, counter*100, counter*1000);
        counter++;
    }
}