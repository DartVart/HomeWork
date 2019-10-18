#include <stdio.h>

int main()
{
    int numberOfUsers = 0;
    int requiredNumberOfActions = 0;
    int requiredTimeInterval = 0;
    int numberOfSuitableUsers = 0;
    int numberOfUserActions = 0;
    int timeIntervalAfterAction = 0;
    int counterOfSuitableActions = 0;

    printf("Enter the number of users: ");
    scanf("%d", &numberOfUsers);
    printf("Enter the required number of actions: ");
    scanf("%d", &requiredNumberOfActions);
    printf("Enter the required time period:");
    scanf("%d", &requiredTimeInterval);


    for (int i = 1; i <= numberOfUsers; i++)
    {
        printf("Enter the number actions of user %d:", i);
        scanf("%d", &numberOfUserActions);

        printf("Enter %d time intervals indicating how many minutes ago these actions happened: ", numberOfUserActions);
        for (int j = 0; j < numberOfUserActions; j++)
        {
            scanf("%d", &timeIntervalAfterAction);
            if (timeIntervalAfterAction <= requiredTimeInterval)
            {
                counterOfSuitableActions++;
            }
        }

        if (counterOfSuitableActions == requiredNumberOfActions)
        {
            numberOfSuitableUsers++;
        }
        counterOfSuitableActions = 0;

    }

    printf("The number of users who completed exactly %d actions in the last %d minute(-s): %d",
            requiredNumberOfActions, requiredTimeInterval, numberOfSuitableUsers);

    return 0;
}