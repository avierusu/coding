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
#define FULL_NAME_LENGTH 40
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
    char name[FULL_NAME_LENGTH+1];
    char account[ACCT_LENGTH + 1];
    float grades[NUM_GRADES];
    float avg;
} Record;

/*****************************************************************************************************
                                        FUNCTION PROTOTYPES
*****************************************************************************************************/
// For reading and storing data
void readData(char *inFile, char *outFile, Record students[], int *numRecords, int *numGrades);
void populateStruct(Record students[], int *numRecords, int *numGrades, char *line);
char* skipSpace(char *line);
void createName(char fullName[], char firstName[], char middleName[], char lastName[]);
void createAccount(char account[], char first[], char middle[], char last[], char ID[]);
float gradeAvg(Record student, int numGrades);


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
void populateStruct(Record students[], int *numRecords, int *numGrades, char *line){
    // Create arrays to store the student's first, middle, and last names, as well as their
    // full name, id, and account id
    char lastName[LAST_NAME_LENGTH],
         firstName[FIRST_NAME_LENGTH],
         middleName[MIDDLE_NAME_LENGTH],
         fullName[FULL_NAME_LENGTH],
         studentId[ID_SIZE],
         accountId[ACCT_LENGTH],
         temp[30];
    
    // Set grade amount to 0 and increment by 1 for each grade we store
    *numGrades = 0;

    while (*line != '\0'){
        // if *line is pointing to a letter or a digit
        if (isalnum(*line)){
            // Read student ID as a string
            sscanf(line, "%s", temp);
            strcpy(studentId, temp);

            // Use studentId to create a student record
            students[*numRecords].ID = atoi(temp);

            // Move "line" to the end of ID
            line += strlen(temp);
            line = skipSpace(line);

            // Read last name
            sscanf(line, "%s", temp);
            strcpy(lastName, temp);
            // Move "line" to the end of last name
            line += strlen(temp);
            line = skipSpace(line);

            // Read first name
            sscanf(line, "%s", temp);
            strcpy(firstName, temp);
            // Move "line" to the end of first name
            line += strlen(temp);
            line = skipSpace(line);

            // Read middle name
            sscanf(line, "%s", temp);
            strcpy(middleName, temp);
            // Move "line" to the end of middle name
            line += strlen(temp);
            line = skipSpace(line);


            // Loop through all grades and store them
            while (isdigit(*line)){
                // Read the next grade
                sscanf(line, "%s", temp);
                // Add the grade to the current studet's record
                students[*numRecords].grades[*numGrades] = atof(temp);

                // Move "line" to the end of the grade
                line += strlen(temp);
                line = skipSpace(line);

                // Increment grade count by 1
                *numGrades++;
            }


            // Create a full name from first, middle, and last
            // Set all characters to null so that when we combine
            // first, middle, and last names, excess space after
            // the full name will be null
            for (int index = 0; index < FULL_NAME_LENGTH; index++){
                fullName[index] = '\0';
            }
            createName(fullName, firstName, middleName, lastName);
            // Store full name in the current student record
            strcpy(students[*numRecords].name, fullName);

            // Create account ID and store it
            createAccount(accountId, firstName, middleName, lastName, studentId);
            // Store account ID in the current student record
            strcpy(students[*numRecords].account, accountId);

            // Calculate the average for all the student's grades
            students[*numRecords].avg = gradeAvg(students[*numRecords], *numGrades);
        } else {
            // If "line" is pointing to an empty space, move the pointer to the next
            // element
            line = skipSpace(line);
        }
    }
}


/*****************************************************************************************************
    This function traverses the line character by character to skip all spaces and stop the pointer
    at the next non-space character
*****************************************************************************************************/
char* skipSpace(char *line){
    // Keep checking for empty spaces
    while (isspace(*line)){
        // Increment line pointer
        line++;
    }

    return line;
}

/*****************************************************************************************************
    This function creates a full name for the student, comprising of their first, middle, and
    last name, with spaces in between each
*****************************************************************************************************/
void createName(char fullName[], char firstName[], char middleName[], char lastName[]){
    // Add first name to full name
    strcat(fullName, firstName);
    // Add middle name to full name
    strcat(fullName, " ");
    strcat(fullName, middleName);
    // Add last name to full name
    strcat(fullName, " ");
    strcat(fullName, lastName);
}

/*****************************************************************************************************
    This function creates an account ID in the form "abc123", where "abc" are the student's first,
    middle, and last initials respectively, and "1234" are the last four digits of the student's ID
*****************************************************************************************************/
void createAccount(char account[], char first[], char middle[], char last[], char ID[]){
    sprintf(account, "%c%c%c%s", *first, *middle, *last, (ID+1));
}

/*****************************************************************************************************
    This function calculates the average of all grades for each student record
*****************************************************************************************************/
float gradeAvg(Record student, int numGrades){
    // Create float variables to store sum and average
    float sum = 0.0, average = 0.0;

    // Loop through each grade and add it to sum
    for (int gradeIndex = 0; gradeIndex < numGrades; gradeIndex++){
        // Add the current grade to the sum
        sum += student.grades[gradeIndex];
    }

    // Validate against dividing by zero
    if(numGrades != 0){
        // Calculate average
        average = sum / numGrades;
    }

    return average;
}

/*****************************************************************************************************
    
*****************************************************************************************************/
void sortById(Record students[], int numRecords){

}

/*****************************************************************************************************
    
*****************************************************************************************************/
void sortByGrades(Record students[], int numRecords){

}

/*****************************************************************************************************
    
*****************************************************************************************************/
void sortByName(Record students[], int numRecords){

}

/*****************************************************************************************************
    
*****************************************************************************************************/
void writeBinaryFile(Record students[], int numRecords, FILE *filePtrBin){

}