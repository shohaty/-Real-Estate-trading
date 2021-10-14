#ifndef _functions_
#define _functions_

#include "Project.h"
#include "linkedList.h"


void addApt(Apartment* apt, char* aptInfo, int AptCode);
void checkMemoryAllocation(void* ptr);
char* insertAddress(char* aptInfo, int* sizeOfAddress);
int readCommand(char* line, int sizeLine, int* sizeCommand);
char* input(int* size);
int insertInfoOfApt(char* info, int* index);
void findApt(Apartment* arr_Of_Apt, int sizeOfArr, char* command, int sizeOfLine, int howManyAptBought);
void insertAction(char* command, Findcommands* arrActions, int* sizeOfArrActions, int size);
bool isLetter(int data);
int whichAction(char* currAction);
void checkActions(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter,int bucketArrSize);
void filteredNumRooms(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter);
void filteredPrice(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter);
void filteredDate(int numActions, Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int data, int* counter);
bool isDate(int data, int day, int month, int year);
void buyApt(Apartment* arr_Of_Apt, int sizeOfArray, char* whichApt);
void enterAndPrint(Apartment* arr_Of_apt, int sizeOfArr, int data);
void deleteAptByTime(Apartment* arr_Of_Apt, int* sizeOfArray, char* commend);
void priceSort(Apartment* arr_Of_apt, int sizeOfArr, int* bucketFilterArr, int counter, int numAction,int bucketArrSize);
void mergesort(Apartment* sortedArr, int size, int numAction);
void sortedMergeAsc(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res);
void sortedMergeDes(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res);
void Historyinsert(char* command, char* short_term_history[N], int sizeOfLine, LIST* oldHistoryList, int* arrOfSizesFromText);
void printApt(Apartment apt);
void PrintShortHistory(char* short_term_history[N], int howManyCommands, int printIndex);
int PrintHistory(LIST oldHistoryList);
char* applyLastCommand(char* short_term_history[N], int* sizeOfLine, int countHistory);
int readHistoryCommand(char* command);
void applyExactCommand(LIST oldHistoryList, char* short_term_history, int* sizeOfLine, int countHistory, int whichHistoryCommandNumber, char** command);
void replaceStringFromCommand(char** command, int* sizeOfLine, char* str1, char* str2);
char* disassembleCommand(char* command, int* sizeStr);
char* replaceString(char* command, int sizeCommand, int* sizeOfLine, char* str1, char* str2);
int whichHistoryCommandNumberTranslate(char* command);
void addToBinFile(int numOfApt, Apartment* apartments,int howManyAptBought);
void checkFileAllocation(FILE* file_ptr);
void addToTextFile(LIST oldHistoryList, char* short_term_history[N], int countHistory, FILE* file_ptr);
char* findCommandFromTextFile(FILE* file_ptr, int* sizeOfLine, int* howManyCommands);
int HistoryinsertFromTextFile(char* command, char* short_term_history[N], int sizeOfLine, LIST* oldHistoryList);
Apartment* readAptFromBinFile(FILE* file_BinPtr, int* numOfApt, int* howManyAptBought);
#endif