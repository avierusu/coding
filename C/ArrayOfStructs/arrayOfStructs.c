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
// There are actually 10 grades, but to search for a -1 in the binary file, count is increased by 1
#define NUM_GRADES 11
#define LINE_LENGTH 200
// There are 100 records, but we will store space for extra when we add/remove records later
#define MAX_RECORDS 150
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
void addDropUsingFile(Record students[], int *numRecords, int *numGrades);
void readAddDropFile(Record students[], int *numRecords, int *numGrades, FILE *filePtrAddDrop);
void addDropUsingKeyboard(Record students[], int *numRecords, int *numGrades);
void printRecords(Record students[], int numRecords);
void updateGrades(Record students[], int *numRecords, int *numGrades);
// For reading/writing the binary file
void readBinaryFile(FILE *filePtrBin, Record students[], int *numRecords, int *numGrades);
void writeBinaryFile(FILE *filePtrBin, Record students[], int numRecords);
long int getRecordCount(FILE *filePtrBin, Record students[]);
// Other
int binarySearch(Record students[], int searchKey, int low, int high, int size);
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

    // // Call readData() only if "stuList.bin" file does not exist
    // if ( (filePtrBin = fopen(BIN_FILE, "r")) == NULL ){
    //     readData(TEXT_FILE, BIN_FILE, students, &recordCount, &gradeCount);
    //     // Close the bin file, since it does not exist
    //     fclose(filePtrBin);
    // } else {
    //     // If the bin file exists, read its data into the array of structs
    //     readBinaryFile(filePtrBin, students, &recordCount, &gradeCount);

    //     processMenu(students, &recordCount, &gradeCount);
    // }

    readData(TEXT_FILE, BIN_FILE, students, &recordCount, &gradeCount);
    processMenu(students, &recordCount, &gradeCount);

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
                // Process Add/Drop using a File
                addDropUsingFile(students, numRecords, numGrades);
                break;
            case 2:
                // Process Individual Add/Drop using Keyboard
                addDropUsingKeyboard(students, numRecords, numGrades);
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
                // Update Grades
                updateGrades(students, numRecords, numGrades);
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
    This function uses one of three files to process either an Add or a Drop of a student record
    depending on the character in the first column of the input file ('A' for Add, 'D' for Drop) 
*****************************************************************************************************/
void addDropUsingFile(Record students[], int *numRecords, int *numGrades){
    int choice;
    FILE *filePtrAddDrop;

    // Display the options to the user
    printf("\n\tThe following files can be used to Add/Drop:\n\n");
    printf("\t\t1. addDrop01.dat\n");
    printf("\t\t1. addDrop02.dat\n");
    printf("\t\t1. addDrop03.dat\n");
    printf("\n\tSelect a number to indicate a file of your choice: ");

    // Accept the user's input
    scanf("%d ", &choice);
    // If the user did not enter a valid choice, display an error message and reprompt
    while (choice < 1 || choice > 3){
        printf("\n\tYou must select a number between 1 and 3\n\tEnter your choice: ");
        scanf("%d ", &choice);
    }

    // Depending on the user's choice, open and process the requested file
    switch(choice){
        case 1:
            // Open and process the addDrop01.dat file
            filePtrAddDrop = openFile("addDrop01.dat", "r");
            readAddDropFile(students, numRecords, numGrades, filePtrAddDrop);
            break;
        case 2:
            // Open and process the addDrop02.dat file
            filePtrAddDrop = openFile("addDrop02.dat", "r");
            readAddDropFile(students, numRecords, numGrades, filePtrAddDrop);
            break;
        case 3:
            // Open and process the addDrop03.dat file
            filePtrAddDrop = openFile("addDrop03.dat", "r");
            readAddDropFile(students, numRecords, numGrades, filePtrAddDrop);
            break;
    }

    // Close the file
    fclose(filePtrAddDrop);
}

/*****************************************************************************************************
    This function opens the "stuList.bin" file. It reads the given ".dat" file and determines which
    record to add/drop, depending on the first character ('A' for Add, 'D' for Drop).

    If it's 'A', it checks to see if the ID read already exists. If so, it reports that it cannot add
    that record. If not, it creates space for the new ID and takes all information needed for the
    record, including calculating an account ID and grade average.

    If it's 'D', it checks to see if the ID read already exists. If so, it will ask the user if they
    are sure that they want to delete the record from the array.

    Finally, it will display a list of IDs added, IDs dropped, and IDs not found
*****************************************************************************************************/
void readAddDropFile(Record students[], int *numRecords, int *numGrades, FILE *filePtrAddDrop){
    FILE *filePtrBin;
    char *outFile = "stuList.bin";
    char buffer[LINE_LENGTH];
    char *line;
    // Count the total records in the .dat file
    int lineCount = 0;
    // ID of the student to add/drop
    int ID;
    // The size of these array is dynamically allocated depending on the size of the file
    int *IDsAddedArray, *IDsDroppedArray, *IDsNotFoundArray, *IDsExistsArray;
    // Count the number of records added, dropped, already existing, or not found
    int addCount = 0, dropCount = 0, notFoundCount = 0, existCount = 0;
    int notFoundFlag = FALSE;
    int existFlag = FALSE;
    int result;

    // Open "stuList.bin" in write mode
    filePtrBin = openFile(outFile, "w");

    // Count the total number of lines in the file. Since each line does not represent a record
    // and is therefore uneven, we will use fgets()
    while ( fgets(buffer, LINE_LENGTH, filePtrAddDrop) != NULL ){
        lineCount++;
    }

    // After the while loop above, the pointer filePtrAddDrop is pointing to the last line of the
    // file, so we must bring the pointer back to the beginning of the file.
    fseek(filePtrAddDrop, 0L, 0);

    // Allocate dynamic memory for the 4 arrays previously defined. Assume every line must be added
    // to the array to assign enough memory
    if ( (IDsAddedArray = (int *)calloc(lineCount, sizeof(int))) == NULL ){
        printf("\nUnable to allocate space for \"IDsAddedArray\"\n");
        exit(20);
    }
    if ( (IDsDroppedArray = (int *)calloc(lineCount, sizeof(int))) == NULL ){
        printf("\nUnable to allocate space for \"IDsDroppedArray\"\n");
        exit(20);
    }
    if ( (IDsNotFoundArray = (int *)calloc(lineCount, sizeof(int))) == NULL ){
        printf("\nUnable to allocate space for \"IDsNotFoundArray\"\n");
        exit(20);
    }
    if ( (IDsExistsArray = (int *)calloc(lineCount, sizeof(int))) == NULL ){
        printf("\nUnable to allocate space for \"IDsExistsArray\"\n");
        exit(20);
    }

    // Assign null to buffer
    for (int index = 0; index < LINE_LENGTH; index++){
        buffer[index] == '\0';
    }

    // Process each line
    while ( fgets(buffer, LINE_LENGTH, filePtrAddDrop) != NULL ){
        // *line contains either 'A' or 'D'
        line = buffer;
        // Move the pointer next to 'A' or 'D'
        line += 1;
        line = skipSpace(line);
        sscanf(line, "%5d", &ID);

        // Search for the ID in the array
        result = binarySearch(students, ID, 0, ((*numRecords)-1), (*numRecords));

        // Make line point to the first character
        line = buffer;

        // Process Add or Drop
        if ((*line) == 'A'){
            // Add the record in the last element of the array
            // First, check if the record is not already in the array
            if (result == -1){
                // Move the pointer to the next 'A'
                line = line + 1;
                populateStruct(students, numRecords, numGrades, line);
                // Increase the number of records by one
                (*numRecords)++;

                // Store the IDs that are successfully added
                IDsAddedArray[addCount] = ID;
                addCount++;
            } else {
                // If the ID already exists:
                IDsExistsArray[existCount] == ID;
                existCount++;
                existFlag = TRUE;
            }
        } else if ((*line) == 'D'){
            // Drop record from the array
            // First, check if the record is already in the array
            if (result != -1){
                // Move all elements after the found index up by one element
                // FIXME: might have to change condition to index < ((*numRecords)-1), because
                // the students[index+1] check might go out of bounds. we will see !!
                for (int index = result; index < (*numRecords); index++){
                    students[index] = students[index+1];
                }

                // Store the IDs that are successfully dropped
                IDsDroppedArray[dropCount] = ID;
                dropCount++;

                // Cut down the size of the array by 1, since we dropped 1 record
                (*numRecords)--;
            } else {
                // If the ID does not exist:
                IDsNotFoundArray[notFoundCount] = ID;
                notFoundCount++;
                notFoundFlag = TRUE;
            }
        } else {
            // If neither 'A' nor 'D'
            printf("\nUnable to Add/Drop record from file\nDid not see either an 'A' or a 'D' in the file\n");
        }
    }

    // Display how many IDs were added/dropped
    printf("\n\tTotal IDs ADDED: \t%d", addCount);
    printf("\n\tTotal IDs DROPPED: \t%d\n", dropCount);

    // If any IDs were added/dropped, display a table showing them
    if (addCount > 0 || dropCount > 0){
        printf("\n\t\t--------------------------------");
        printf("\n\t\tIDs Added\t\tIDs Dropped");
        printf("\n\t\t--------------------------------");

        // Display each ID that was added/dropped
        // Since the IDs added and IDs dropped will be displayed side by side, we must print them at the same time
        // and pass through each array at the same time
        for (int addIndex = 0, dropIndex = 0; addIndex < addCount || dropIndex < dropCount; addIndex++, dropIndex++){
            if (IDsAddedArray[addIndex] == 0){
                // If there are no more added IDs, only print the dropped IDs
                printf("\t\t*****\t\t\t%d\n", IDsDroppedArray[dropIndex]);
            } else if (IDsDroppedArray[dropIndex] == 0){
                // If there are no more dropped IDs, only print the added IDs
                printf("\t\t%d\t\t\t*****\n", IDsAddedArray[addIndex]);
            } else {
                // If there are still more added AND dropped IDs, print both side by side
                printf("\t\t%d\t\t\t%d\n", IDsAddedArray[addIndex], IDsDroppedArray[dropIndex]);
            }
            // Print a divider
            printf("\t\t--------------------------------\n\n");
        }
    }

    // Display any errors in reading Add/Drop from the file
    // First, display any records that already existed and could not be added
    if (existFlag == TRUE){
        printf("\n\tThe following IDs could not be added:\n");
        // Loop through the array of existing IDs and display them
        for (int existIndex = 0; existIndex <  existCount; existIndex++){
            printf("\t\t%d\n", IDsExistsArray[existIndex]);
        }
        printf("\t\tReason: They already exist.\n");
    }
    // Next, display any records that could not be dropped because they did not exist
    if (notFoundFlag == TRUE){
        printf("\n\tThe following IDs could not be dropped:\n");
        // Loop through the array of non-existent IDs and display them
        for (int notFoundIndex = 0; notFoundIndex <  notFoundCount; notFoundIndex++){
            printf("\t\t%d\n", IDsNotFoundArray[notFoundIndex]);
        }
        printf("\t\tReason: They do not exist.\n");
    }

    // Sort the complete array by ID
    sortById(students, (*numRecords));

    // Write each record to the bin file
    for (int index = 0; index < (*numRecords); index++){
        writeBinaryFile(filePtrBin, students, index);
    }

    free((void*)IDsNotFoundArray);
    free((void*)IDsExistsArray);
}

/*****************************************************************************************************
    TODO: write function
*****************************************************************************************************/
void addDropUsingKeyboard(Record students[], int *numRecords, int *numGrades){

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
    TODO: write function
*****************************************************************************************************/
void updateGrades(Record students[], int *numRecords, int *numGrades){

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
    This function uses Binary Search to search the entire student array for the desired student ID
*****************************************************************************************************/
int binarySearch(Record students[], int searchKey, int low, int high, int size){
    // Since the size ranges from 0 to size, we cannot assign 0 to "middle"
    int index = -1, middle;

    // Perform a binary search
    while (low <= high){
        middle = (low + high) / 2;

        // Check for a match
        if (searchKey == students[middle].ID){
            index = middle;
            break;
        } else {
            if (searchKey < students[middle].ID){
                // Search the lower half of the array
                high = middle - 1;
            } else {
                // Search the higher half of the array
                low = middle + 1;
            }
        }
    }

    return index;
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