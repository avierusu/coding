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
void processData(char *inFile, char *outFile, Record student[], int *numRecs, int *gradeCount);
void populateStruct(Record students[], int *numRecs, int *gradeCount, char *line);
void createName(char completeName[], char firstName[], char middleName[], char lastName[], char otherName[]);
void createAccount(char account[], char first[], char middle[], char last[], char studentID[]);
float gradeAvg(Record pupil, int numTests);
char *skipSpace(char *line);
void sortById(Record students[], int size);
void sortByGrades(Record students[], int size);
void sortByName(Record students[], int size);
void readBinaryFile(FILE *fpBin, Record student[], int *numRecs, int *numGrades);
void writeBinaryFile(Record students[], int numRecs, FILE *fpBin);
long int getRecordCount(FILE *fpBin, Record pupil[]);

void welcome();
int menu();
void processMenu(Record students[], int *recordCount, int *gradeCount);

void addDropUsingFile(Record students[], int *numRecs, int *gradeCount);
void readAddDropFile(Record students[], int *numRecs, int *gradeCount, FILE *fpAddDrop);
void dropRecordFromFile(Record students[], int *size, int ID, int dropped[],
    int *dropCount, int notFound[], int *notFoundCount, int *flag);
void addDropUsingKeyboard(Record pupil[], int *size, int gradeCount);
void addrecord(Record students[], int *size, int gradeCount);
void dropRecord(Record students[], int *size);
void updateGrades(Record students[], int *numRecs, int *gradeCount);
void readGrades(Record students[], int *numRecs, int *gradeCount, FILE *fpGrades);
void printRecords(Record students[], int numRecs);
int binarySearch(Record rec[], int searchKey, int low, int high, int size);
FILE *openFile(char *fileName, char *mode);
void closeFile(FILE *fp);