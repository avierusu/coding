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
                        Sort by Student Average (Ascending order)
                        Sort by Student ID number (Ascending order)
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

#define STUD_IN_FILE "stuListShort.dat"
#define OUT_BIN_FILE "stuList.bin"
#define ID_LENGTH 5
#define FIRST_NAME_LENGTH 10
#define MIDDLE_NAME_LENGTH 10
#define LAST_NAME_LENGTH 15
#define ACCT_LENGTH 7
// There are actually 10 grades, but to search for a -1 in the binary file, count is increased by 1
#define NUM_GRADES 11
#define LINE_LENGTH 200
// There are 100 records, but we will store space for extra when we add/remove records later
#define MAX_RECORDS 150
#define TRUE 1
#define FALSE 0

// Define and name a struct to store student records
typedef struct student{
    int ID;
    char firstName[FIRST_NAME_LENGTH+1];
    char middleName[MIDDLE_NAME_LENGTH+1];
    char lastName[LAST_NAME_LENGTH+1];
    char account[ACCT_LENGTH+1];
    float grades[NUM_GRADES];
    float avg;
} Student;

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
    DROP
} RecordOperation;
// TODO: Make a validateID() function that does all the ID validation, checking if digits, length,
// exists or not. called by addDropByStudent and other thangs, uses argument "RecordOperation operation"
// do determine if you add/drop and print stuff about adding or exists/notexists etc etc. then calls the
// appropriate add/drop student function which will simply add or drop yus

/*****************************************************************************************************
                                        FUNCTION PROTOTYPES
*****************************************************************************************************/
// For reading and storing data
void readData(char *inFile, char *outFile, Student students[], int *numRecords, int *numGrades);
void populateStruct(Student students[], int *numRecords, int *numGrades, char *line);
void createAccount(char account[], char first[], char middle[], char last[], char ID[]);
float gradeAvg(Student student, int numGrades);
// For sorting data
void sortById(Student students[], int numRecords);
void sortByGradeAverage(Student students[], int numRecords);
void sortByName(Student students[], int numRecords);
void sortSubArray(Student *inArray, int left, int right, SortMode mode);
int compare(Student *student1, Student *student2, SortMode mode);
void swap(Student *inArray, int firstIndex, int secondIndex);
// For adding or dropping student records
void addDropByStudent(Student *students, int *numRecords, int *numGrades);
void addRecord(Student *students, int *numRecords, int *numGrades);
void dropRecord(Student *students, int *numRecords);
// Other
int binarySearch(Student students[], int searchKey, int low, int high, int size);
FILE* openFile(char *fileName, char *mode);
void printRecords(Student students[], int numRecords);


/*****************************************************************************************************
                                            MAIN FUNCTION
*****************************************************************************************************/
int main(){
    // Define an array of student records, as well as integers to store the number of records
    // and the number of grades per student
    Student students[MAX_RECORDS];
    int recordCount = 0;
    int gradeCount;
    FILE *filePtrBin;

    readData(STUD_IN_FILE, OUT_BIN_FILE, students, &recordCount, &gradeCount);
    printRecords(students, recordCount);

    addDropByStudent(students, &recordCount, &gradeCount);
    // sortByGradeAverage(students, recordCount);
    // sortByName(students, recordCount);

    printRecords(students, recordCount);

    return 0;
}

/*****************************************************************************************************
    This function opens the file "stuList.dat" and reads each line until the EOF. Since each line
    represents a student record, the students' first, middle, and last names are read and stored in a
    struct. A unique account ID is created for each student. All grades are stored in the respective
    struct, and the average of all grades is calculated and stored as well
*****************************************************************************************************/
void readData(char *inFile, char *outFile, Student students[], int *numRecords, int *numGrades){
    FILE *filePtrIn, *filePtrBin;
    char buffer[LINE_LENGTH];
    // char *line;
    // Open the input (stuList.dat) and output (stuList.bin) files
    filePtrIn = openFile(inFile, "r");
    filePtrBin = openFile(outFile, "w");

    // Read through each line of the stuList.dat file
    while ((fgets(buffer, LINE_LENGTH, filePtrIn) != NULL) && (*numRecords < MAX_RECORDS)){
        // line = buffer;

        // Read the data from one line into a struct
        populateStruct(students, numRecords, numGrades, buffer);

        // Write the data in the struct to the "stuList.bin" file
        // TODO: Write current struct to bin file

        (*numRecords)++;
    }

    // Sort the array of structs by student ID in increasing order
    // before sending back to main
    sortById(students, (*numRecords));

    // Close both files
    fclose(filePtrIn);
    fclose(filePtrBin);
}

/*****************************************************************************************************
    This function reads one line from the given file and populates the data into a student struct.
    It also creates an account ID for each student, and calculates the average of the students'
    grades
*****************************************************************************************************/
void populateStruct(Student students[], int *numRecords, int *numGrades, char *line){
    // Create arrays to store the student's first, middle, and last names, as well as their
    // full name, id, and account id
    char lastName[LAST_NAME_LENGTH],
         firstName[FIRST_NAME_LENGTH],
         middleName[MIDDLE_NAME_LENGTH],
         studentId[ID_LENGTH],
         accountId[ACCT_LENGTH],
         currGrade[3];
    
    // Set grade amount to 0 and increment by 1 for each grade we store
    *numGrades = 0;

    // Read student ID as a string
    sscanf(line, "%s", studentId);
    // Use studentId to create a student record
    students[*numRecords].ID = atoi(studentId);
    // Move "line" to the end of ID
    line += ID_LENGTH+1;

    // Read last name
    sscanf(line, "%s", lastName);
    // Store last name in the current student record
    strcpy(students[*numRecords].lastName, lastName);
    // Move "line" to the end of last name
    line += LAST_NAME_LENGTH+1;

    // Read first name
    sscanf(line, "%s", firstName);
    // Store first name in the current student record
    strcpy(students[*numRecords].firstName, firstName);
    // Move "line" to the end of first name
    line += FIRST_NAME_LENGTH+1;

    // Read middle name
    sscanf(line, "%s", middleName);
    // Store middle name in the current student record
    strcpy(students[*numRecords].middleName, middleName);
    // Move "line" to the start of the first grade
    line += MIDDLE_NAME_LENGTH+1;
    while (isspace(*line)){
        line += 1;
    }

    // Loop through all grades and store them in student struct
    while (isdigit(*line)){
        // Read the next grade
        sscanf(line, "%s", currGrade);
        // Add the grade to the current student's record
        students[*numRecords].grades[*numGrades] = atoi(currGrade);

        // TODO: optimize this more
        // Move "line" to the end of the grade
        // Each grade takes 3 spaces, plus an extra space
        line += 3;
        // Depending on the number of digits the current grade is and the next grade is,
        // there may be between 0 and 2 extra placeholder spaces here
        while (isspace(*line)){
            line += 1;
        }

        // Increment grade count by 1
        (*numGrades)++;
    }
    // Store -1 at the end of the array of grades
    students[*numRecords].grades[*numGrades] = -1;

    // Create account ID and store it
    createAccount(accountId, firstName, middleName, lastName, studentId);
    // Store account ID in the current student record
    strcpy(students[*numRecords].account, accountId);

    // Calculate the average for all the student's grades
    students[*numRecords].avg = gradeAvg(students[*numRecords], *numGrades);
}

/*****************************************************************************************************
    This function creates an account ID in the form "abc1234", where "abc" are the student's first,
    middle, and last initials respectively, and "1234" are the last four digits of the student's ID
*****************************************************************************************************/
void createAccount(char account[], char first[], char middle[], char last[], char ID[]){
    // Create an array to store account ID
    char accountID[7];
    // Use the student's initials at the beginning
    accountID[0] = first[0];
    accountID[1] = middle[0];
    accountID[2] = last[0];
    // Use the student's ID at the end
    for (int index = 3; index < 7; index++){
        accountID[index] = ID[index-2];
    }
    // Copy the newly created account ID into the student record
    strcpy(account, accountID);
}

/*****************************************************************************************************
    This function calculates the average of all grades for each student record
*****************************************************************************************************/
float gradeAvg(Student student, int numGrades){
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
void sortById(Student students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by ID
    sortSubArray(students, 0, (numRecords - 1), SORT_BY_ID);
}

/*****************************************************************************************************
    This function uses quick sort to sort student records by the average of their grades in
    increasing order
*****************************************************************************************************/
void sortByGradeAverage(Student students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by average
    sortSubArray(students, 0, numRecords - 1, SORT_BY_AVERAGE);
}

/*****************************************************************************************************
    This function uses quick sort to sort student records by their full name in increasing order
*****************************************************************************************************/
void sortByName(Student students[], int numRecords){
    // Sort the array from start (index 0) to end (index size-1) by name
    sortSubArray(students, 0, numRecords - 1, SORT_BY_NAME);
}

/*****************************************************************************************************
    This function sorts one section of the array by splitting it in two and recursively calling
    itself to sort the smaller sections, until the full array is sorted
*****************************************************************************************************/
void sortSubArray(Student *inArray, int left, int right, SortMode mode){
    int leftSwap = left;
    int rightSwap = right;
    // Calculate the middle student record in the array
    Student pivot = inArray[(left + right) / 2];

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
int compare(Student *student1, Student *student2, SortMode mode){
    // Check which sorting mode to sort by
    switch(mode){
        case SORT_BY_AVERAGE:
            // Compare averages by subtracting and returning the difference
            return (student1 -> avg) - (student2 -> avg);
            break;
        case SORT_BY_NAME:
            // Compare names using strcmp and return the output
            return strcmp( (student1 -> lastName) , (student2 -> lastName));
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
void swap(Student *inArray, int firstIndex, int secondIndex){
    Student temp = inArray[firstIndex];
    inArray[firstIndex] = inArray[secondIndex];
    inArray[secondIndex] = temp;
}

/*****************************************************************************************************
    This function adds or drops a student record when the user enters an 'A' or a 'D' in the command
    line.
*****************************************************************************************************/
void addDropByStudent(Student *students, int *numRecords, int *numGrades){
    // Create a variable to store the user's choice of whether to add a student ('A'), drop a
    // student ('D'), or quit out of the prompts ('Q')
    char choice;

    // Repeatedly prompt the user for input until they decide to quit
    do {
        printf("\n\t--------------------------------------------------------");
        printf("\n\t\tA - Add a student record");
        printf("\n\t\tD - Drop a student record");
        printf("\n\t\tQ - Quit");
        printf("\n\tEnter your choice: ");
        // Store the user's input
        scanf(" %c", &choice);

        // Process the user's input
        switch (toupper(choice)){
            case 'Q':
                // Exit the loop
                break;
            case 'A':
                // Add a student record
                addRecord(students, numRecords, numGrades);
                break;
            case 'D':
                // Drop a student record
                dropRecord(students, numRecords);
                break;
            default:
                // Any invalid option
                printf("\n\t\tInvalid choice.\n");
        }
    } while (toupper(choice) != 'Q');
}

/*****************************************************************************************************
    This function adds a student record to the array of structs
*****************************************************************************************************/
void addRecord(Student *students, int *numRecords, int *numGrades){
    int ID, IDSize, result = 0;
    Student temp;
    char lastName[LAST_NAME_LENGTH],
         firstName[FIRST_NAME_LENGTH],
         middleName[MIDDLE_NAME_LENGTH],
         studentId[ID_LENGTH+1],
         accountId[ACCT_LENGTH+1];
    
    fflush(stdin);
    printf("\n\t\tEnter the ID to be added: ");
    scanf("%d%n", &ID, &IDSize);
    
    // If the ID is not 5 digits long, continue to reprompt
    // Also, if the ID is already in the list, continue to reprompt
    while (IDSize != ID_LENGTH || result != -1){
        // First, check if the ID is 5 digits long
        if (IDSize != ID_LENGTH){
            // If not, reprompt and start the loop from the beginning
            printf("\n\t\tThe ID should be %d digits long\n", ID_LENGTH);
            fflush(stdin);
            printf("\t\tEnter the ID to be added: ");
            scanf("%d%n", &ID, &IDSize);
            continue;
        }
        // If we reach here, the ID is the correct length
        
        // Search to see if the ID already exists
        result = binarySearch(students, ID, 0, ((*numRecords)-1), (*numRecords));

        // Next, check if the ID entered already exists
        if (result != -1){
            // If so, reprompt
            printf("\n\t\tThe ID you entered already exists.\n");
            fflush(stdin);
            printf("\t\tEnter the ID to be added: ");
            scanf("%d%n", &ID, &IDSize);
        }
    }
    // If we reach here, the ID is the correct length and does not already exist in the array

    // Now, we can add the ID to the array
    // Increment the size of the array by 1
    (*numRecords)++;

    // Store data of the new record in the last array element, i.e. (size-1)
    // Store ID
    students[(*numRecords)-1].ID = ID;

    // Get and populate first, middle, and last names
    fflush(stdin);
    printf("\n");
    printf("\tEnter First name: ");
    scanf("%s", &firstName);
    strcpy(students[(*numRecords)-1].firstName, firstName);

    fflush(stdin);
    printf("\tEnter Middle name: ");
    scanf("%s", &middleName);
    strcpy(students[(*numRecords)-1].middleName, middleName);

    fflush(stdin);
    printf("\tEnter Last name: ");
    scanf("%s", &lastName);
    strcpy(students[(*numRecords)-1].lastName, lastName);

    // Get grades
    printf("\n\tEnter all %d grades, each separated by a space:\n", (*numGrades));

    for (int index = 0; index < (*numGrades); index++){
        fflush(stdin);
        printf("\t\tGrade %2d of %2d: ", (index+1), (*numGrades));
        // FIXME: scanf fails here
        scanf("%d", (students[(*numRecords)-1].grades[index]));
    }

    // Calculate the average of all grades
    students[(*numGrades)-1].avg = gradeAvg(students[(*numGrades)-1], (*numGrades));

    // Create the student's account ID
    snprintf(studentId, ACCT_LENGTH+1, "%d", ID);
    createAccount(accountId, firstName, middleName, lastName, studentId);
    strcpy(students[(*numRecords)-1].account, accountId);

    // Re-sort the array
    sortById(students, (*numRecords));
}

/*****************************************************************************************************
    This function drops a student record from the array of structs
*****************************************************************************************************/
void dropRecord(Student *students, int *numRecords){
    int ID, IDSize = 0, reply, result = -1, allDigits = 0;
    char studentID[ID_LENGTH+1], buffer[32];

    printf("\n\tEnter ID to be dropped: ");
    fflush(stdin);
    scanf("%s", buffer);
    IDSize = strlen(buffer);

    // If the ID is not 5 digits long, continue to reprompt
    // Also, if the ID is not already in the list, continue to reprompt
    while (IDSize != ID_LENGTH || result == -1 || !allDigits){
        // First, check if the ID entered is only digit characters
        allDigits = 1;
        // Loop through each character in the buffer
        for (int index = 0; index < IDSize; index++){
            if (!isdigit((unsigned char)buffer[index])){
                // If a character is not a digit, break out of the loop
                allDigits = 0;
                break;
            }
        }
        // If any character was not a digit, reprompt continue to the start of the next loop
        if (!allDigits){
            printf("\n\tInvalid ID.\n");
            fflush(stdin);
            printf("\tEnter the ID to be dropped: ");
            scanf("%s", buffer);
            IDSize = strlen(buffer);
            continue;
        }

        // Next, check if the ID is 5 digits long
        if (IDSize != ID_LENGTH){
            // If not, reprompt and start the loop from the beginning
            printf("\n\tThe ID should be %d digits long\n", ID_LENGTH);
            fflush(stdin);
            printf("\tEnter the ID to be dropped: ");
            scanf("%s", buffer);
            IDSize = strlen(buffer);
            continue;
        }
        // If we reach here, the ID is the correct length
        
        // Once the ID entered is all digits and the correct length,
        // convert to int and search to see if the ID already exists
        ID = atoi(buffer);
        result = binarySearch(students, ID, 0, ((*numRecords)-1), (*numRecords));

        // Next, check if the ID entered does not already exist
        if (result == -1){
            // If so, reprompt
            printf("\n\tThe ID you entered doesn't exist.\n");
            fflush(stdin);
            printf("\tEnter the ID to be dropped: ");
            scanf("%s", buffer);
            IDSize = strlen(buffer);
        }
    }
    // If we reach here, the ID is the correct length and already exists in the array

    // Now, we can drop the student from the array
    printf("\n\tThe record that you requested to be dropped is:");
    printf("\n\t%d  ", students[result].ID);
    printf("%s %s %s", students[result].firstName, students[result].middleName, students[result].lastName);
    printf("  %s", students[result].account);
    printf("\t%5.2f\n", students[result].avg);

    printf("\n\tYou have selected to drop the record with ID: %d", ID);
    printf("\n\tAre you sure? (Y/N): ");
    fflush(stdin);
    scanf(" %c", &reply);
    if ( toupper(reply) == 'Y' ){
        // If the user chooses to drop the grade, then drop it from the array
        for (int index = result; index < (*numRecords)-1; index++){
            // Move all elements after the chosen record's index up by one
            students[index] = students[index+1];
            // *(students+index) = *(students+index+1);
        }

        // Clear the last record (optional but recommended for safety)
        memset(&students[(*numRecords) - 1], 0, sizeof(Student));
        // Reduce the size of the array by 1
        (*numRecords)--;
        printf("\n\tSuccessfully dropped the record with ID \"%d\"\n", ID);
    } else {
        // If the user replies with somthing other than 'Y':
        printf("\n\tYou chose not to drop the record with ID #%d\n", ID);
    }
}

/*****************************************************************************************************
    This function uses Binary Search to search the entire student array for the desired student ID
*****************************************************************************************************/
int binarySearch(Student students[], int searchKey, int low, int high, int size){
    // Since we are searching by comparing IDs, we must first sort by ID
    sortById(students, size);
    // Since the size ranges from 0 to size, we cannot assign 0 to "middle"
    int index = -1, middle;

    // Perform a binary search
    while (low <= high){
        middle = (low + high) / 2;

        // Check for a match
        if (searchKey == students[middle].ID){
            index = middle;
            return index;
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

/*****************************************************************************************************
    This function prints out the data stored in the student array depending on how any from the list
    need to be printed
*****************************************************************************************************/
void printRecords(Student students[], int numRecords){
    // Print the top banner
    printf("-------------------------------------------------------------------------------------\n");
    printf("Record# ID#\tName\t\t\t\t     Account#\tAvg.Gr\n");
    printf("-------------------------------------------------------------------------------------\n");

    // Print each record
    for(int index = 0; index < numRecords; index++){
        printf("%03d: ", index+1);
        printf("   %d", students[index].ID);
        printf("\t%-10s %-10s %-15s", students[index].firstName, students[index].middleName, students[index].lastName);
        printf("%-.7s", students[index].account);
        printf("\t%5.2f\n", students[index].avg);
    }
}