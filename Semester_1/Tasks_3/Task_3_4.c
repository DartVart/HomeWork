#include <stdio.h>
#include <stdbool.h>

bool enterInitialData(int* numberOfUsers, int* requiredNumberOfActions, int* requiredTimeInterval)
{
    printf("Enter the number of users:\n");
    bool isCorrectInput = scanf("%d", numberOfUsers) != 0;
    if (!isCorrectInput || *numberOfUsers <= 0)
    {
        printf("Incorrect input!");
        return false;
    }

    printf("Enter the required number of actions:\n");
    isCorrectInput = scanf("%d", requiredNumberOfActions) != 0;
    if (!isCorrectInput || *requiredNumberOfActions < 0)
    {
        printf("Incorrect input!");
        return false;
    }

    printf("Enter the required time period:\n");
    isCorrectInput = scanf("%d", requiredTimeInterval) != 0;
    if (!isCorrectInput || *requiredTimeInterval <= 0)
    {
        printf("Incorrect input!");
        return false;
    }
    return true;
}

bool getNumberOfSuitableActions(int numberOfUserActions, int requiredTimeInterval, int* counterOfSuitableActions)
{
    int timeIntervalAfterAction = 0;
    bool isCorrectInput = true;

    for (int i = 0; i < numberOfUserActions; i++)
    {
        isCorrectInput = scanf("%d", &timeIntervalAfterAction) != 0;
        if (!isCorrectInput || timeIntervalAfterAction <= 0)
        {
            return false;
        }

        if (timeIntervalAfterAction <= requiredTimeInterval)
        {
            (*counterOfSuitableActions)++;
        }
    }
    return true;
}

bool processUserActivityData(int requiredTimeInterval, int* counterOfSuitableActions, int indexOfUser)
{
    int numberOfUserActions = 0;

    bool isCorrectInput = true;
    printf("Enter the number actions of user %d:\n", indexOfUser);
    isCorrectInput = scanf("%d", &numberOfUserActions) != 0;
    if (!isCorrectInput || numberOfUserActions < 0)
    {
        return false;
    }

    if (numberOfUserActions != 0)
    {
        printf("Enter %d time intervals indicating how many minutes ago these actions happened:\n",
               numberOfUserActions);
    }

    isCorrectInput = getNumberOfSuitableActions(numberOfUserActions, requiredTimeInterval, counterOfSuitableActions);

    return isCorrectInput;
}

bool getNumberOfSuitableUsers(int numberOfUsers, int requiredNumberOfActions, int requiredTimeInterval,
                              int* numberOfSuitableUsers)
{
    int counterOfSuitableActions = 0;

    bool isCorrectInput = true;

    for (int i = 1; i <= numberOfUsers; i++)
    {
        isCorrectInput = processUserActivityData(requiredTimeInterval, &counterOfSuitableActions, i);
        if (!isCorrectInput)
        {
            printf("Incorrect input!");
            return false;
        }

        if (counterOfSuitableActions == requiredNumberOfActions)
        {
            (*numberOfSuitableUsers)++;
        }
        counterOfSuitableActions = 0;
    }

    return numberOfSuitableUsers;
}

int main()
{
    int numberOfUsers = 0;
    int requiredNumberOfActions = 0;
    int requiredTimeInterval = 0;
    int numberOfSuitableUsers = 0;

    bool isCorrectInput = true;

    isCorrectInput = enterInitialData(&numberOfUsers, &requiredNumberOfActions, &requiredTimeInterval);
    if (!isCorrectInput)
    {
        return -1;
    }

    isCorrectInput = getNumberOfSuitableUsers(numberOfUsers, requiredNumberOfActions, requiredTimeInterval,
                                              &numberOfSuitableUsers);
    if (!isCorrectInput)
    {
        return -1;
    }

    printf("The number of users who completed exactly %d actions in the last %d minute(-s): %d",
           requiredNumberOfActions, requiredTimeInterval, numberOfSuitableUsers);

    return 0;
}