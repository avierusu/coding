// Analysis of exam results

#include <stdio.h>

int main(void){
    int passes = 0;
    int failures = 0;
    int student = 1;

    while(student <= 10){
        printf("%s", "Enter result (1=pass,2=fail): ");
        int result = 0;
        scanf("%d", &result);

        if(result == 1){
            passes++;
        } else {
            failures++;
        }

        student++;
    }

    printf("Passed %d\n", passes);
    printf("Failed %d\n", failures);

    if(passes > 8){
        puts("Bonus to the instructor!");
    }
}