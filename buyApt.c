#include "Project.h"
#include "functions.h"

void buyApt(Apartment* arr_Of_Apt, int sizeOfArray, char* whichApt)
{
    int numOfApt, i = 0;
    bool flag = true;
    Apartment temp;
    numOfApt = atoi(whichApt);

    while (flag && i < sizeOfArray)
    {
        if (arr_Of_Apt[i].aptCode != numOfApt)
            i++;
        else
            flag = false;
    }
    if (flag == true)
        printf("The apartment has already been bought \n");
    else
    {
        temp = arr_Of_Apt[sizeOfArray - 1];
        arr_Of_Apt[sizeOfArray - 1] = arr_Of_Apt[i];
        arr_Of_Apt[i] = temp;

        sizeOfArray -= 1;
        free(arr_Of_Apt[sizeOfArray].address);
        arr_Of_Apt = (Apartment*)realloc(arr_Of_Apt, (sizeOfArray) * sizeof(Apartment));
        checkMemoryAllocation(arr_Of_Apt);



    }
}