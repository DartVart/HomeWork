#include <stdio.h>
#include "circularList.h"

CircularList* createCircleOfWarriors(int numberOfWarriors)
{
    CircularList* circleOfWarriors = createCircularList();
    for (int i = 1; i <= numberOfWarriors; i++)
    {
        addToCircularList(circleOfWarriors, i);
    }

    return circleOfWarriors;
}

int getNumberOfLastWarrior(CircularList* circleOfWarriors, int orderOfKilling)
{
    int numberOfWarriors = getCircularListSize(circleOfWarriors);

    while (numberOfWarriors > 1)
    {
        deleteElementOfCircularList(circleOfWarriors, orderOfKilling - 1, AFTER_LAST_DELETED);
        numberOfWarriors = getCircularListSize(circleOfWarriors);
    }

    return deleteElementOfCircularList(circleOfWarriors, 0, FIRST);
}

int main()
{
    int numberOfWarriors = 0;
    int orderOfKilling = 0;

    printf("Enter number of warriors: ");
    scanf("%d", &numberOfWarriors);

    printf("Enter the order in which warriors will kill themselves:");
    scanf("%d", &orderOfKilling);

    CircularList *circleOfWarriors = createCircleOfWarriors(numberOfWarriors);

    int survivingWarrior = getNumberOfLastWarrior(circleOfWarriors, orderOfKilling);
    printf("Warrior number %d will survive.", survivingWarrior);

    deleteCircularList(circleOfWarriors);
    return 0;
}
