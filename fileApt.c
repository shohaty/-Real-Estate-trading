#include "Project.h"
#include "functions.h"

void addToTextFile(LIST oldHistoryList, char* short_term_history[N], int countHistory, FILE* file_ptr)//the function writes the history commands to a text file
{
	ListNode* curr = oldHistoryList.head;
	int i, tempLen;
	file_ptr = fopen("ListCommandsHistory.txt", "w");
	checkFileAllocation(file_ptr);

	fprintf(file_ptr, "%d\n", countHistory);

	if (countHistory <= N)
	{
		for (i = 0;i < countHistory;i++)
		{
			tempLen = strlen(short_term_history[i]) + 1;
			fprintf(file_ptr, "%d\n", tempLen);
			fputs(short_term_history[i], file_ptr);
			fflush(file_ptr);
		}
	}
	else
	{
		for (i = 0;i < N;i++)
		{
			tempLen = strlen(short_term_history[i]) + 1;
			fprintf(file_ptr, "%d\n", tempLen);
			fputs(short_term_history[i], file_ptr);
			fprintf(file_ptr, "\n");
			fflush(file_ptr);
		}

		while (i < countHistory && curr != NULL)
		{
			tempLen = strlen(curr->command) + 1;
			fprintf(file_ptr, "%d\n", tempLen);
			fputs(curr->command, file_ptr);
			fprintf(file_ptr, "\n");
			curr = curr->next;
			fflush(file_ptr);
		}
	}
	fflush(file_ptr);

	fclose(file_ptr);

}

char* findCommandFromTextFile(FILE* file_ptr, int* sizeOfLine, int* howManyCommands)//The function reads a line from the text file that includes a size and the command
{
	char* command;
	static int counter = 0;
	int numOfCommands = 0;
	int lineSize = 0;

	if (counter == 0)
	{
		fscanf(file_ptr, "%d", &numOfCommands);
		*howManyCommands = numOfCommands;
	}


	fscanf(file_ptr, "%d\n", &lineSize);
	*sizeOfLine = lineSize;
	command = (char*)malloc(*sizeOfLine * sizeof(char));
	checkMemoryAllocation(command);

	fgets(command, *sizeOfLine, file_ptr);
	fscanf(file_ptr, "\n");

	counter++;
	return command;
}
int HistoryinsertFromTextFile(char* command, char* short_term_history[N], int sizeOfLine, LIST* oldHistoryList)//The function inserts the history back from the file to the array and the list
{
	ListNode* curr = oldHistoryList->head;
	static int counter = 0;
	
	if (counter < N)
	{
		short_term_history[counter] = (char*)malloc(sizeOfLine+5 * sizeof(char));
		checkMemoryAllocation(short_term_history[counter]);
		strcpy(short_term_history[counter], command);
		counter++;
	}
	else
	{
		insertDataToEndList(oldHistoryList, command, sizeOfLine);

	}

	return sizeOfLine;


}

void addToBinFile(int numOfApt, Apartment* apartments,int howManyAptBought)//The function adds the appartments array into the binary file
{
	FILE* file_ptr;
	unsigned short int lengthOfAddress;
	unsigned short int maskRooms = 0X0f;
	unsigned short int maskDay = 0X1f;
	unsigned short int maskMonth = 0X0f;
	unsigned short int maskYear = 0X7f;
	unsigned int tempSizeOfBits;
	unsigned char tempDay = 0, tempYear = 0;
	unsigned int i;
	unsigned char compressed1 = 0, compressed2 = 0, compressed3 = 0;


	file_ptr = fopen("AptBinFile.bin", "wb");
	checkFileAllocation(file_ptr);

	fwrite(&numOfApt, sizeof(int), 1, file_ptr);
	fwrite(&howManyAptBought, sizeof(int), 1, file_ptr);

	for (i = 0;i < numOfApt;i++)
	{
		fwrite(&(apartments[i].aptCode), sizeof(unsigned short int), 1, file_ptr);
		lengthOfAddress = strlen(apartments[i].address) + 1;
		fwrite(&lengthOfAddress, sizeof(unsigned short int), 1, file_ptr);
		fwrite(apartments[i].address, sizeof(unsigned char), lengthOfAddress, file_ptr);
		fwrite(&apartments[i].price, sizeof(unsigned int), 1, file_ptr);
		fwrite(&apartments[i].addingDay, sizeof(time_t), 1, file_ptr);
		compressed1 |= apartments[i].numOfRooms << (BYTE - ROOMSBIT);
		tempDay = apartments[i].enterDate[0] >> HOWMANYBITSLEFTDAY;
		compressed1 |= tempDay;
		tempDay = apartments[i].enterDate[0] << (BYTE - HOWMANYBITSLEFTDAY);
		compressed2 |= tempDay;
		compressed2 |= apartments[i].enterDate[1] << (BYTE - MONTHBIT - HOWMANYBITSLEFTDAY);
		tempYear = apartments[i].enterDate[2] >> HOWMANYBITSLEFTYEAR;
		compressed2 |= tempYear;
		tempYear = apartments[i].enterDate[2] << HOWMANYBITSLEFTYEAR;
		compressed3 |= tempYear;
		fwrite(&compressed1, sizeof(unsigned char), 1, file_ptr);
		fwrite(&compressed2, sizeof(unsigned char), 1, file_ptr);
		fwrite(&compressed3, sizeof(unsigned char), 1, file_ptr);
		fflush(file_ptr);
		compressed1 = 0;
		compressed2 = 0;
		compressed3 = 0;
		tempDay = 0;
		tempYear = 0;
	}
	fclose(file_ptr);
}

Apartment* readAptFromBinFile(FILE* file_BinPtr, int* numOfApt,int* howManyAptBought)//The function reads the apartments from the binary file
{
	Apartment* arr_Of_Apt;
	int tempNumOfApt, i,tempHowManyBought;
	unsigned short int lengthAddress;
	unsigned short int numOfRooms = 0;
	unsigned short int day = 0;
	unsigned short int month = 0;
	unsigned short int year = 0;
	unsigned char tempRead;
	unsigned char mask = 0X0F;


	fread(&tempNumOfApt, sizeof(int), 1, file_BinPtr);
	*numOfApt = tempNumOfApt;
	fread(&tempHowManyBought, sizeof(int), 1, file_BinPtr);
	*howManyAptBought = tempHowManyBought;

	arr_Of_Apt = (Apartment*)malloc(tempNumOfApt * sizeof(Apartment));
	checkMemoryAllocation(arr_Of_Apt);

	for (i = 0;i < tempNumOfApt;i++)
	{

		fread(&arr_Of_Apt[i].aptCode, sizeof(short int), 1, file_BinPtr);
		fread(&lengthAddress, sizeof(unsigned short int), 1, file_BinPtr);
		arr_Of_Apt[i].address = (char*)malloc(lengthAddress * sizeof(char));
		checkMemoryAllocation(arr_Of_Apt[i].address);
		fread(arr_Of_Apt[i].address, sizeof(unsigned char), lengthAddress, file_BinPtr);
		arr_Of_Apt[i].address[lengthAddress] = '\0';
		fread(&arr_Of_Apt[i].price, sizeof(unsigned int), 1, file_BinPtr);
		fread(&arr_Of_Apt[i].addingDay, sizeof(time_t), 1, file_BinPtr);
		fread(&tempRead, sizeof(unsigned char), 1, file_BinPtr);
		numOfRooms = (tempRead >> ROOMSBIT) & mask;
		arr_Of_Apt[i].numOfRooms = numOfRooms;
		day |= tempRead & mask;
		day <<= HOWMANYBITSLEFTDAY;
		fread(&tempRead, sizeof(unsigned char), 1, file_BinPtr);
		day |= tempRead >> BYTE - HOWMANYBITSLEFTDAY;
		arr_Of_Apt[i].enterDate[0] = day;
		month |= (tempRead >> BYTE - HOWMANYBITSLEFTDAY - MONTHBIT) & mask;
		arr_Of_Apt[i].enterDate[1] = month;
		year |= tempRead & (mask >> BYTE - YEARBIT);
		fread(&tempRead, sizeof(unsigned char), 1, file_BinPtr);
		year <<= HOWMANYBITSLEFTYEAR;
		year |= (tempRead >> HOWMANYBITSLEFTYEAR) & mask;
		arr_Of_Apt[i].enterDate[2] = year;
		day = 0;
		month = 0;
		year = 0;
		numOfRooms = 0;
	}

	return arr_Of_Apt;
}

void checkFileAllocation(FILE* file_ptr)
{
	if (file_ptr == NULL)
	{
		printf("Error opening file");
		exit(-1);
	}
}