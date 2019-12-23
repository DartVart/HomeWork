#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

const int maxDistance = INT_MAX;

/* The array is filled with the values​contained in 'initialValue'. */
int** getTwoDimensionalArray(int numberOfRows, int numberOfColumns, int initialValue)
{
    int** array = (int**) calloc(numberOfRows, sizeof(int*));
    for (int row = 0; row < numberOfRows; row++)
    {
        array[row] = (int*) calloc(numberOfColumns, sizeof(int));
        for (int column = 0; column < numberOfColumns; column++)
        {
            array[row][column] = initialValue;
        }
    }
    return array;
}

void freeTwoDimensionalArray(int** array, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        free(array[i]);
    }
    free(array);
}

/* The function scans a number from 'minimumValue' to 'maximumValue' inclusive. */
bool scanNumberInRange(FILE* fileInput, int* number, int minimumValue, int maximumValue)
{
    return fscanf(fileInput, "%d", number) == 1 &&
           *number >= minimumValue && *number <= maximumValue;
}

bool scanDistanceAndCities(FILE* fileInput, int* numberOfFirstCity, int* numberOfSecondCity, int* distance,
                           int numberOfCities)
{
    return scanNumberInRange(fileInput, numberOfFirstCity, 1, numberOfCities) &&
           scanNumberInRange(fileInput, numberOfSecondCity, 1, numberOfCities) &&
           scanNumberInRange(fileInput, distance, 1, maxDistance - 1) &&
           *numberOfFirstCity != *numberOfSecondCity;
}

bool scanInitialData(FILE* fileInput, int* numberOfCities, int* numberOfRoads)
{
    // since the graph of roads is connected, then (numberOfRoads >= *numberOfCities - 1)
    return scanNumberInRange(fileInput, numberOfCities, 1, INT_MAX) &&
           scanNumberInRange(fileInput, numberOfRoads, *numberOfCities - 1, INT_MAX);
}

/* The function reads from the file the number of cities
 * (will be contained in the 'numberOfCities'), the number of roads and distance between cities.
 * If (fileInput == NULL) or the data in the file is incorrect, the function will return NULL. */
int** getArrayOfDistanceFromFile(FILE* fileInput, int* numberOfCities)
{
    if (fileInput == NULL)
    {
        return NULL;
    }
    int numberOfRoads = 0;
    bool isCorrectInput = scanInitialData(fileInput, numberOfCities, &numberOfRoads);
    if (!isCorrectInput)
    {
        return NULL;
    }

    int** distances = getTwoDimensionalArray(*numberOfCities, *numberOfCities, maxDistance);
    int numberOfFirstCity = 0;
    int numberOfSecondCity = 0;
    int distance = 0;
    for (int i = 0; i < numberOfRoads; i++)
    {
        isCorrectInput = scanDistanceAndCities(fileInput, &numberOfFirstCity, &numberOfSecondCity, &distance,
                                               *numberOfCities);
        if (!isCorrectInput)
        {
            freeTwoDimensionalArray(distances, *numberOfCities);
            return NULL;
        }
        distances[numberOfFirstCity - 1][numberOfSecondCity - 1] = distance;
        distances[numberOfSecondCity - 1][numberOfFirstCity - 1] = distance;
    }
    return distances;
}

/* The function reads from the file the number of capitals
 * (will be contained in the 'numberOfCapitals') and their numbers.
 * If (fileInput == NULL) or the data in the file is incorrect, the function will return NULL. */
int* getCapitals(FILE* fileInput, int* numberOfCapitals, int numberOfCities)
{
    if (fileInput == NULL)
    {
        return NULL;
    }
    bool isCorrectReading = scanNumberInRange(fileInput, numberOfCapitals, 1, numberOfCities);
    if (!isCorrectReading)
    {
        return NULL;
    }

    int* capitals = (int*) calloc(*numberOfCapitals, sizeof(int));
    int capitalNumber = 0;
    for (int i = 0; i < *numberOfCapitals; i++)
    {
        isCorrectReading = scanNumberInRange(fileInput, &capitalNumber, 1, numberOfCities);
        if (!isCorrectReading)
        {
            free(capitals);
            return NULL;
        }
        capitals[i] = capitalNumber - 1;
    }
    return capitals;
}

void separateCapitals(int** distances, const int* capitals, bool* isCityUsed, int numberOfCapitals)
{
    int firstCapitalNumber = 0;
    int secondCapitalNumber = 0;
    for (int i = 0; i < numberOfCapitals; i++)
    {
        firstCapitalNumber = capitals[i];
        isCityUsed[firstCapitalNumber] = true;
        for (int j = 0; j < numberOfCapitals; j++)
        {
            secondCapitalNumber = capitals[j];
            distances[firstCapitalNumber][secondCapitalNumber] = maxDistance;
        }
    }
}

/* If there is no accessible city, the function will return -1. */
int getNearestCity(int** distances, const bool* isCityUsed, int capitalNumber, int numberOfCities)
{
    int minimumDistance = maxDistance;
    int nearestCityNumber = -1;
    int currentDistance = 0;
    for (int i = 0; i < numberOfCities; i++)
    {
        currentDistance = distances[capitalNumber][i];
        if (!isCityUsed[i] && minimumDistance > currentDistance)
        {
            minimumDistance = currentDistance;
            nearestCityNumber = i;
        }
    }
    return nearestCityNumber;
}

void updateDistances(int** distances, int capitalNumber, int affiliatedCityNumber, const bool* isCityUsed,
                     int numberOfCities)
{
    int lengthFromAffiliatedCity = 0;
    int lengthFromCapital = 0;
    int lengthToAffiliatedCity = 0;
    int newLength = 0;
    for (int i = 0; i < numberOfCities; i++)
    {
        lengthFromAffiliatedCity = distances[affiliatedCityNumber][i];
        if (!isCityUsed[i] && lengthFromAffiliatedCity != maxDistance)
        {
            lengthFromCapital = distances[capitalNumber][i];
            lengthToAffiliatedCity = distances[capitalNumber][affiliatedCityNumber];
            newLength = lengthFromAffiliatedCity + lengthToAffiliatedCity;
            if (newLength < lengthFromCapital)
            {
                distances[capitalNumber][i] = newLength;
            }
        }
    }
}

/* The function sets the maximum distance from all capitals to the 'numberOfSeparatedCity'. */
void separateCityFromCapitals(int** distances, int numberOfSeparatedCity, const int* capitals, int numberOfCapitals)
{
    int currentNumberOfCapital = 0;
    for (int i = 0; i < numberOfCapitals; i++)
    {
        currentNumberOfCapital = capitals[i];
        distances[currentNumberOfCapital][numberOfSeparatedCity] = maxDistance;
    }
}

void assignCitiesToCapitals(int** distances, int* capitals, bool* isCityUsed, int numberOfCities,
                            int numberOfCapitals)
{
    int numberOfCountriesCreated = 0;
    int numberOfNearestCity = 0;
    int capitalNumber = 0;
    int distanceToNearestCity = 0;
    separateCapitals(distances, capitals, isCityUsed, numberOfCapitals);
    while (numberOfCountriesCreated != numberOfCapitals)
    {
        numberOfCountriesCreated = 0;
        for (int i = 0; i < numberOfCapitals; i++)
        {
            capitalNumber = capitals[i];
            numberOfNearestCity = getNearestCity(distances, isCityUsed, capitalNumber, numberOfCities);

            if (numberOfNearestCity != -1)
            {
                updateDistances(distances, capitalNumber, numberOfNearestCity, isCityUsed, numberOfCities);

                distanceToNearestCity = distances[capitalNumber][numberOfNearestCity];
                separateCityFromCapitals(distances, numberOfNearestCity, capitals, numberOfCapitals);
                distances[capitalNumber][numberOfNearestCity] = distanceToNearestCity;

                isCityUsed[numberOfNearestCity] = true;
            }
            else
            {
                numberOfCountriesCreated++;
            }
        }
    }
}

void displayAnswer(int** distances, const int* capitals, int numberOfCities, int numberOfCapitals)
{
    int capitalNumber = 0;
    int currentDistance = 0;
    bool hasCities = false;
    printf("Countries and their cities in the following format:\n"
           "<number of the capital (the country)> -- <numbers of cities that belong to the country>:\n");
    for (int i = 0; i < numberOfCapitals; i++)
    {
        capitalNumber = capitals[i];
        printf("%d -- ", capitalNumber + 1);
        for (int cityNumber = 0; cityNumber < numberOfCities; cityNumber++)
        {
            currentDistance = distances[capitalNumber][cityNumber];
            if (currentDistance != maxDistance)
            {
                printf("%d ", cityNumber + 1);
                hasCities = true;
            }
        }
        if (!hasCities)
        {
            printf("This country has only the capital!");
        }
        printf("\n");
        hasCities = false;
    }
}

int main()
{
    char* nameOfFile = "cities_and_capitals.txt";
    FILE* fileInput = fopen(nameOfFile, "r");
    if (fileInput == NULL)
    {
        fprintf(stderr, "File open error.\n");
        return -1;
    }

    int numberOfCities = 0;
    int** distances = getArrayOfDistanceFromFile(fileInput, &numberOfCities);
    if (distances == NULL)
    {
        fprintf(stderr, "Error initializing array of distances.\n");
        fclose(fileInput);
        return -1;
    }

    int numberOfCapitals = 0;
    int* capitals = getCapitals(fileInput, &numberOfCapitals, numberOfCities);
    if (capitals == NULL)
    {
        fprintf(stderr, "Error initializing capitals.\n");
        freeTwoDimensionalArray(distances, numberOfCities);
        fclose(fileInput);
        return -1;
    }

    bool* isCityUsed = (bool*) calloc(numberOfCities, sizeof(bool));

    assignCitiesToCapitals(distances, capitals, isCityUsed, numberOfCities, numberOfCapitals);
    displayAnswer(distances, capitals, numberOfCities, numberOfCapitals);

    freeTwoDimensionalArray(distances, numberOfCities);
    free(capitals);
    free(isCityUsed);
    fclose(fileInput);
    return 0;
}