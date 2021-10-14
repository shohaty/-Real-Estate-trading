#include "linkedList.h"
#include "Project.h"
#include "functions.h"

void makeEmptyList(LIST* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyList(LIST* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

ListNode* createNewListNode(char* command, ListNode* next, int sizeOfCommand)
{
	ListNode* res;
	res = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation(res);
	res->command = (char*)malloc(sizeOfCommand * sizeof(char));
	checkMemoryAllocation(res->command);
	strcpy(res->command, command);
	res->next = next;
	return res;
}

void insertDataToHeadList(LIST* lst, char* command, int sizeOfCommand)
{
	ListNode* newHead;
	newHead = createNewListNode(command, NULL, sizeOfCommand);
	insertNodeToHeadList(lst, newHead);
}

void insertNodeToHeadList(LIST* lst, ListNode* head)
{
	ListNode* curr = lst->head;
	if (lst->head == NULL)
	{
		head->next = lst->head;
		lst->head = head;
		lst->tail = lst->head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
		while (curr->next != NULL)
			curr = curr->next;
		lst->tail = curr;
	}

}
void insertDataToEndList(LIST* lst, char* command, int sizeOfCommand)
{
	ListNode* newTail;
	newTail = createNewListNode(command, NULL, sizeOfCommand);
	insertNodeToEndList(lst, newTail);
}
void insertNodeToEndList(LIST* lst, ListNode* head)
{
	if (lst->head == NULL)
	{
		lst->head = head;
		lst->tail = head;
	}
	else
	{
		lst->tail->next = head;
		lst->tail = head;
	}
	head->next = NULL;

}

void printList(LIST lst, int* index)
{
	ListNode* curr;
	curr = lst.head;
	while (curr != NULL)
	{
		printf("%d: %s\n", *index, curr->command);
		curr = curr->next;
		(*index)++;
	}

}
