/*
 * ================================================================
 * STUDENT RESULT & PERFORMANCE MANAGEMENT SYSTEM
 * ================================================================
 */

#include <stdio.h>
#include <string.h>

/* ================================================================
   CONSTANTS
   ================================================================ */

#define MAX_STUDENTS 5
#define SUBJECTS 5
#define NAME_LENGTH 50


/* ================================================================
   STORAGE CLASS - extern
   ================================================================ */

extern int totalStudents;


/* ================================================================
   STRUCTURE
   ================================================================ */

typedef struct
{
    int rollNumber;
    char name[NAME_LENGTH];

    int marks[SUBJECTS];

    int total;
    float average;
    char grade;
    int result;

} Student;


/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */

Student students[MAX_STUDENTS];

int totalStudents = 0;

const int PASS_MARK = 40;


/* ================================================================
   FUNCTION DECLARATIONS
   ================================================================ */

void displayTitle(void);
void addStudent(void);
void displayStudent(Student *student);
void displayAllStudents(void);
void calculateResult(Student *student);
char calculateGrade(float average);
void searchStudent(void);
void displayStatistics(void);
void initializeStudents(void);
int findStudentByRoll(int rollNumber);
void clearInputBuffer(void);


/* ================================================================
   MAIN FUNCTION
   ================================================================ */

int main(void)
{
    int choice;

    initializeStudents();

    do
    {
        displayTitle();

        printf("\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Display Statistics\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                displayStatistics();
                break;

            case 5:
                printf("\nExiting program...\n");
                printf("Thank you!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    }
    while(choice != 5);

    return 0;
}


/* ================================================================
   DISPLAY TITLE
   ================================================================ */

void displayTitle(void)
{
    printf("\n");
    printf("============================================================\n");
    printf("       STUDENT RESULT & PERFORMANCE MANAGEMENT SYSTEM\n");
    printf("============================================================\n");
}


/* ================================================================
   INITIALIZE STUDENTS
   ================================================================ */

void initializeStudents(void)
{
    for(int i = 0; i < MAX_STUDENTS; i++)
    {
        students[i].rollNumber = 0;
        students[i].name[0] = '\0';

        for(int j = 0; j < SUBJECTS; j++)
        {
            students[i].marks[j] = 0;
        }

        students[i].total = 0;
        students[i].average = 0.0f;
        students[i].grade = 'F';
        students[i].result = 0;
    }
}


/* ================================================================
   ADD STUDENT
   ================================================================ */

void addStudent(void)
{
    Student *student;

    if(totalStudents >= MAX_STUDENTS)
    {
        printf("\nStudent database is full!\n");
        return;
    }

    student = &students[totalStudents];

    printf("\n---------------- ADD STUDENT ----------------\n");

    printf("Enter Roll Number: ");
    scanf("%d", &student->rollNumber);

    if(findStudentByRoll(student->rollNumber) != -1)
    {
        printf("\nError: Roll number already exists!\n");
        return;
    }

    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(student->name, NAME_LENGTH, stdin);

    student->name[strcspn(student->name, "\n")] = '\0';

    const char subjectNames[SUBJECTS][30] =
    {
        "Embedded Systems",
        "Computer Networks",
        "Machine Learning",
        "Digital Electronics",
        "Programming in C"
    };

    for(int i = 0; i < SUBJECTS; i++)
    {
        do
        {
            printf("Enter marks for %-20s: ",
                   subjectNames[i]);

            scanf("%d", &student->marks[i]);

            if(student->marks[i] < 0 ||
               student->marks[i] > 100)
            {
                printf("Invalid marks! Enter 0-100.\n");
            }

        }
        while(student->marks[i] < 0 ||
              student->marks[i] > 100);
    }

    calculateResult(student);

    totalStudents++;

    printf("\nStudent added successfully!\n");

    printf("\n");
    displayStudent(student);
}


/* ================================================================
   CALCULATE RESULT
   ================================================================ */

void calculateResult(Student *student)
{
    static int calculationCount = 0;

    student->total = 0;

    for(int i = 0; i < SUBJECTS; i++)
    {
        student->total += student->marks[i];
    }

    student->average =
        (float)student->total / (float)SUBJECTS;

    student->grade = calculateGrade(student->average);

    student->result = 1;

    for(int i = 0; i < SUBJECTS; i++)
    {
        if(student->marks[i] < PASS_MARK)
        {
            student->result = 0;
            break;
        }
    }

    calculationCount++;
}


/* ================================================================
   CALCULATE GRADE
   ================================================================ */

char calculateGrade(float average)
{
    if(average >= 90)
    {
        return 'A';
    }
    else if(average >= 80)
    {
        return 'B';
    }
    else if(average >= 70)
    {
        return 'C';
    }
    else if(average >= 60)
    {
        return 'D';
    }
    else if(average >= 50)
    {
        return 'E';
    }
    else
    {
        return 'F';
    }
}


/* ================================================================
   DISPLAY ONE STUDENT
   ================================================================ */

void displayStudent(Student *student)
{
    const char subjectNames[SUBJECTS][30] =
    {
        "Embedded Systems",
        "Computer Networks",
        "Machine Learning",
        "Digital Electronics",
        "Programming in C"
    };

    printf("\n");
    printf("-----------------------------------------------\n");

    printf("Roll Number : %d\n", student->rollNumber);
    printf("Name        : %s\n", student->name);

    printf("-----------------------------------------------\n");

    for(int i = 0; i < SUBJECTS; i++)
    {
        printf("%-22s : %d\n",
               subjectNames[i],
               student->marks[i]);
    }

    printf("-----------------------------------------------\n");

    printf("Total       : %d / %d\n",
           student->total,
           SUBJECTS * 100);

    printf("Average     : %.2f\n",
           student->average);

    printf("Grade       : %c\n",
           student->grade);

    if(student->result == 1)
    {
        printf("Result      : PASS\n");
    }
    else
    {
        printf("Result      : FAIL\n");
    }

    printf("-----------------------------------------------\n");
}


/* ================================================================
   DISPLAY ALL STUDENTS
   ================================================================ */

void displayAllStudents(void)
{
    if(totalStudents == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n================ ALL STUDENTS ================\n");

    for(int i = 0; i < totalStudents; i++)
    {
        displayStudent(&students[i]);
    }
}


/* ================================================================
   SEARCH STUDENT
   ================================================================ */

void searchStudent(void)
{
    int rollNumber;
    int index;

    if(totalStudents == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNumber);

    index = findStudentByRoll(rollNumber);

    if(index != -1)
    {
        printf("\nStudent Found!\n");

        displayStudent(&students[index]);
    }
    else
    {
        printf("\nStudent not found!\n");
    }
}


/* ================================================================
   FIND STUDENT BY ROLL NUMBER
   ================================================================ */

int findStudentByRoll(int rollNumber)
{
    for(int i = 0; i < totalStudents; i++)
    {
        if(students[i].rollNumber == rollNumber)
        {
            return i;
        }
    }

    return -1;
}


/* ================================================================
   DISPLAY STATISTICS
   ================================================================ */

void displayStatistics(void)
{
    float highest = -1.0f;
    float lowest = 101.0f;

    int highestStudent = -1;
    int lowestStudent = -1;

    int passCount = 0;
    int failCount = 0;

    float classTotal = 0.0f;
    float classAverage;

    if(totalStudents == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    for(int i = 0; i < totalStudents; i++)
    {
        if(students[i].average > highest)
        {
            highest = students[i].average;
            highestStudent = i;
        }

        if(students[i].average < lowest)
        {
            lowest = students[i].average;
            lowestStudent = i;
        }

        if(students[i].result == 1)
        {
            passCount++;
        }
        else
        {
            failCount++;
        }

        classTotal += students[i].average;
    }

    classAverage =
        classTotal / (float)totalStudents;

    printf("\n");
    printf("=============== CLASS STATISTICS =============\n");

    printf("Total Students : %d\n", totalStudents);
    printf("Passed         : %d\n", passCount);
    printf("Failed         : %d\n", failCount);
    printf("Class Average  : %.2f\n", classAverage);

    if(highestStudent != -1)
    {
        printf("Top Student    : %s\n",
               students[highestStudent].name);

        printf("Top Average    : %.2f\n",
               students[highestStudent].average);
    }

    if(lowestStudent != -1)
    {
        printf("Lowest Student : %s\n",
               students[lowestStudent].name);

        printf("Lowest Average : %.2f\n",
               students[lowestStudent].average);
    }

    printf("================================================\n");
}


/* ================================================================
   CLEAR INPUT BUFFER
   ================================================================ */

void clearInputBuffer(void)
{
    int character;

    while((character = getchar()) != '\n' &&
          character != EOF)
    {
    }
}
