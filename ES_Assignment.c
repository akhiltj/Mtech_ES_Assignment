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

/*
 * This variable is declared using extern.
 * The actual definition is provided below.
 */
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

/*
 * Definition of the extern variable.
 */
int totalStudents = 0;


/*
 * const variable demonstrates constant data.
 */
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

    /*
     * Initialize student records.
     */
    initializeStudents();

    /*
     * do-while loop
     *
     * The menu will execute at least once.
     */
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

        /*
         * switch-case demonstrates menu selection.
         */
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
    /*
     * for loop
     *
     * Initialize all student records.
     */
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

    /*
     * Pointer points to the next available student record.
     */
    student = &students[totalStudents];

    printf("\n---------------- ADD STUDENT ----------------\n");

    printf("Enter Roll Number: ");
    scanf("%d", &student->rollNumber);

    /*
     * Check whether roll number already exists.
     */
    if(findStudentByRoll(student->rollNumber) != -1)
    {
        printf("\nError: Roll number already exists!\n");
        return;
    }

    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(student->name, NAME_LENGTH, stdin);

    /*
     * Remove newline character from string.
     */
    student->name[strcspn(student->name, "\n")] = '\0';


    /*
     * Array of subject names.
     *
     * This demonstrates a 2-dimensional character array
     * and strings.
     */
    const char subjectNames[SUBJECTS][30] =
    {
        "Embedded Systems",
        "Computer Networks",
        "Machine Learning",
        "Digital Electronics",
        "Programming in C"
    };


    /*
     * for loop used to enter marks.
     */
    for(int i = 0; i < SUBJECTS; i++)
    {
        do
        {
            printf("Enter marks for %-20s: ",
                   subjectNames[i]);

            scanf("%d", &student->marks[i]);

            /*
             * Decision making.
             */
            if(student->marks[i] < 0 ||
               student->marks[i] > 100)
            {
                printf("Invalid marks! Enter 0-100.\n");
            }

        }
        while(student->marks[i] < 0 ||
              student->marks[i] > 100);
    }


    /*
     * Calculate total, average, grade and result.
     */
    calculateResult(student);


    /*
     * Increase number of students.
     */
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
    /*
     * static variable demonstrates the static storage class.
     *
     * This variable retains its value between function calls.
     */
    static int calculationCount = 0;

    student->total = 0;

    /*
     * Calculate total using array.
     */
    for(int i = 0; i < SUBJECTS; i++)
    {
        student->total += student->marks[i];
    }


    /*
     * Typecasting:
     *
     * student->total is an integer.
     * SUBJECTS is an integer.
     *
     * Explicit conversion to float prevents integer
     * division.
     */
    student->average =
        (float)student->total / (float)SUBJECTS;


    /*
     * Calculate grade.
     */
    student->grade = calculateGrade(student->average);


    /*
     * Initially assume student has passed.
     */
    student->result = 1;


    /*
     * A student must obtain PASS_MARK in every subject.
     */
    for(int i = 0; i < SUBJECTS; i++)
    {
        if(student->marks[i] < PASS_MARK)
        {
            student->result = 0;
            break;
        }
    }


    calculationCount++;

    /*
     * calculationCount is intentionally not printed.
     * Its purpose is to demonstrate static storage.
     */
}


/* ================================================================
   CALCULATE GRADE
   ================================================================ */

char calculateGrade(float average)
{
    /*
     * Decision-making statements.
     */

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


    /*
     * Display marks using for loop.
     */
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


    /*
     * Decision making.
     */
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


    /*
     * Loop through student array.
     */
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


    /*
     * Function returns array index.
     */
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
    /*
     * for loop for searching.
     */
    for(int i = 0; i < totalStudents; i++)
    {
        if(students[i].rollNumber == rollNumber)
        {
            return i;
        }
    }

    /*
     * -1 means not found.
     */
    return -1;
}


/* ================================================================
   DISPLAY STATISTICS
   ================================================================ */

void displayStatistics(void)
{
    int highest = -1;
    int lowest = 101;

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


    /*
     * Analyze all students.
     */
    for(int i = 0; i < totalStudents; i++)
    {
        /*
         * Find highest average.
         */
        if(students[i].average > highest)
        {
            highest = (int)students[i].average;
            highestStudent = i;
        }


        /*
         * Find lowest average.
         */
        if(students[i].average < lowest)
        {
            lowest = (int)students[i].average;
            lowestStudent = i;
        }


        /*
         * Count pass/fail students.
         */
        if(students[i].result == 1)
        {
            passCount++;
        }
        else
        {
            failCount++;
        }


        /*
         * Calculate class total.
         */
        classTotal += students[i].average;
    }


    /*
     * Typecasting again.
     */
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

    /*
     * while loop.
     *
     * Consume remaining characters from input buffer.
     */
    while((character = getchar()) != '\n' &&
          character != EOF)
    {
        /* Nothing required here */
    }
}
