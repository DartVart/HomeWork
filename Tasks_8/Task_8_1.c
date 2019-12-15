#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum Errors
{
    normalCompletion = 0,
    mismatchWithCondition = -1,
    incorrectReading = -2,
    incorrectAccess = -3,
    loopingProgram = -4,
} Errors;

bool isComplianceWithCondition(int numberOfStudent, int numberOfHelper)
{
    return !((numberOfStudent == 1 && numberOfHelper != 1) ||
             (numberOfStudent == 2 && numberOfHelper != 2) ||
             (numberOfStudent == 3 && numberOfHelper != 3));
}

Errors scanNumberOfStudents(int* numberOfStudents)
{
    bool isCorrectInput = scanf("%d", numberOfStudents) == 1;
    if (!isCorrectInput)
    {
        return incorrectReading;
    }
    if (*numberOfStudents < 3)
    {
        return mismatchWithCondition;
    }
    return normalCompletion;
}

Errors scanNumberOfStudent(int* numberOfStudent, const int* studentsWhoHelpCheat, int numberOfStudents)
{
    bool isCorrectReading = scanf("%d", numberOfStudent) == 1;
    if (!isCorrectReading)
    {
        return incorrectReading;
    }
    if (*numberOfStudent > numberOfStudents || *numberOfStudent <= 0 || studentsWhoHelpCheat[*numberOfStudent] != 0)
    {
        return mismatchWithCondition;
    }
    return normalCompletion;
}

Errors scanNumberOfHelper(int* numberOfHelper, int numberOfStudents)
{
    bool isCorrectReading = scanf("%d", numberOfHelper) == 1;
    if (!isCorrectReading)
    {
        return incorrectReading;
    }
    if (*numberOfHelper > numberOfStudents || (*numberOfHelper <= 0 && *numberOfHelper != -1))
    {
        return mismatchWithCondition;
    }
    return normalCompletion;
}

/* studentsWhoHelpCheat[k] contains number of the student who helped the student #k cheat. */
Errors scanStudentsData(int* studentsWhoHelpCheat, int numberOfStudents)
{
    int numberOfStudent = 0;
    int numberOfHelper = 0;
    Errors error = normalCompletion;
    printf("Enter the number of the student and the student whom he cheat off.\n"
           "If the student has not completed the tasks, enter -1:\n");
    for (int i = 0; i < numberOfStudents; i++)
    {
        error = scanNumberOfStudent(&numberOfStudent, studentsWhoHelpCheat, numberOfStudents);
        if (error != normalCompletion)
        {
            return error;
        }

        error = scanNumberOfHelper(&numberOfHelper, numberOfStudents);
        if (error != normalCompletion)
        {
            return error;
        }

        if (!isComplianceWithCondition(numberOfStudent, numberOfHelper))
        {
            return mismatchWithCondition;
        }

        studentsWhoHelpCheat[numberOfStudent] = numberOfHelper;
    }
    return normalCompletion;
}

bool isTaskOption(int taskOption)
{
    return ((taskOption >= 1 && taskOption <= 3) || taskOption == -1);
}

/* The function will return 'loopingProgram' if a looping occurred,
 * and will return 'incorrectAccess' if the some student tried to cheat off the student who did nothing. */
int getTasksOption(int numberOfStudent, int* studentsWhoHelpCheat)
{
    int numberOfHelper = studentsWhoHelpCheat[numberOfStudent];
    if (isTaskOption(numberOfHelper))
    {
        return numberOfHelper;
    }

    // -2 is assigned to prevent repeated access to element
    studentsWhoHelpCheat[numberOfStudent] = -2;
    if (numberOfHelper == -2)
    {
        return loopingProgram;
    }

    int taskOption = getTasksOption(numberOfHelper, studentsWhoHelpCheat);
    if (taskOption == -1)
    {
        return incorrectAccess;
    }
    studentsWhoHelpCheat[numberOfHelper] = taskOption;
    return taskOption;
}

Errors setTasksOption(int* studentsWhoHelpCheat, int numberOfStudents)
{
    for (int i = 1; i <= numberOfStudents; i++)
    {
        int taskOption = getTasksOption(i, studentsWhoHelpCheat);
        if (taskOption == loopingProgram || taskOption == incorrectAccess)
        {
            return taskOption;
        }
        studentsWhoHelpCheat[i] = taskOption;
    }
    return normalCompletion;
}

void displayStudentsData(int* studentsWhoHelpCheat, int numberOfStudents)
{
    printf("Final description:\n");
    int taskOption = 0;
    for (int i = 1; i <= numberOfStudents; i++)
    {
        taskOption = studentsWhoHelpCheat[i];
        if (taskOption == -1)
        {
            printf("The student #%d - an expulsion\n", i);
        }
        else
        {
            printf("The student #%d - task option #%d\n", i, studentsWhoHelpCheat[i]);
        }
    }
}

void displayError(Errors error)
{
    switch (error)
    {
        case loopingProgram:
        {
            fprintf(stderr, "Looping occurred.\n");
            break;
        }
        case incorrectAccess:
        {
            fprintf(stderr, "Someone tried to cheat off a student who has not completed the task.\n");
            break;
        }
        case incorrectReading:
        {
            fprintf(stderr, "Incorrect input.\n");
            break;
        }
        case mismatchWithCondition:
        {
            fprintf(stderr, "Data does not meet the condition.\n");
            break;
        }
        default:
        {
            break;
        }
    }
}

int main()
{
    int numberOfStudents = 0;
    Errors error = normalCompletion;
    printf("Enter number of students:\n");
    error = scanNumberOfStudents(&numberOfStudents);
    if (error != normalCompletion)
    {
        displayError(error);
        return -1;
    }

    int* studentsWhoHelpCheat = (int*) calloc(numberOfStudents + 1, sizeof(int));
    error = scanStudentsData(studentsWhoHelpCheat, numberOfStudents);
    if (error != normalCompletion)
    {
        displayError(error);
        free(studentsWhoHelpCheat);
        return -1;
    }

    error = setTasksOption(studentsWhoHelpCheat, numberOfStudents);
    if (error == normalCompletion)
    {
        displayStudentsData(studentsWhoHelpCheat, numberOfStudents);
    }
    else
    {
        displayError(error);
    }

    free(studentsWhoHelpCheat);
    return 0;
}