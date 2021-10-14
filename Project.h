#define _CRT_SECURE_NO_WARNINGS
#ifndef _project_
#define _project_


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define END_OF_PROJECT -1
#define MAX_ADDRESS 100
#define MAX_PRICE 10
#define MAX_ACTION 12
#define MAX_NUM_ACTIONS 8
#define SECOND_IN_DAY 86400
#define N 7
#define ROOMSBIT 4
#define DAYBIT 5
#define MONTHBIT 4
#define YEARBIT 7
#define HOWMANYBITSLEFTDAY 1
#define HOWMANYBITSLEFTYEAR 4
#define BYTE 8



typedef struct  apartment
{
    short int aptCode;
    unsigned char* address;
    unsigned int price;
    unsigned short int numOfRooms;
    unsigned short int enterDate[3];
    time_t addingDay;

}Apartment;

typedef struct findcommends
{
    char action[MAX_ACTION];
    int data;
}Findcommands;


#endif
