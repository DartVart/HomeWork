#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initialSizeOfArray = 10;
int maxSizeOString = 1000;

typedef struct Member
{
    char* name;
    int loyalty;
} Member;

void swapInteger(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapCharPointer(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void swapMember(Member* first, Member* second)
{
    swapInteger(&first->loyalty, &second->loyalty);
    swapCharPointer(&first->name, &second->name);
}

void sortMembersByLoyalty(Member* members, int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        for (int j = 0; j < sizeOfArray - i - 1; j++)
        {
            if (members[j].loyalty < members[j + 1].loyalty)
            {
                swapMember(&members[j], &members[j + 1]);
            }
        }
    }
}

void sortMembersByName(Member* members, int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        for (int j = 0; j < sizeOfArray - i - 1; j++)
        {
            if (strcmp(members[j].name, members[j + 1].name) > 0)
            {
                swapMember(&members[j], &members[j + 1]);
            }
        }
    }
}

int main()
{
    char* nameOfFile = "members.txt";
    FILE* inputFile = fopen(nameOfFile, "r");
    if (inputFile == NULL)
    {
        printf("File open error.");
        return -1;
    }

    char* currentStringInFile = (char*) malloc(maxSizeOString * sizeof(char));
    Member* members = (Member*) malloc(initialSizeOfArray * sizeof(Member));
    int currentNumberOfMembers = 0;
    int currentArrayCapacity = initialSizeOfArray;

    while (!feof(inputFile))
    {
        if (currentNumberOfMembers == currentArrayCapacity)
        {
            currentArrayCapacity *= 2;
            members = (Member*) realloc(members, currentArrayCapacity * sizeof(Member));
        }

        fgets(currentStringInFile, maxSizeOString, inputFile);
        int indexOfLastCharacter = strlen(currentStringInFile) - 1;
        if (currentStringInFile[indexOfLastCharacter] == '\n')
        {
            currentStringInFile[indexOfLastCharacter] = '\0';
        }
        members[currentNumberOfMembers].name = (char*) malloc(maxSizeOString * sizeof(char));
        sscanf(currentStringInFile, "%s - %d", members[currentNumberOfMembers].name,
               &members[currentNumberOfMembers].loyalty);
        currentNumberOfMembers++;
    }

    printf("The sum of the following two numbers entered must not exceed %d (total number of members).\n",
           currentNumberOfMembers);

    int numberOfMostDangerousMembers = 0;
    printf("Enter the number of the most dangerous members:\n");
    scanf("%d", &numberOfMostDangerousMembers);

    int numberOfMembersToBeSent = 0;
    printf("Enter the number of members to be sent to Siberia:\n");
    scanf("%d", &numberOfMembersToBeSent);

    sortMembersByLoyalty(members, currentNumberOfMembers);

    if (numberOfMostDangerousMembers == 0)
    {
        printf("Nobody will be killed.\n");
    }
    else
    {
        int indexOfMemberToBeKilled = 0;
        printf("The following members will be shoot:\n");
        for (int i = 0; i < numberOfMostDangerousMembers; i++)
        {
            indexOfMemberToBeKilled = currentNumberOfMembers - i - 1;
            printf("%s\n", members[indexOfMemberToBeKilled].name);
        }
    }

    sortMembersByName(members, currentNumberOfMembers - numberOfMostDangerousMembers);

    if (numberOfMembersToBeSent == 0)
    {
        printf("No one will be sent to Siberia.\n");
    }
    else
    {
        printf("The following members will be sent to Siberia:\n");
        for (int i = 0; i < numberOfMembersToBeSent; i++)
        {
            printf("%s\n", members[i].name);
        }
    }

    if (numberOfMembersToBeSent + numberOfMostDangerousMembers == currentNumberOfMembers)
    {
        printf("There will be no unharmed members.\n");
    }
    else
    {
        printf("The following members will remain intact:\n");
        for (int i = numberOfMembersToBeSent; i < currentNumberOfMembers - numberOfMostDangerousMembers; i++)
        {
            printf("%s\n", members[i].name);
        }
    }

    for (int i = 0; i < currentNumberOfMembers; i++)
    {
        free(members[i].name);
    }
    free(members);
    free(currentStringInFile);
    fclose(inputFile);
    return 0;
}