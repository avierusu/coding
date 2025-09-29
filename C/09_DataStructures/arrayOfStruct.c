/*****************************************************************************************************
    Description:    This program checks to see if there is a binary file called "stuList.bin" that
                    exists in the directory.

                    If "stuList.bin" doesn't exist:
                    The program opens a text file named "stuList.dat" and reads student records into
                    a struct. Each line in the file represents a new student record. Reading the
                    student info also includes figuring out the students' ID numbers and the average
                    of each students' grades. Then, each student structure is written to a file called
                    "stuList.bin" in a binary form. Reading from the text file "stuList.dat" occurs
                    only one time. The subsequent manipulations to the struct are carried out using
                    the binary file "stuList.bin"

                    If "stulist.bin" does exist:
                    All this binary information is read into an array and a menu is printed to prompt
                    the user to acchieve different tasks

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
#define NAME_LENGTH 35
#define ACCT_LENGTH 7
#define NUM_GRADES 13
// There are actually 12 grades, but to search for a -1, count is increased by 1
#define LUNE_LENGTH 200
#define MAX_RECORDS 100
#define TRUE 1
#define FALSE 0

// Define and name a struct to store student records
typedef struct record{
    int ID;
    char name[NAME_LENGTH + 1];
    char account[ACCT_LENGTH + 1];
    float grades[NUM_GRADES];
    float avg;
} Record;

// Function prototypes
void processData(char *, char *, Record [], int *, int *);
void populateStruct(Record [], int *, int *, char *);
void createName(char [], char [], char [], char [], char []);
void createAccount(char [], char [], char [], char [], char []);
float gradeAvg(Record, int);
char *skipSpace(char *);
void sortById(Record [], int);
void sortByGrades(Record [], int);
void sortByName(Record [], int);
void readBinaryFile(FILE *, Record [], int *, int *);
void writeBinaryFile(Record [], int, FILE *);
long int getRecordCount(FILE *, Record []);

void welcome();
int menu();
void processMenu();

void addDropUsingFile(Record [], int *, int *);
void readAddDropFile(Record [], int *, int *, FILE *);
void dropRecordFromFile(Record [], int *, int, int [], int *, int [], int *, int *);
void addDropUsingKeyboard(Record [], int *, int);
void addrecord(Record [], int *, int);
void dropRecord(Record student[], int *size);
void updateGrades(Record [], int *, int *);
void readGrades(Record [], int *, int *, FILE *);
void printRecords(Record [], int);
int binarySearch(Record [], int, int, int, int);
FILE *openFile(char *, char);
void closeFile(FILE *);