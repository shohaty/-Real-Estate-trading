#ifndef _list_
#define _list_

#include <stdbool.h>

typedef struct listNode
{
	char* command;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}LIST;

void makeEmptyList(LIST* lst);
bool isEmptyList(LIST* lst);
ListNode* createNewListNode(char* command, ListNode* next, int sizeOfCommand);
void insertDataToHeadList(LIST* lst, char* command, int sizeOfCommand);
void insertNodeToHeadList(LIST* lst, ListNode* head);
void insertDataToEndList(LIST* lst, char* command, int sizeOfCommand);
void insertNodeToEndList(LIST* lst, ListNode* head);
void printList(LIST lst, int* index);

#endif
