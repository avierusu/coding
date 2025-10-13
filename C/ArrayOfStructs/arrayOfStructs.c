/*****************************************************************************************************
    Description:    This program checks to see if there is a binary file called "stuList.bin" that
                    exists in the directory.

                    If "stuList.bin" doesn't exist:
                    The program opens a text file named "stuList.dat" and reads student records into
                    a struct. Each line in the file represents a new student record. Reading the
                    student info also includes figuring out the students' account IDs and the average
                    of each students' grades. Then, each student structure is written to a file called
                    "stuList.bin" in a binary form. Reading from the text file "stuList.dat" occurs
                    only one time. The subsequent manipulations to the struct are carried out using
                    the binary file "stuList.bin"

                    If "stulist.bin" does exist:
                    All this binary information is read into an array of structs and a menu is printed
                    to prompt the user to achieve various tasks:
                        Process Add/Drop File
                        Process Individual Add/Drop
                        Sort by Student Name (Alphabetic order)
                        Sort by Student Average (Descending order)
                        Sort by Student ID number (Descending order)
                        Update Grades (Should automatically sort by ID number, then recalculate
                        averages)
                        Print List
                        Exit

    Developer:      Avinash Erusu
    Method used:    Array of struct *record*
                    Static memory Allocation
*****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>     // For using malloc
#include <ctype.h>      // For using isalnum()
#include <string.h>     // For using strcat()

#define TEXT_FILE "stuList.dat"
#define BIN_FILE "stuList.bin"
#define ID_SIZE 5
#define FIRST_NAME_LENGTH 10
#define MIDDLE_NAME_LENGTH 10
#define LAST_NAME_LENGTH 15
#define ACCT_LENGTH 7
#define NUM_GRADES 10
// There are actually 12 grades, but to search for a -1, count is increased by 1
#define LINE_LENGTH 200
#define MAX_RECORDS 100
#define TRUE 1
#define FALSE 0

// Define and name a struct to store student records
typedef struct record{
    int ID;
    char firstName[FIRST_NAME_LENGTH + 1];
    char middleName[MIDDLE_NAME_LENGTH + 1];
    char lastName[LAST_NAME_LENGTH + 1];
    char account[ACCT_LENGTH + 1];
    float grades[NUM_GRADES];
    float avg;
} Record;

// Function prototypes
void readData(char *inFile, char *outFile, Record students[], int *numRecords, int *numGrades);


int main(){

    return 0;
}

/*****************************************************************************************************
    This function opens the file "stuList.dat" and reads each line until the EOF. Since each line
    represents a student record, the students' first, middle, and last names are read and stored in a
    struct. A unique account ID is created for each student. All grades are stored in the respective
    struct, and the average of all grades is calculated and stored as well
*****************************************************************************************************/
// Reads records from stuList.dat into an array of structs. Also calculates the 
// number of records and the number of grades for each student
void readData(char *inFile, char *outFile, Record students[], int *numRecords, int *numGrades){
    FILE *filePtrIn, *filePtrBin;
    char buffer[LINE_LENGTH];
    char *line;
    // Open the input (stuList.dat) and output (stuList.bin) files
    filePtrIn = open(inFile, "r");
    filePtrBin = open(outFile, "w");

    // Read through each line of the stuList.dat file
    while ( (fgets(buffer, LINE_LENGTH, filePtrIn) != NULL) && (numRecords < MAX_RECORDS)){
        line = buffer;
        numGrades = 0;

        // Read the data from each line into a struct
        populateStruct(students, numRecords, numGrades, line);

        // Write the data in the struct to the "stuList.bin file
        writeBinaryFile(students, numRecords, filePtrBin);

        numRecords++;
    }

    // Sort the array of structs by student ID in increasing order
    // before sending back to main
    sortById(students, numRecords);

    // Close both files
    fclose(filePtrIn);
    fclose(filePtrBin);
}

/*****************************************************************************************************
    This function reads each line from the given file and populates the data into a student struct.
    It also creates an account ID for each student, and calculates the average of the students'
    grades
*****************************************************************************************************/
void populateStruct(Record students[], int *numRecords, int *numgrades, char *line){
    
}

void writeBinaryFile(Record students[], int numRecords, FILE *filePtrBin){

}

void sortById(Record students[], int numRecords){

}