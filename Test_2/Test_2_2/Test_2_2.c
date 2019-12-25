#include <stdio.h>
#include "list.h"

int main()
{
    int numberOfElements = 0;
    int newValue = 0;
    printf("Enter number of elements in the list:\n");
    scanf("%d", &numberOfElements);
    printf("Enter %d values:\n", numberOfElements);

    List* list = createList();
    for (int i = 0; i < numberOfElements; i++)
    {
        scanf("%d", &newValue);
        insertToList(list, newValue, 0);
    }
    printf("The list before sorting:\n");
    printList(list);
    printf("\n");

    insertionSort(list);
    printf("Sorted list:\n");
    printList(list);

    deleteList(list);
    return 0;
}
