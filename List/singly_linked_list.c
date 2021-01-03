#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct NODE {
	int data;
	struct NODE* next;
};
typedef struct NODE NODE;

NODE* createNode(int data);
void destroyNode(NODE* node);
void appendNode(NODE** Head, NODE* node);
NODE* getNodeAt(NODE* Head, int location);
void removeNode(NODE** Head, NODE* remove);
int countNode(NODE* Head);
void print(NODE* Head);

int main() {
	NODE* List = NULL;
	NODE* node = NULL;
	NODE* tmp;
	int data, rank;
	char flag;

	printf("[ Singly Linked List ]\n");
	printf("======================\n");

	while (1) {
		printf("(fuction) : \n");
		printf("'a' : Append Node\n");
		printf("'r' : Remove Node\n");
		printf("'g' : Get node data\n");
		printf("'s' : Set node data\n");
		printf("'c' : Count node numbers\n");
		printf("'p' : Print All List\n");
		printf("'q' : Quit\n");
		printf("======================\n");
		printf("Select Function : ");
		scanf("%c", &flag);
		getchar();

		if (flag == 'a') {
			printf("[Input data] ");
			scanf("%d", &data);
			getchar();

			node = createNode(data);
			appendNode(&List, node);
			printf("\n");
		}
		else if (flag == 'r') {
			printf("[Input rank] ");
			scanf("%d", &rank);
			getchar();

			node = getNodeAt(List, rank);
			removeNode(&List, node);
			destroyNode(node);
			printf("\n");
		}
		else if (flag == 'g') {
			printf("[Input rank] ");
			scanf("%d", &rank);
			getchar();

			node = getNodeAt(List, rank);
			printf("[output] %d\n\n", node->data);
		}
		else if (flag == 's') {
			printf("[input data, rank] ");
			scanf("%d,%d", &data, &rank);
			getchar();

			node = getNodeAt(List, rank);
			node->data = data;
			printf("[output] set data to %d\n\n", data);
		}
		else if (flag == 'c') {
			data = countNode(List);

			printf("[output] %d\n\n", data);
		}
		else if (flag == 'p') {
			print(List);
		}
		else if (flag == 'q')
			break;
	}

	if (List != NULL) {
		node = List->next;
		while (node != NULL) {
			tmp = node->next;
			destroyNode(node);
			node = tmp;
		}
		destroyNode(List);
	}

	return 0;
}

//// 노드 생성/소멸 ////

NODE* createNode(int data)
{
	NODE* node = (NODE*)malloc(1 * sizeof(NODE));

	node->data = data;
	node->next = NULL;

	return node;
}

void destroyNode(NODE* node)
{
	free(node);
}

//// 노드 추가 ////

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
	}
}

//// 노드 탐색 ////

NODE* getNodeAt(NODE* Head, int location)
{
	NODE* current = Head;

	while (current != NULL && (--location) >= 1) {
		current = current->next;
	}

	return current;
}

//// 노드 제거 ////

void removeNode(NODE** Head, NODE* remove)
{
	if ((*Head) == remove) {
		(*Head) = remove->next;
	}
	else {
		NODE* current = (*Head);

		while (current != NULL && current->next != remove) {
			current = current->next;
		}

		if (current != NULL) {
			current->next = remove->next;
		}
	}
}


//// 노드 개수 세기 ////

int countNode(NODE* Head)
{
	NODE* current = Head;
	int count = 0;

	while (current != NULL) {
		current = current->next;
		count++;
	}

	return count;
}

//// Print ////

void print(NODE* Head)
{
	NODE* current = Head;

	printf("[output] ");

	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}

	printf("\n\n");
}