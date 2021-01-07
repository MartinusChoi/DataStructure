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

	printf("[ Circular Doubly Linked List ]\n");
	printf("===============================\n");

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
			removeNode(&List, current);
			destroyNode(current);
			
			printf("[output] Removed\n");
		}
		else if (flag == 'A') {
			printf("input rank, data : ");
			scanf("%d %d", &rank, &data);
			getchar();

			current = getNodeAt(List, rank);
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

			printf("[output] data at rank [%d] is %d\n", rank, current->data);
		}
		else if (flag == 's') {
			printf("input rank, data : ");
			scanf("%d %d", &rank, &data);
			getchar();

			current = getNodeAt(List, rank);
			
			current->data = data;

			printf("[output] set data at rank [%d] to %d\n", rank, current->data);
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
		printf("create node failed!\n");
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

	if ((*Head)->next == (*Head)) {
		free((*Head));
		return;
	}

	NODE* current;
	NODE* tmp;

	current = (*Head)->next;
	while (current != (*Head)) {
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free((*Head));
}

void appendNode(NODE** Head, NODE* node)
{
	// List�� ���� �ƹ��͵� ������
	if ((*Head) == NULL) {
		// node�� Head ���� �����ϰ�
		(*Head) = node;

		// node�� prev�� next�� ��� �ڱ� �ڽ����� ����
		node->next = (*Head);
		node->prev = (*Head);
	}
	// List�� ������� �ʴٸ�
	else {
		// Tail�� ã�Ƴ���
		NODE* Tail = (*Head)->prev;

		// Head�� prev�� Tail�� next�� ��� node�� ������.
		(*Head)->prev = node;
		Tail->next = node;

		// node�� Head�� Tail ���̿� ��ġ�ϵ��� ������.
		node->prev = Tail;
		node->next = (*Head);
	}
}

void insertAfter(NODE* current, NODE* node)
{
	// ������ ����� next�� current�� ���� ��带 ����Ű���� �ϰ�
	// node�� ���� ��尡 current�̵��� ��.
	node->next = current->next;
	node->prev = current;

	// current�� ���� ����� prev�� node�� ����Ű���� �ϰ�
	// current�� next�� node�� ����Ű���� ��.
	(current->next)->prev = node;
	current->next = node;
}

void insertBefore(NODE** Head, NODE* current, NODE* node)
{
	// ������ ����� next�� current�̵��� �ϰ�
	// prev�� current�� ���� ����̵��� ������.
	node->next = current;
	node->prev = current->prev;

	// current�� ���� ����� next�� ������ ����̵��� �����ϰ�
	// current�� prev�� ������ ����̵��� ������.
	(current->prev)->next = node;
	current->prev = node;

	// �� ���� ������ Head �ϰ�� Head �տ� �����Ͽ����Ƿ�
	// Head�� node�� ������.
	if ((*Head) == current)
		(*Head) = node;
}

void removeNode(NODE** Head, NODE* remove)
{
	// Head ��带 ������ �Ѵٸ�
	if ((*Head) == remove) {
		// Head�� �ϳ� ���� ��带 ����Ű�� ��.
		(*Head) = remove->next;
	}

	// ���� ����� �յ� ��尡 ���θ� ����Ű�� ��.
	(remove->prev)->next = remove->next;
	(remove->next)->prev = remove->prev;

	// ���� ����� ������ ������ �ʱ�ȭ ��.
	remove->next = NULL;
	remove->prev = NULL;
}

NODE* getNodeAt(NODE* Head, int rank)
{
	NODE* current = Head;

	while ((current != NULL) && (--rank) >= 0) {
		current = current->next;
	}

	return current;
}

void printAll(NODE* Head)
{
	NODE* current = Head;
	
	printf("[output] ");

	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;

		if (current == Head)
			break;
	}

	printf("\n");
}