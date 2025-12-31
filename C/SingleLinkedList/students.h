/**
 * This header file defines a struct detailing a student record
 */


#define STUD_IN_FILE "stuListShort.dat"
#define OUT_BIN_FILE "stuList.bin"
#define ID_LENGTH 5
#define FIRST_NAME_LENGTH 10
#define MIDDLE_NAME_LENGTH 10
#define LAST_NAME_LENGTH 15
#define ACCT_LENGTH 7
#define SSN_LENGTH 11
// There are actually 10 grades, but to search for a -1 in the binary file, count is increased by 1
#define NUM_GRADES 11
#define LINE_LENGTH 200
// There are 100 records, but we will store space for extra when we add/remove records later
#define MAX_RECORDS 150
#define TRUE 1
#define FALSE 0

// Define different sorting modes to be able to sort student records using one function
typedef enum {
    SORT_BY_ID,
    SORT_BY_AVERAGE,
    SORT_BY_NAME
} SortMode;

// Define operations for adding and dropping a student record. This allows us to validate IDs
// the user inputs while displaying the appropriate messages for the operation
typedef enum {
    ADD,
    DROP,
    UPDATE
} RecordOperation;

// Define and name a struct to store student records
typedef struct studentRecord{
    int ID;
    char firstName[FIRST_NAME_LENGTH+1];
    char middleName[MIDDLE_NAME_LENGTH+1];
    char lastName[LAST_NAME_LENGTH+1];
    char account[ACCT_LENGTH+1];
    char ssn[SSN_LENGTH+1];
    float grades[NUM_GRADES];
    float avg;
} element;

// NOTE: The header file that defines a generic node struct must be
// imported AFTER defining the type "element". See above. Otherwise
// you will get compilation errors
#include "node.h"