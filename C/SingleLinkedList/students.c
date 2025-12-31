/*****************************************************************************************************
    Description:    This program checks to see if there is a binary file called "stuList.bin" that
                    exists in the directory.

                    If "stuList.bin" doesn't exist:
                    The program opens a text file named "stuList.dat" and reads student records into
                    a linked list. Each line in the file represents a new student record. Reading the
                    student info also includes figuring out the students' account IDs and the average
                    of each students' grades. Then, the student linked list is written to a file
                    called "stuList.bin" in a binary form. Reading from the text file "stuList.dat"
                    occurs only one time. The subsequent manipulations to the struct are carried out
                    using the binary file "stuList.bin"

                    If "stulist.bin" does exist:
                    All this binary information is read into an array of structs and a menu is printed
                    to prompt the user to achieve various tasks:
                        Process Add/Drop using a File
                        Process Individual Add/Drop
                        Sort by element Name (Alphabetic order)
                        Sort by element Average (Ascending order)
                        Sort by element ID number (Ascending order)
                        Update Grades (Should automatically sort by ID number, then recalculate
                        averages)
                        Print List
                        Exit

    Developer:      Avinash Erusu
    Method used:    Array of struct *record*
                    Static memory Allocation
*****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>     // For using calloc
#include <ctype.h>      // For using isalnum()
#include <string.h>     // For using strcat()
#include <stdbool.h>

#include "students.h"

/*****************************************************************************************************
                                        FUNCTION PROTOTYPES
*****************************************************************************************************/
// For reading and storing data
void readData(char *inFile, Node **student, int *numGrades);
void populateStruct(element *student, int *numGrades, char *line);
void addNodeToList(element data, Node **student);
void createAccount(char account[], char first[], char middle[], char last[], char ID[]);
float gradeAvg(element *student, int numGrades);
// For the UI
void welcome();
int menu();
void processMenu(Node **student, int *numRecords, int *numGrades);
// Other
FILE* openFile(char *fileName, char *mode);
void printRecords(Node *student);

/*****************************************************************************************************
                                            MAIN FUNCTION
*****************************************************************************************************/
int main(){
    // Define an array of student records, as well as integers to store the number of records
    // and the number of grades per student
    int gradeCount;

    Node *student = NULL;
    readData(STUD_IN_FILE, &student, &gradeCount);

    printRecords(student);

    // processMenu(students, &gradeCount);

    return 0;
}

/*****************************************************************************************************
    This function opens the file "stuList.dat" and reads each line until the EOF. Since each line
    represents a student record, the students' first, middle, and last names are read and stored in a
    struct. A unique account ID is created for each student. All grades are stored in the respective
    struct, and the average of all grades is calculated and stored as well
*****************************************************************************************************/
void readData(char *inFile, Node **student, int *numGrades){
    FILE *filePtrIn;
    char buffer[LINE_LENGTH];
    // Open the input (stuList.dat) and output (stuList.bin) files
    filePtrIn = openFile(inFile, "r");
    // Create a temporary struct to store the next student's information
    element currStudent = {0};

    // Read through each line of the stuList.dat file
    while ((fgets(buffer, LINE_LENGTH, filePtrIn) != NULL)){

        // Read the data from one line into a struct
        populateStruct(&currStudent, numGrades, buffer);
        addNodeToList(currStudent, student);

    }

    // Close both files
    fclose(filePtrIn);
}

/*****************************************************************************************************
    This function reads one line from the given file and populates the data into a student struct.
    It also creates an account ID for each student, and calculates the average of the students'
    grades
*****************************************************************************************************/
void populateStruct(element *student, int *numGrades, char *line){
    // Create arrays to store the student's first, middle, and last names, as well as their
    // full name, id, and account id
    int currGrade;
    char lastName[LAST_NAME_LENGTH+1],
         firstName[FIRST_NAME_LENGTH+1],
         middleName[MIDDLE_NAME_LENGTH+1],
         studentId[ID_LENGTH+1],
         accountId[ACCT_LENGTH+1],
         ssn[SSN_LENGTH+1];
    
    // Set grade amount to 0 and increment by 1 for each grade we store
    *numGrades = 0;

    // Read student ID as a string
    sscanf(line, "%s", studentId);
    // Use studentId to create a student record
    student->ID = atoi(studentId);
    // Move "line" to the end of ID
    line += ID_LENGTH+1;

    // Read last name
    sscanf(line, "%s", lastName);
    // Store last name in the current student record
    strcpy(student->lastName, lastName);
    // Move "line" to the end of last name
    line += LAST_NAME_LENGTH+1;

    // Read first name
    sscanf(line, "%s", firstName);
    // Store first name in the current student record
    strcpy(student->firstName, firstName);
    // Move "line" to the end of first name
    line += FIRST_NAME_LENGTH+1;

    // Read middle name
    sscanf(line, "%s", middleName);
    // Store middle name in the current student record
    strcpy(student->middleName, middleName);
    // Move "line" to the end of middle name
    line += MIDDLE_NAME_LENGTH+1;

    // Read ssn
    sscanf(line, "%s", ssn);
    // Store ssn in the current student record
    strcpy(student->ssn, ssn);
    // Move "line" to the start of the first grade
    line += SSN_LENGTH+1;
    while (isspace(*line)){
        line += 1;
    }

    // Loop through all grades and store them in student struct
    while (1){
        // Skip leading white spaces
        while (isspace(*line)){
            line++;
        }

        // Check for the end of the line
        if (*line == '\0'){
            break;
        }

        // Store the position for the end of the current grade
        char *end;
        // Store the grade
        currGrade = strtol(line, &end, 10);

        // No valid number found
        if (line == end){
            break;
        }

        // Add the grade to the current student's record
        student->grades[*numGrades] = currGrade;

        // Increment grade count by 1
        (*numGrades)++;

        // Move pointer forward past the parsed number
        line = end;
    }
    // Store -1 at the end of the array of grades
    student->grades[*numGrades] = -1;

    // Create account ID and store it
    createAccount(accountId, firstName, middleName, lastName, studentId);
    // Store account ID in the current student record
    strcpy(student->account, accountId);

    // Calculate the average for all the student's grades
    student->avg = gradeAvg(student, *numGrades);
}

/*****************************************************************************************************
    This function traverses through the current linked list and adds a new node into the list, in
    ascending order of student ID
*****************************************************************************************************/
void addNodeToList(element data, Node **headNode){
    // If the linked list is empty, add the first node to the beginning of the list
    // Also, if the new student's ID is a smaller number than the first in the list, add
    // the new node to the beginning
    if (((*headNode) == NULL) || (data.ID < (*headNode)->data.ID)){
        addNodeAtHead(headNode, data);
        return;
    }

    // Traverse through the linked list and determine where the new node should be placed
    // by comparing student IDs
    // When we insert a node, we need the pointer to the previous node, so create a temporary
    // pointer to store its address
    Node *prevNode = (*headNode);
    // Also create a temporary pointer to store the current node, so we don't change the address
    // of the head node
    Node *currNode = (*headNode);
    // Since we know the node will not be placed at the beginning of the list, we can advance
    // to the next node
    currNode = currNode->nextNode;
    while (currNode != NULL){
        // Compare the IDs of the new node and the current node to determine where the new
        // node should be placed
        // If the new student's ID is less than the current student's ID, we exit the loop
        // to place the new node here
        if (data.ID < currNode->data.ID){
            break;
        }

        // Otherwise, continue traversing through the list
        currNode = currNode->nextNode;
    }
    // Once we find where to place the new node, add the new node in the appropriate spot
    // Also, if we reach the end of the list, add the new node to the end
    addNode(prevNode, data);
}

/*****************************************************************************************************
    This function creates an account ID in the form "abc1234", where "abc" are the student's first,
    middle, and last initials respectively, and "1234" are the last four digits of the student's ID
*****************************************************************************************************/
void createAccount(char account[], char first[], char middle[], char last[], char ID[]){
    // Create an array to store account ID
    char accountID[ACCT_LENGTH+1];
    // Use the student's initials at the beginning
    accountID[0] = first[0];
    accountID[1] = middle[0];
    accountID[2] = last[0];
    // Use the student's ID at the end
    for (int index = 3; index < ACCT_LENGTH; index++){
        accountID[index] = ID[index-2];
    }
    // Copy the newly created account ID into the student record
    strcpy(account, accountID);
}

/*****************************************************************************************************
    This function calculates the average of all grades for each student record
*****************************************************************************************************/
float gradeAvg(element *student, int numGrades){
    // Create float variables to store sum and average
    float sum = 0.0, average = 0.0;

    // Loop through each grade and add it to sum
    for (int gradeIndex = 0; gradeIndex < numGrades; gradeIndex++){
        // Add the current grade to the sum
        // printf("\n%d: %f", gradeIndex, student.grades[gradeIndex]);
        sum += student->grades[gradeIndex];
    }

    // Validate against dividing by zero
    if(numGrades != 0){
        // Calculate average
        average = sum / numGrades;
    }

    return average;
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
    printf("\t1. Bulk Add/Drop Students\n");
    printf("\t2. Add/Drop By Student\n");
    printf("\t3. Sort Students by Name\n");
    printf("\t4. Sort Students by Average Grade\n");
    printf("\t5. Sort Students by ID\n");
    printf("\t6. Update Grades by Student\n");
    printf("\t7. Bulk Update Grades\n");
    printf("\t8. Print Student List\n");
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
void processMenu(Node **student, int *numRecords, int *numGrades){
    int choice, displayCount = 0;
    // Display the welcome banner
    // welcome();
    // Display the menu and accept the user's choice
    choice = menu();

    // Keep displaying the menu until the user chooses to exit
    while (choice != 9){
        // Use a switch to perform different actions depending on the user's choice
        switch (choice){
            case 1:
                // Bulk Add/Drop Students
                // TODO: make function
                break;
            case 2:
                // Add/Drop By Student
                // TODO: make function
                break;
            case 3:
                // Sort Students by Name
                // TODO: make function
                // Display the records after sorting
                // TODO: make function
                break;
            case 4:
                // Sort Students by Average Grade
                // TODO: make function
                // Display the records after sorting
                // TODO: make function
                break;
            case 5:
                // Sort Students by ID
                // TODO: make function
                // Display the records after sorting
                // TODO: make function
                break;
            case 6:
                // Update Grades by Student
                // TODO: make function
                break;
            case 7:
                // Bulk Update Grades
                // TODO: make function
                break;
            case 8:
                // Print Student List
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
                printRecords(*student);

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
void printRecords(Node *student){
    // Print the top banner
    // TODO: fix the formatting for this top bar
    printf("-------------------------------------------------------------------------------------\n");
    printf("Record# ID#\tName\t\t\t\t     Account#\tAvg.Gr\n");
    printf("-------------------------------------------------------------------------------------\n");

    for (int index = 1; student != NULL; index++){
        printf("%03d: ", index+1);
        printf("   %d", student->data.ID);
        printf("\t%-10s %-10s %-15s", student->data.firstName, student->data.middleName, student->data.lastName);
        printf("%-.7s", student->data.account);
        printf("%s ", student->data.ssn);
        printf("\t%5.2f\n", student->data.avg);

        student = student->nextNode;
    }
}