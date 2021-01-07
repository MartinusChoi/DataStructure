#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct NODE {
	int data;
	struct NODE* prev;
	struct NODE* next;
};
typedef struct NODE NODE;

NODE* createNode(int data);
void destroyNode(NODE* node);
void destroyAllNode(NODE** Head);
void appendNode(NODE** Head, NODE* node);
void insertAfter(NODE* current, NODE* node);
void insertBefore(NODE** Head, NODE* current, NODE* node);
void removeNode(NODE** Head, NODE* remove);
NODE* getNodeAt(NODE* Head, int rank);
void printAll(NODE* Head);

int main() {
	NODE* List = NULL;
	NODE* node = NULL;
	NODE* current = NULL;
	int data, rank;
	char flag;

	printf("[ Doubly Linked List ]\n");
	printf("======================\n");

	while (1) {
		printf("\n(function) : \n");
		printf("1. 'a' : append node\n");
		printf("2. 'r' : remove node\n");
		printf("3. 'A' : insert After\n");
		printf("4. 'B' : insert Before\n");
		printf("5. 'g' : get node data\n");
		printf("6. 's' : set node data\n");
		printf("7. 'p' : print all List data\n");
		printf("8. 'q' : Quit\n");
		printf("======================\n");
		printf("Select Function : ");
		scanf("%c", &flag);
		getchar();

		if (flag == 'a') {
			printf("input data : ");
			scanf("%d", &data);
			getchar();

			node = createNode(data);
			if (node == NULL) continue;

			appendNode(&List, node);

			printf("[output] Appended (data : %d)\n", data);
		}
		else if (flag == 'r') {
			printf("input rank : ");
			scanf("%d", &rank);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			removeNode(&List, current);

			printf("[output] Removed\n");
		}
		else if (flag == 'A') {
			printf("input rank, data : ");
			scanf("%d %d", &rank, &data);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			node = createNode(data);
			if (node == NULL) continue;

			insertAfter(current, node);

			printf("[output] inserted after %d (data : %d)\n", current->data, node->data);
		}
		else if (flag == 'B') {
			printf("input rank, data : ");
			scanf("%d %d", &rank, &data);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			node = createNode(data);
			if (node == NULL) continue;

			insertBefore(&List, current, node);

			printf("[output] inserted before %d (data : %d)\n", current->data, node->data);
		}
		else if (flag == 'g') {
			printf("input rank : ");
			scanf("%d", &rank);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			printf("[output] data at rank [%d] is %d", rank, current->data);
		}
		else if (flag == 's') {
			printf("input rank, data : ");
			scanf("%d %d", &rank, &data);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			current->data = data;

			printf("[output] set data at rank [%d] to %d", rank, current->data);
		}
		else if (flag == 'p') {
			printAll(List);
		}
		else if (flag == 'q')
			break;
	}

	destroyAllNode(&List);

	return 0;
}

NODE* createNode(int data)
{
	NODE* node = (NODE*)malloc(1 * sizeof(NODE));


	if (node == NULL) {
		printf("Create node failed\n");
		return NULL;
	}

	node->data = data;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void destroyNode(NODE* node)
{
	free(node);
}

void destroyAllNode(NODE** Head)
{
	if ((*Head) == NULL) return;

	if ((*Head)->next == NULL) {
		free((*Head));
		return;
	}

	NODE* current;
	NODE* tmp;

	current = (*Head)->next;
	while (current != NULL) {
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free((*Head));
}

void appendNode(NODE** Head, NODE* node)
{
	if ((*Head) == NULL) {
		(*Head) = node;
	}
	else {
		NODE* current = (*Head);

		while (current->next != NULL) {
			current = current->next;
		}

		current->next = node;
		node->prev = current;
	}
}

void insertAfter(NODE* current, NODE* node)
{
	node->prev = current;
	node->next = current->next;

	if (current->next != NULL) {
		(current->next)->prev = node;
	}
	current->next = node;
}

void insertBefore(NODE** Head, NODE* current, NODE* node)
{
	node->next = current;

	if ((*Head) == current) {
		node->prev = NULL;
		(*Head) = node;
	}
	else {
		node->prev = current->prev;
		(current->prev)->next = node;
	}

	current->prev = node;
}

void removeNode(NODE** Head, NODE* remove)
{
	if ((*Head) == remove) {
		(*Head) = remove->next;
		
		if ((*Head) != NULL)
			(*Head)->prev = NULL;
	}
	else {
		(remove->prev)->next = remove->next;

		if (remove->next != NULL) {
			(remove->next)->prev = remove->prev;
		}
	}

	remove->prev = NULL;
	remove->next = NULL;
}

NODE* getNodeAt(NODE* Head, int rank)
{
	NODE* current = Head;

	if ((current != NULL) && (--rank) >= 0) {
		current = current->next;
	}

	if (current == NULL)
		printf("No such node!\n");

	return current;
}

void printAll(NODE* Head)
{
	NODE* current = Head;

	printf("[output] ");

	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}

	printf("\n");
}