#include "Project.h"
#include "functions.h"


void findApt(Apartment* arr_Of_Apt, int sizeOfAptArr, char* command, int sizeOfLine,int howManyAptBought)//The main function of the "find apt" command
{
    int* resArr;
    int bucketArrSize = sizeOfAptArr + howManyAptBought;
    int sizeOfArrAction, numAction;
    Findcommands arrActions[MAX_NUM_ACTIONS];
    int i = 0, j, counter = 0;
    resArr = (int*)calloc(bucketArrSize+1, sizeof(int));
    Apartment* sortedArr;
    checkMemoryAllocation(resArr);

    insertAction(command, arrActions, &sizeOfArrAction, sizeOfLine);

    while (i < sizeOfArrAction)
    {
        numAction = whichAction(arrActions[i].action);
        checkActions(numAction, arr_Of_Apt, sizeOfAptArr, resArr, arrActions[i].data, &counter, bucketArrSize);
        i++;
    }
    if (numAction != 5 && numAction != 6 && numAction != 7 && numAction != -1)
    {
        for (j = 0;j < sizeOfAptArr;j++)
        {
            if (resArr[j] == counter)
                printApt(arr_Of_Apt[j]);

        }
    }
    free(resArr);
}
void checkActions(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter, int bucketArrSize) //The function gets the number of the action that returned from "whichAction" function and every case is doing another action.
{
    switch (numActions)
    {
    case 0://MinNumRooms
        filteredNumRooms(numActions, arr_Of_apt, sizeOfArr, bucketFilterArr, data, counter);
        break;
    case 1://MaxNumRooms
        filteredNumRooms(numActions, arr_Of_apt, sizeOfArr, bucketFilterArr, data, counter);
        break;
    case 2://MinPrice
        filteredPrice(numActions, arr_Of_apt, sizeOfArr, bucketFilterArr, data, counter);
        break;
    case 3://MaxPrice
        filteredPrice(numActions, arr_Of_apt, sizeOfArr, bucketFilterArr, data, counter);
        break;
    case 4://Date
        filteredDate(numActions, arr_Of_apt, sizeOfArr, bucketFilterArr, data, counter);
        break;
    case 5://Enter
        enterAndPrint(arr_Of_apt, sizeOfArr, data);
        break;
    case 6://sr
        priceSort(arr_Of_apt, sizeOfArr, bucketFilterArr, counter, numActions, bucketArrSize);
        break;
    case 7://s
        priceSort(arr_Of_apt, sizeOfArr, bucketFilterArr, counter, numActions, bucketArrSize);
        break;
    }
}
int whichAction(char* currAction)// The function gets a string and check which action is the string.
{
    if (strcmp(currAction, "MinNumRooms") == 0)
        return 0;
    else if (strcmp(currAction, "MaxNumRooms") == 0)
        return 1;
    else if (strcmp(currAction, "MinPrice") == 0)
        return 2;
    else if (strcmp(currAction, "MaxPrice") == 0)
        return 3;
    else if (strcmp(currAction, "Date") == 0)
        return 4;
    else if (strcmp(currAction, "Enter") == 0)
        return 5;
    else if (strcmp(currAction, "sr") == 0)
        return 6;
    else if (strcmp(currAction, "s") == 0)
        return 7;

}


void insertAction(char* command, Findcommands* arrActions, int* sizeOfArrActions, int size) //The function insert to a struct array the actions (every cell has the action and the data) for example [i] include an action "MinNumRooms" and a data "3"
{
    int i = 0, j = 0, k = 0, data = 0;
    while (command[i] != '\0' && i < size)
    {

        if (command[i] == ' ')
            i++;

        else if (isLetter(command[i]))
        {
            arrActions[k].action[j] = command[i];
            i++;
            j++;
        }
        else
        {
            data = data * 10 + (int)(command[i] - '0');
            arrActions[k].data = data;
            i++;
        }

        if (command[i] == '-' || command[i] == '\0')
        {
            i++;
            arrActions[k].action[j] = '\0';
            j = 0;
            k++;
            data = 0;
        }
    }
    *sizeOfArrActions = k;
}
bool isLetter(int data) // The function checks if the data is a letter or not
{
    return (data >= 'a' && data <= 'z' || data >= 'A' && data <= 'Z');
}
void enterAndPrint(Apartment* arr_Of_apt, int sizeOfArr, int data)
{
    int i;
    for (i = 0;i < sizeOfArr;i++)
    {
        if (arr_Of_apt[i].addingDay >= time(NULL) - (data * SECOND_IN_DAY))
        {
            printf("%d\n", arr_Of_apt[i].aptCode);
        }

    }
}

void filteredNumRooms(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter)
{
    int i = 0, j = 0;
    if (numActions == 0)//MinNumRooms
    {
        while (i < sizeOfArr)
        {
            if (arr_Of_apt[i].numOfRooms >= data)
            {
                bucketFilterArr[arr_Of_apt[i].aptCode-1] += 1;
                j++;
                i++;
            }
            else
                i++;
        }

    }
    else//MaxNumRooms
    {
        while (i < sizeOfArr)
        {
            if (arr_Of_apt[i].numOfRooms <= data)
            {
                bucketFilterArr[arr_Of_apt[i].aptCode - 1] += 1;
                j++;
                i++;
            }
            else
                i++;

        }
    }

    *counter += 1;

}
void filteredPrice(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter)
{
    int i = 0, j = 0;
    if (numActions == 0)//min Num Price
    {
        while (i < sizeOfArr)
        {
            if (arr_Of_apt[i].price >= data)
            {
                bucketFilterArr[arr_Of_apt[i].aptCode - 1] += 1;
                j++;
                i++;
            }
            else
                i++;
        }

    }
    else// Max Price
    {
        while (i < sizeOfArr)
        {
            if (arr_Of_apt[i].price <= data)
            {
                bucketFilterArr[arr_Of_apt[i].aptCode - 1] += 1;
                j++;
                i++;
            }
            else
                i++;

        }
    }

    *counter += 1;
}
void filteredDate(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter)// The function filer the apartments if the enter date is correct 
{
    int i = 0, j = 0;
    while (i < sizeOfArr)
    {
        if (isDate(data, arr_Of_apt[i].enterDate[0], arr_Of_apt[i].enterDate[1], arr_Of_apt[i].enterDate[2]))
        {
            bucketFilterArr[arr_Of_apt[i].aptCode-1] += 1;
            j++;
            i++;
        }
        else
            i++;
    }

    *counter += 1;
}
bool isDate(int data, int day, int month, int year)
{
    if (year > data % 100)
        return false;
    else if (year < data % 100)
        return true;
    else
    {
        data /= 10000;
        if (month > data % 100)
            return false;
        else if (month < data % 100)
            return true;
        else
        {
            data /= 100;
            if (day > data)
                return false;
        }
    }
    return true;
}

void priceSort(Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int* counter, int numAction,int bucketArrSize)//the function gets the bucketArr and the counter - how many actions we had on the command, and sort which apartment met all the criteria 
{
    int i, j = 0, printIndex, k,whichApt=0;
    Apartment* sortedArr = (Apartment*)malloc(sizeOfArr * sizeof(Apartment));
    checkMemoryAllocation(sortedArr);

    for (i = 0;i < bucketArrSize;i++)
    {
        if (bucketFilterArr[i] == *counter)
        {
            while (arr_Of_apt[whichApt].aptCode != i+1)
                whichApt++;
            sortedArr[j] = arr_Of_apt[whichApt];
            j++;
            whichApt = 0;
        }
    }
    if (j == 0)
        return;
    k = j + 1;
    sortedArr = (Apartment*)realloc(sortedArr, k * sizeof(Apartment));
    checkMemoryAllocation(sortedArr);
    mergesort(sortedArr, j, numAction);
    for (printIndex = 0; printIndex < j; printIndex++)
    {
        printApt(sortedArr[printIndex]);
    }
    free(sortedArr);
}
void mergesort(Apartment* sortedArr, int size, int numAction)
{
    Apartment* temp;
    int i, j;
    if (size <= 1)
        return;
    mergesort(sortedArr, size / 2, numAction);
    mergesort(sortedArr + (size / 2), size - (size / 2), numAction);
    temp = (Apartment*)malloc(size * sizeof(Apartment));
    checkMemoryAllocation(temp);
    if (numAction == 7)
        sortedMergeAsc(sortedArr, size / 2, sortedArr + size / 2, size - size / 2, temp);
    else
        sortedMergeDes(sortedArr, size / 2, sortedArr + size / 2, size - size / 2, temp);

    for (j = 0;j < size;j++)
    {
        sortedArr[j] = temp[j];
    }
    free(temp);
}
void sortedMergeAsc(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res)
{
    int read1 = 0, read2 = 0, write = 0;

    while (read1 < size1 && read2 < size2)
    {
        if (arr1[read1].price <= arr2[read2].price)
        {
            res[write] = arr1[read1];
            write++;
            read1++;
        }
        else
        {  //arr1[read1]>arr2[read2] copy info from arr2
            res[write] = arr2[read2];
            write++;
            read2++;
        }
    }
    while (read1 < size1)
    {//copy the end of arr1
        res[write] = arr1[read1];
        write++;
        read1++;
    }//end while
    while (read2 < size2)
    {//copy the end of arr2
        res[write] = arr2[read2];
        write++;
        read2++;
    }
}
void sortedMergeDes(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res)
{
    int read1 = 0, read2 = 0, write = 0;

    while (read1 < size1 && read2 < size2)
    {
        if (arr1[read1].price >= arr2[read2].price)
        {
            res[write] = arr1[read1];
            write++;
            read1++;
        }
        else
        {  //arr1[read1]>arr2[read2] copy info from arr2
            res[write] = arr2[read2];
            write++;
            read2++;
        }
    }
    while (read1 < size1)
    {//copy the end of arr1
        res[write] = arr1[read1];
        write++;
        read1++;
    }//end while
    while (read2 < size2)
    {//copy the end of arr2
        res[write] = arr2[read2];
        write++;
        read2++;
    }
}