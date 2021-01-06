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
void removeNode(NODE** Head, NODE* remove);
void insertAfter(NODE* current, NODE* node);
void insertBefore(NODE** Head, NODE* current, NODE* node);
NODE* getNodeAt(NODE* Head, int rank);
void printAll(NODE* Head);
void destroyAllNode(NODE** Head);

int main() {
	NODE* List = NULL;
	NODE* node = NULL;
	NODE* current = NULL;
	int data, rank;
	char flag;

	printf("[ Singly Linked List ]\n");
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
			if (node == NULL) return -1;

			appendNode(&List, node);

			printf("[output] appended (data : %d)\n", data);
		}
		else if (flag == 'r') {
			printf("input rank : ");
			scanf("%d", &rank);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			removeNode(&List, current);
			destroyNode(current);

			printf("[output] removed\n");
		}
		else if (flag == 'A') {
			printf("input data, rank : ");
			scanf("%d %d", &data, &rank);
			getchar();

			node = createNode(data);
			if (node == NULL) return -1;

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			insertAfter(current, node);

			printf("[output] inserted after [%d] (data : %d)\n", current->data, node->data);
		}
		else if (flag == 'B') {
			printf("input data, rank : ");
			scanf("%d %d", &data, &rank);
			getchar();

			node = createNode(data);
			if (node == NULL) return -1;

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			insertBefore(&List, current, node);

			printf("[output] inserted before [%d] (data : %d)\n", current->data, node->data);
		}
		else if (flag == 'g') {
			printf("input rank : ");
			scanf("%d", &rank);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			printf("[output] %d\n", current->data);
		}
		else if (flag == 's') {
			printf("intput data, rank : ");
			scanf("%d %d", &data, &rank);
			getchar();

			current = getNodeAt(List, rank);
			if (current == NULL) continue;

			current->data = data;

			printf("[output] set to %d (input data : %d)\n", current->data, data);
		}
		else if (flag == 'p') {
			printAll(List);
		}
		else if (flag == 'q') {
			break;
		}
	}

	destroyAllNode(&List);

	return 0;
}

NODE* createNode(int data)
{
	// input : (int data ; ���ο� node�� ������ ����)

	NODE* node = (NODE*)malloc(1 * sizeof(NODE)); // ���ο� node�� �ּҸ� �Ҵ�.

	if (node == NULL) { // �ּ��Ҵ� ���н�
		printf("Create Node failed!\n"); // ���������� �˸���
		return NULL; // �Լ� ���� (NULL ��ȯ)
	}

	node->data = data;
	node->next = NULL;

	return node; // ���� �Ҵ��� node�� �ּҸ� ��ȯ
}

void destroyNode(NODE* node)
{
	// input : (NODE* node ; ������ ����� �ּ�)
	free(node); // node�� �Ҵ��� �ּҸ� ��ȯ
}

void destroyAllNode(NODE** Head) 
{
	if ((*Head) == NULL) return; // �̹� List�� ����ִ� ��� �״�� �Լ��� ����.

	if ((*Head)->next == NULL) { // List�� node�� �ϳ����
		free((*Head)); // Head�� free���ش�.
		return;
	}

	NODE* current;
	NODE* tmp;

	current = (*Head)->next; // Head�� ���� ������ �����Ͽ�
	while (current != NULL) { // ��� ��尡 free �ɶ����� �ݺ����� ����
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free((*Head)); // ���������� Head�� ����Ű�� node�� free.
}

void appendNode(NODE** Head, NODE* node)
{
	// input : (NODE** Head ; List�� ù°����� �ּҸ� ������ �ִ� �����ͺ����� �ּ�)
	//		   (NODE* node ; append�� node�� �ּ�)

	if ((*Head) == NULL) { // List�� �ƹ��� ��嵵 ���ٸ�
		(*Head) = node; // Head�� node�� append
	}
	else { // �ϳ��� List�� ��尡 �����Ѵٸ�
		NODE* current = (*Head);

		while (current->next != NULL) { // ��尡 �������� ����Ű�� ���� ���� ������ �̵�
			current = current->next;
		}

		current->next = node; // �̵��� ����� �������� node�� append
	}
}

void removeNode(NODE** Head, NODE* remove)
{
	// input : (NODE** Head ; List�� ù°����� �ּҸ� ������ �ִ� ������ ������ �ּ�)
	//		   (NODE* remove ; ������� �ϴ� node�� �ּ�)

	if ((*Head) == remove) { // ���� ù��° ��尡 �������� �����
		(*Head) = remove->next; // List�� Head�� ���� Head�� ���� ��带 ����Ű���� ��.
	}
	else { // ù��°�� ���� ��尡 �ƴ϶��
		NODE* current = (*Head);

		while ((current != NULL) && (current->next != remove)) { // �Ѿ������ NULL�� �ƴϰ�, ���� ��ġ�� ���� node�� �ƴϸ�
			// ���� ���� ��尡 List �� ��� NULL�� ���� ���� ��� while���� ���;� error�� ���� ����.
			current = current->next; // ���� ���� �̵�.
		}

		if (current != NULL) {
			current->next = remove->next;
		}
	}
}

void insertAfter(NODE* current, NODE* node)
{
	node->next = current->next;
	current->next = node;
}

void insertBefore(NODE** Head, NODE* current, NODE* node)
{
	// input : (NODE** Head ; List�� ù��° ��带 ����Ű�� �ִ� ������ ������ �ּ�)
	//		   (NODE* current ; ������ ������ �Ǵ� node ��ġ)
	//		   (NODE* node ; ������ node)
	
	node->next = current; // ������ node�� next�� current ��带 ����Ű���� ��.
	
	if ((*Head) == current) { // current�� Head�� ������
		(*Head) = node; // Head�� node�� ����Ű���� ����.
	}
	else { // current�� Head�� �ƴϸ�
		NODE* curr = (*Head);

		while ((curr != NULL) && (curr->next != current)) { // �̵��� ��ġ�� NULL�� �ƴϰ� next�� current�� �ƴ϶��
			curr = curr->next; // ���� ���� �̵���.
		}

		if (curr != NULL) { // curr�� ���� ������ current�� ���� ����̹Ƿ�
			curr->next = node; // curr�� next�� node�� ����Ű���� �Ѵ�.
		}
	}
}

NODE* getNodeAt(NODE* Head, int rank)
{
	NODE* current = Head;

	while ((current != NULL) && (--rank) >= 0) {
		current = current->next;
	}

	if (current == NULL) {
		printf("No Such Node!\n");
		return NULL;
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
	}

	printf("\n");
}