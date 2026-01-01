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
// For adding, updating, and dropping student records
void addDropByStudent(Node **student, int *numGrades);
void validateID(Node **student, int *numGrades, RecordOperation operation);
void searchList(Node **currNode, Node **prevNode, int ID);
void requestData(Node **student, int *numGrades, int ID, int result, RecordOperation operation);
void addRecord(Node **student, int *numGrades, int ID, char firstName[],
    char middleName[], char lastName[], int grades[]);
void updateGrades(Node **student, int result, int ID, int grades[]);
void confirmDrop(Node **student, int ID, int result);
void dropRecord(Node **student, int result);
// Other
FILE* openFile(char *fileName, char *mode);
void printRecords(Node *student);
void printSingleRecord(Node *student, int index);

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
    This function adds or drops a student record when the user enters an 'A' or a 'D' in the command
    line.
*****************************************************************************************************/
void addDropByStudent(Node **student, int *numGrades){
    // Create a variable to store the user's choice of whether to add a student ('A'), drop a
    // student ('D'), or quit out of the prompts ('Q')
    char choice;

    // Repeatedly prompt the user for input until they decide to quit
    do {
        printf("\n\n\t--------------------------------------------------------");
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
                validateID(student, numGrades, ADD);
                break;
            case 'D':
                // Drop a student record
                validateID(student, numGrades, DROP);
                break;
            default:
                // Any invalid option
                printf("\n\t\tInvalid choice.\n");
        }
    } while (toupper(choice) != 'Q');
}

/*****************************************************************************************************
    This function is ran before adding or dropping a student record. It's function is to accept an ID
    from the user and run it through various checks to validate whether or not it is valid.
*****************************************************************************************************/
void validateID(Node **headNode, int *numGrades, RecordOperation operation){
    // Create a temporary node to traverse through the linked list with
    Node *currNode, *prevNode = NULL;
    int ID, IDSize, allDigits = 0;
    char buffer[32], message[32];
    bool binaryCheck;

    // Change the prompt message and binary search check depending on the requested operation
    if (operation == DROP){
        strcpy(message, "Enter ID to be dropped: ");
        currNode = NULL;
        binaryCheck = (currNode == NULL);
    } else if (operation == ADD) {
        strcpy(message, "Enter ID to be added: ");
        currNode = (*headNode);
        binaryCheck = (currNode != NULL);
    } else {
        strcpy(message, "Enter ID to be updated: ");
        currNode = NULL;
        binaryCheck = (currNode == NULL);
    }

    printf("\n\t%s", message);
    fflush(stdin);
    scanf("%s", buffer);
    IDSize = strlen(buffer);
    
    // If the ID is not 5 digits long, continue to reprompt
    // Also, if the ID is already in the list, continue to reprompt
    while (IDSize != ID_LENGTH || binaryCheck || !allDigits){
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
            printf("\n\tInvalid ID.");
            fflush(stdin);
            printf("\n\t%s", message);
            scanf("%s", buffer);
            IDSize = strlen(buffer);
            continue;
        }

        // Next, check if the ID is 5 digits long
        if (IDSize != ID_LENGTH){
            // If not, reprompt and start the loop from the beginning
            printf("\n\tThe ID should be %d digits long", ID_LENGTH);
            fflush(stdin);
            printf("\n\t%s", message);
            scanf("%s", buffer);
            IDSize = strlen(buffer);
            continue;
        }
        // If we reach here, the ID is the correct length
        
        // Once the ID entered is all digits and the correct length,
        // convert to int and search to see if the ID already exists
        ID = atoi(buffer);
        // Reset the current node and previous node so we can traverse through the list from the beginning
        currNode = (*headNode);
        prevNode = NULL;
        // Traverse through the linked list to search for the requested ID
        searchList(&currNode, &prevNode, ID);

        // Re-check the binary search prompt and validate
        if (operation == ADD){
            binaryCheck = (currNode != NULL);
        } else {
            binaryCheck = (currNode == NULL);
        }
        // Next, check if the ID entered already exists
        if (binaryCheck){
            // If so, reprompt
            // If we are adding records and the ID already exists, reprompt
            // If we are dropping records and the ID doesn't exist, reprompt
            if (operation == ADD){
                printf("\n\tThe ID you entered already exists.");
            } else {
                printf("\n\tThe ID you entered doesn't exist.");
            }
            fflush(stdin);
            printf("\n\t%s", message);
            scanf("%s", buffer);
            IDSize = strlen(buffer);
        }
    }
    // If we reach here, the ID is valid and we can continue with adding/dropping

    if (operation == DROP){
        // Drop the record
        // TODO: Make these functions
        // confirmDrop(currNode, ID, result);
    } else if (operation == ADD) {
        // Obtain more information from the user, then add the record
        // requestData(currNode, numGrades, ID, result, ADD);
    } else {
        // requestData(currNode, numGrades, ID, result, UPDATE);
    }
}

/*****************************************************************************************************
    This function traverses through the linked list to search for a particular ID. If the ID is
    found, we exit the function, and currNode will point to the node containing the student with
    the requested ID. If the ID is not found, currNode will point to null
*****************************************************************************************************/
void searchList(Node **currNode, Node **prevNode, int ID){
    // Traverse through the list until we reach the end
    while (*currNode != NULL){
        // Check if the current node contains the requested ID
        if ((*currNode)->data.ID == ID){
            // This means the student already exists
            // We can now exit the function
            // printf("ID %d found in the list\n", ID);
            // printSingleRecord(*currNode, 1);
            return;
        }

        // Move to the next node in the list
        *prevNode = *currNode;
        *currNode = (*currNode)->nextNode;
    }
    // If we traverse through the entire list and do not find the ID before currNode points to NULL
    // (i.e. we reached the end of the list), this means the student does not exist
    // printf("ID not found in the list.\n");
}

/*****************************************************************************************************
    This function is run before adding a student record. It's function is to obtain more data from
    the user about the student to be added.
*****************************************************************************************************/
void requestData(Node **student, int *numGrades, int ID, int result, RecordOperation operation){
    // TODO: make the function
}

/*****************************************************************************************************
    This function adds a student record to the array of structs
*****************************************************************************************************/
void addRecord(Node **student, int *numGrades, int ID, char firstName[],
    char middleName[], char lastName[], int grades[]){
    // TODO: make the function
}

/*****************************************************************************************************
    This function updates the grades for a student, given their ID and their new grades
*****************************************************************************************************/
void updateGrades(Node **student, int result, int ID, int grades[]){
    // TODO: make the function
}

/*****************************************************************************************************
    This function is run before dropping a record. It's function is to confirm whether or not
    the user wants to drop the requested student record
*****************************************************************************************************/
void confirmDrop(Node **student, int ID, int result){
    // TODO: make the function
}

/*****************************************************************************************************
    This function drops a student record from the array of structs
*****************************************************************************************************/
void dropRecord(Node **student, int result){
    // TODO: make the function
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
        printSingleRecord(student, index);
        student = student->nextNode;
    }
}

void printSingleRecord(Node *student, int index){
    printf("%03d: ", index);
    printf("   %d", student->data.ID);
    printf("\t%-10s %-10s %-15s", student->data.firstName, student->data.middleName, student->data.lastName);
    printf("%-.7s", student->data.account);
    printf("%s ", student->data.ssn);
    printf("\t%5.2f\n", student->data.avg);
}