#include "Project.h"
#include "functions.h"

void addApt(Apartment* apt, char* aptInfo, int AptCode) //The main function of the "add Apt" command
{
    int price, day, month, year, sizeOfAddress = 0, index = 1;
    short int numOfRooms;

    apt->aptCode = AptCode;
    apt->address = (char*)malloc(MAX_ADDRESS * sizeof(char));//
    checkMemoryAllocation(apt->address);
    apt->address = insertAddress(aptInfo, &sizeOfAddress);
    apt->address = (char*)realloc(apt->address, sizeOfAddress * sizeof(char));
    checkMemoryAllocation(apt->address);

    apt->price = insertInfoOfApt(aptInfo + sizeOfAddress, &index);
    apt->numOfRooms = insertInfoOfApt(aptInfo + sizeOfAddress, &index);
    apt->enterDate[0] = insertInfoOfApt(aptInfo + sizeOfAddress, &index);
    apt->enterDate[1] = insertInfoOfApt(aptInfo + sizeOfAddress, &index);
    apt->enterDate[2] = insertInfoOfApt(aptInfo + sizeOfAddress, &index);
    apt->addingDay = time(NULL);


}
char* insertAddress(char* aptInfo, int* sizeOfAddress) // The function gets information that the person enterd as an apartment input and extracts the address to the place in the APARTMENT stract.
{
    int localSize = 0, i = 0;
    char* address = (char*)malloc(sizeof(char));
    checkMemoryAllocation(address);

    while (aptInfo[i] != '"')
    {
        localSize = localSize * 2 + 1;
        address = (char*)realloc(address, localSize * sizeof(char));
        checkMemoryAllocation(address);
        address[i] = aptInfo[i];
        i++;
    }
    address[i] = '\0';
    *sizeOfAddress = i + 1;

    return address;
}

int insertInfoOfApt(char* info, int* index) //The function inserts the info (except the address) to the relevant place in the APARTMENT struct
{
    int i = 0, num, k = 0;
    char* tempStr = (char*)malloc(1000 * sizeof(char));
    checkMemoryAllocation(tempStr);
    while (info[i + (*index)] != ' ' && info[i + (*index)] != '\0')
    {
        tempStr[i] = info[i + (*index)];
        i++;
    }

    *index += i + 1;
    num = atoi(tempStr);
    free(tempStr);

    return num;
}

