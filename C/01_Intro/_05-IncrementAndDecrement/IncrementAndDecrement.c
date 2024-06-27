#include <stdio.h>

int main(void){
    int c = 5;
    printf("%d\n", c);      //print 5
    printf("%d\n", c++);    //print 5 then post-increment
    printf("%d\n\n", c);    //print 6

    c = 5;
    printf("%d\n", c);      //print 5
    printf("%d\n", ++c);    //pre-increment then print 6
    printf("%d\n", c);    //print 6
}