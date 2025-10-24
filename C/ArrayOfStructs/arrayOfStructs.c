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
                        Process Add/Drop using a File
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
#define NUM_GRADES 11
// There are actually 10 grades, but to search for a -1 in the binary file, count is increased by 1
#define LINE_LENGTH 200
#define MAX_RECORDS 100
#define TRUE 1
#define FALSE 0

// Define and name a struct to store student records
typedef struct record{
    int ID;
    char name[FULL_NAME_LENGTH+1];
    char account[ACCT_LENGTH+1];
    float grades[NUM_GRADES];
    float avg;
} Record;

// Define different sorting modes to be able to sort student records using one function
typedef enum {
    SORT_BY_ID,
    SORT_BY_AVERAGE,
    SORT_BY_NAME
} SortMode;

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
// For sorting data
void sortById(Record students[], int numRecords);
void sortByGrades(Record students[], int numRecords);
void sortByName(Record students[], int numRecords);
void sortSubArray(Record *inArray, int left, int right, SortMode mode);
int compare(Record *student1, Record *student2, SortMode mode);
void swap(Record inArray[], int firstIndex, int secondIndex);
// User Interface
void welcome();
int menu();
void processMenu(Record students[], int *numRecords, int *numGrades);
void printRecords(Record students[], int numRecords);
// For reading/writing the binary file
void readBinaryFile(FILE *filePtrBin, Record students[], int *numRecords, int *numGrades);
void writeBinaryFile(FILE *filePtrBin, Record students[], int numRecords);
long int getRecordCount(FILE *filePtrBin, Record students[]);
// Other
FILE* openFile(char *fileName, char *mode);


/*****************************************************************************************************
                                            MAIN FUNCTION
*****************************************************************************************************/
int main(){
    // Define an array of student records, as well as integers to store the number of records
    // and the number of grades per record
    Record students[MAX_RECORDS];
    int recordCount = 0;
    int gradeCount;
    FILE *filePtrBin;

    readData(TEXT_FILE, BIN_FILE, students, &recordCount, &gradeCount);
    processMenu(students, &recordCount, &gradeCount);
    // printRecords(students, recordCount);

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
    filePtrIn = openFile(inFile, "r");
    filePtrBin = openFile(outFile, "w");

    // Read through each line of the stuList.dat file
    while ( (fgets(buffer, LINE_LENGTH, filePtrIn) != NULL) && (*numRecords < MAX_RECORDS)){
        line = buffer;
        *numGrades = 0;

        // Read the data from each line into a struct
        populateStruct(students, numRecords, numGrades, line);

        // Write the data in the struct to the "stuList.bin file
        writeBinaryFile(filePtrBin, students, *numRecords);

        (*numRecords)++;
    }

    // Sort the array of structs by student ID in increasing order
    // before sending back to main
    sortById(students, *numRecords);

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
                (*numGrades)++;
            }
            // Store -1 at the end of the array of grades
            students[*numRecords].grades[*numGrades] = -1;


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
    snprintf(account, ACCT_LENGTH+1, "%c%c%c%s", *first, *middle, *last, (ID+1));
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
        // printf("\n%d: %f", gradeIndex, student.grades[gradeIndex]);
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
    This function uses quick sort to sort student records by their student ID in increasing order
*****************************************************************************************************/
void sortById(Record students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by ID
    sortSubArray(students, 0, (numRecords - 1), SORT_BY_ID);
}

/*****************************************************************************************************
    This function uses quick sort to sort student records by the average of their grades in
    increasing order
*****************************************************************************************************/
void sortByGrades(Record students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by average
    sortSubArray(students, 0, numRecords - 1, SORT_BY_AVERAGE);
}

/*****************************************************************************************************
    This function uses quick sort to sort student records by their full name in increasing order
*****************************************************************************************************/
void sortByName(Record students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by name
    sortSubArray(students, 0, numRecords - 1, SORT_BY_NAME);
}

/*****************************************************************************************************
    This function sorts one section of the array by splitting it in two and recursively calling
    itself to sort the smaller sections, until the full array is sorted
*****************************************************************************************************/
void sortSubArray(Record *inArray, int left, int right, SortMode mode){
    int leftSwap = left;
    int rightSwap = right;
    // Calculate the middle student record in the array
    // Record *middle = &(inArray[ (left + right) / 2 ]);
    Record pivot = inArray[(left + right) / 2];

    do {
        while ( compare(&(inArray[leftSwap]), &pivot, mode) < 0/*(inArray[leftSwap] < middle)*/ && (leftSwap < right) ){
            leftSwap++;
        }
        while ( compare(&(inArray[rightSwap]), &pivot, mode) > 0/*(inArray[rightSwap] > middle)*/ && (rightSwap > left) ){
            rightSwap--;
        }

        if (leftSwap <= rightSwap){
            swap(inArray, leftSwap, rightSwap);
            leftSwap++;
            rightSwap--;
        }

    } while (leftSwap <= rightSwap);

    if (left < rightSwap){
        sortSubArray(inArray, left, rightSwap, mode);
    }
    if (leftSwap < right){
        sortSubArray(inArray, leftSwap, right, mode);
    }
}

/*****************************************************************************************************
    This function compares the element of two student record structs. It uses SortMode to determine
    whether to compare by student ID, student average, or student name.
    Returns a value < 0 when student1 < student2
    Returns 0 when student1 = student2
    Returns a value > 0 when student1 > student2
*****************************************************************************************************/
int compare(Record *student1, Record *student2, SortMode mode){
    // Check which sorting mode to sort by
    switch(mode){
        case SORT_BY_AVERAGE:
            // Compare averages by subtracting and returning the difference
            return (student1 -> avg) - (student2 -> avg);
            break;
        case SORT_BY_NAME:
            // Compare names using strcmp and return the output
            return strcmp( (student1 -> name) , (student2 -> name));
            break;
        case SORT_BY_ID:
        default:
            // Compare by ID by default
            // Subtract IDs and return the difference
            return (student1 -> ID) - (student2 -> ID);
    }
}

/*****************************************************************************************************
    This function swaps two student records in an array
*****************************************************************************************************/
void swap(Record *inArray, int firstIndex, int secondIndex){
    Record temp = inArray[firstIndex];
    inArray[firstIndex] = inArray[secondIndex];
    inArray[secondIndex] = temp;
}

/*****************************************************************************************************
    This function displays a Welcome screen to the user
*****************************************************************************************************/
void welcome(){
    // Clear the console
    system("cls");
    // Display a welcome banner
    printf("\n\n");
    printf("\t=====================================================\n");
    printf("\tR E G I S T R A T I O N   P R O C E S S I N G\n");
    printf("\t=====================================================\n");
    printf("\tWelcome to the Registration Processing Program. This\n");
    printf("\tprogram handles students who register for our course.\n");
    printf("\tPlease respond to the following menu choice:\n\n");
}

/*****************************************************************************************************
    This function displays a menu to the user
*****************************************************************************************************/
int menu(){
    // Store the user's choice
    int choice = 0;

    // Display the menu options
    printf("\n\n");
    printf("\t*************************************************************************************\n");
    printf("\t                                    M E N U\n");
    printf("\t                                   ---------\n");
    printf("\t1. Process Add/Drop using a File\n");
    printf("\t2. Process Individual Add/Drop using Keyboard\n");
    printf("\t3. Sort by Student Name (Alphabetic Order)\n");
    printf("\t4. Sort by Student Average (Descending Order)\n");
    printf("\t5. Sort by Student ID (Ascending Order)\n");
    printf("\t6. Update Grades\n");
    printf("\t7. Print List\n");
    printf("\t9. Exit\n");
    printf("\t*************************************************************************************\n\n");
    printf("Enter your choice here: ");
    scanf("%d", &choice);
    return choice;
}

/*****************************************************************************************************
    This function displays the menu to the user and processes their choice. If the user enters
    an invalid menu choice, reprompts the user
*****************************************************************************************************/
void processMenu(Record students[], int *numRecords, int *numGrades){
    int choice, displayCount = 0;
    // Display the welcome banner
    welcome();
    // Display the menu and accept the user's choice
    choice = menu();

    // Keep displaying the menu until the user chooses to exit
    while (choice != 9){
        // Use a switch to perform different actions depending on the user's choice
        switch (choice){
            case 1:
                // TODO: Process Add/Drop using a File
                break;
            case 2:
                // TODO: Process Individual Add/Drop using Keyboard
                break;
            case 3:
                // Sort by Student Name (Alphabetic Order)
                sortByName(students, *numRecords);

                // Display the first 20 records after sorting
                printf("\nAfter sorting by Student Name, the Top 20 records from the list are:\n");
                printRecords(students, 20);
                break;
            case 4:
                // Sort by Student Average (Descending Order)
                sortByGrades(students, *numRecords);

                // Display the first 20 records after sorting
                printf("\nAfter sorting by Student Average Grade, the Top 20 records from the list are:\n");
                printRecords(students, 20);
                break;
            case 5:
                // Sort by Student ID (Ascending Order)
                sortById(students, *numRecords);

                // Display the first 20 records after sorting
                printf("\nAfter sorting by Student ID, the Top 20 records from the list are:\n");
                printRecords(students, 20);
                break;
            case 6:
                // TODO: Update Grades
                break;
            case 7:
                // Print List
                // Prompt the user to enter the amount of records to be displayed and store it
                printf("\n\tA total of %d records are available.", *numRecords);
                printf("\n\tEnter the number of student records you want to see: ");
                scanf("%d", &displayCount);
                
                // If the user entered an invalid number of records (i.e. < 1 or more than the
                // total number of records), reprompt
                while (displayCount < 1 || displayCount > (*numRecords)){
                    printf("\n\tThere are only %d records in the list", *numRecords);
                    printf("\n\tEnter a number between 1 and %d: ", *numRecords);
                    scanf("%d", &displayCount);
                }

                // Display the requested amount of records
                printf("\n\n\tThe Top %d records from the list are:\n");
                printRecords(students, displayCount);

                break;
            default:
                // If the user enters an invalid value, display an error message and prompt again
                printf("\tSorry, that is not a valid selection\n");
                break;
        }

        // Display the menu again after the user presses Enter
        printf("\n > Press ENTER to continue...");
        getchar();
        getchar();
        choice = menu();
    }
}

/*****************************************************************************************************
    This function prints out the data stored in the student array depending on how any from the list
    need to be printed
*****************************************************************************************************/
void printRecords(Record students[], int numRecords){
    // Print the top banner
    printf("-------------------------------------------------------------------------------------\n");
    printf("S.No.\tID #\tName\t\t\t\tAccount #\tAvg.Gr\n");
    printf("-------------------------------------------------------------------------------------\n");

    // Print each record
    for(int index = 0; index < numRecords; index++){
        printf("Rec #%2d:", index+1);
        printf("\t%d", students[index].ID);
        printf("\n%-27.25s", students[index].name);
        printf("%-.7s", students[index].account);
        printf("\t\t%5.2f\n", students[index].avg);
    }
}

/*****************************************************************************************************
    This function reads the binary file into an array of student record structs. It also calculates
    the total number of records in the array and total number of grades for each student
*****************************************************************************************************/
void readBinaryFile(FILE *filePtrBin, Record students[], int *numRecords, int *numGrades){
    // Get the total number of records in the file
    *numRecords = getRecordCount(filePtrBin, students);

    // Move the pointer to the beginning of the binary file
    fseek(filePtrBin, 0L, 0);
    // Read the binary file into an array of structs using fread()
    for (int index = 0; index < (*numRecords); index++){
        // Read one struct from the file
        fread(&students[index], sizeof(Record), 1, filePtrBin);

        // Move the file pointer to point to the end of the struct
        fseek(filePtrBin, (long) ((index+1) * sizeof(Record)), 0);
    }

    // Determine the number of grades
    for (int index = 0; index < NUM_GRADES; index++){
        // Compare to see which grade is -1, which is stored after the final grade
        if (students[0].grades[index] == -1){
            *numGrades = index;
            break;
        }
    }
}

/*****************************************************************************************************
    This function writes the data stored in the student records array into a binary file
*****************************************************************************************************/
void writeBinaryFile(FILE *filePtrBin, Record students[], int numRecords){
    // Write each student record into the binary file
    fwrite(&students[numRecords], sizeof(Record), 1, filePtrBin);

    // Move the file pointer to the end of file each time
    fseek(filePtrBin, 0L, 2);
}

/*****************************************************************************************************
    This function calculates the total number of records that are present in the input binary file.
    Instead of calculating the number of lines in the file, this function calculates the total number
    of bytes to store the whole file and divides that amount by the number of bytes required to store
    one record
*****************************************************************************************************/
long int getRecordCount(FILE *filePtrBin, Record students[]){
    long int numBytes, numRecords;
    // Move the file pointer to the EOF
    fseek(filePtrBin, (long)0, 2);
    // Get the total number of bytes in the file
    numBytes = ftell(filePtrBin);
    // Calculate the total number of records
    numRecords = numBytes / sizeof(Record);

    return numRecords;
}

/*****************************************************************************************************
    This function opens the requested file. If the file cannot be opened, exit the program
*****************************************************************************************************/
FILE* openFile(char *fileName, char *mode){
    FILE *filePtr;

    // Exit the program if the file cannot be opened
    if( (filePtr = fopen(fileName, mode)) == NULL ){
        printf("Unable to open file\"%s\"\n", fileName);
        exit(1);
    }

    return filePtr;
}