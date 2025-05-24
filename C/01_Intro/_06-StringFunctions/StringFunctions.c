// Various functions we can use with strings

#include <stdio.h>
#include <string.h>

int main(){
    char str1[] = "Good";
    char str2[] = "Morning!";
    char str3[] = "Night.";

    // Convert a string to lowercase
    strlwr(str1);
    printf("\nlowercase             : %s", str1);

    // Converts a string to uppercase
    strupr(str2);
    printf("\nuppercase             : %s", str2);

    // Appends str2 to the end of str1
    strcat(str1, str2);
    printf("\nappend full string    : %s", str1);

    // Append a certain amount of characters from str1 to the end of str2
    strncat(str2, str1, 2);
    printf("\nappend 2 characters   : %s", str2);

    // Copy str3 into str2
    strcpy(str2, str3);
    printf("\ncopied string         : %s", str2);

    // Copy 5 characters from str3 to str1
    strncpy(str1, str3, 5);
    printf("\ncopied 5 characters   : %s", str1);

    // Set all characters of a string to a given character
    strset(str3, '!');
    printf("\nall exclamation marks : %s", str3);

    // Set the first 3 characters of str2 to underscores
    strnset(str2, '_', 3);
    printf("\nset 3 characters to _ : %s", str2);

    // Reverse a string
    strrev(str1);
    printf("\nreverse               : %s", str1);



    int result;
    // Returns string length as an int
    result = strlen(str1);
    printf("\n\nstring length         : %d", result);
    
    // Compare all characters within two strings
    // If they are the same, returns 0; otherwise, returns a different number
    result = strcmp(str2, str3);
    char *resultMsg1 = (result == 0) ? "same" : "different";
    printf("\ncompare strings       : %s", resultMsg1);

    // Compare 1 character between str1 and str3
    result = strncmp(str1, str3, 1);
    char *resultMsg2 = (result == 0) ? "same" : "different";
    printf("\ncompare strings       : %s", resultMsg2);

    /**
     * There are two other versions of the previous two:
     * - strcmpi(str1, str2)
     * - strnicmp(str1, str2, 3)
     * These ignore the case of the strings when comparing
     */
    
    return 0;
}