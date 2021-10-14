#include "Project.h"
#include "functions.h"

void deleteAptByTime(Apartment* arr_Of_Apt, int* sizeOfArray, char* command)
{
    int i = 0, data;
    data = atoi(command);
    while (arr_Of_Apt[i].addingDay < time(NULL) - (data * SECOND_IN_DAY))
    {
        i++;
    }
    *sizeOfArray -= i;
    arr_Of_Apt = (Apartment*)realloc(arr_Of_Apt, *sizeOfArray * sizeof(Apartment));
    checkMemoryAllocation(arr_Of_Apt);

}