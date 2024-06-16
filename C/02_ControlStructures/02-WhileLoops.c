// Class average program with counter-controlled iteration

#include <stdio.h>

int main(void){
    int total = 0;
    int counter = 0;

    printf("%s", "Enter grade, -1 to : ");
    int grade = 0;
    scanf("%d", &grade);

    while(grade != -1){
        total += grade;
        counter ++;

        printf("%s", "Enter grade, -1 to : ");
        scanf("%d", &grade);
    }

    if(counter != 0){
        double average = (double)total / counter;
        printf("Class average is %.2f\n", average);
    } else {
        puts("No grades were entered");
    }
    
}