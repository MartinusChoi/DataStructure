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
	// input : (int data ; 새로운 node에 저장할 정보)

	NODE* node = (NODE*)malloc(1 * sizeof(NODE)); // 새로운 node의 주소를 할당.

	if (node == NULL) { // 주소할당 실패시
		printf("Create Node failed!\n"); // 실패했음을 알리고
		return NULL; // 함수 종료 (NULL 반환)
	}

	node->data = data;
	node->next = NULL;

	return node; // 새로 할당한 node의 주소를 반환
}

void destroyNode(NODE* node)
{
	// input : (NODE* node ; 삭제할 노드의 주소)
	free(node); // node에 할당한 주소를 반환
}

void destroyAllNode(NODE** Head) 
{
	if ((*Head) == NULL) return; // 이미 List가 비어있는 경우 그대로 함수를 종료.

	if ((*Head)->next == NULL) { // List에 node가 하나라면
		free((*Head)); // Head만 free해준다.
		return;
	}

	NODE* current;
	NODE* tmp;

	current = (*Head)->next; // Head의 다음 노드부터 설정하여
	while (current != NULL) { // 모든 노드가 free 될때까지 반복문을 돌림
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free((*Head)); // 마지막으로 Head가 가리키는 node를 free.
}

void appendNode(NODE** Head, NODE* node)
{
	// input : (NODE** Head ; List의 첫째노드의 주소를 가지고 있는 포인터변수의 주소)
	//		   (NODE* node ; append할 node의 주소)

	if ((*Head) == NULL) { // List에 아무런 노드도 없다면
		(*Head) = node; // Head에 node를 append
	}
	else { // 하나라도 List에 노드가 존재한다면
		NODE* current = (*Head);

		while (current->next != NULL) { // 노드가 다음으로 가리키는 것이 없는 노드까지 이동
			current = current->next;
		}

		current->next = node; // 이동한 노드의 다음으로 node를 append
	}
}

void removeNode(NODE** Head, NODE* remove)
{
	// input : (NODE** Head ; List의 첫째노드의 주소를 가지고 있는 포인터 변수의 주소)
	//		   (NODE* remove ; 지우려고 하는 node의 주소)

	if ((*Head) == remove) { // 만약 첫번째 노드가 지워야할 노드라면
		(*Head) = remove->next; // List의 Head가 현재 Head의 다음 노드를 가리키도록 함.
	}
	else { // 첫번째가 지울 노드가 아니라면
		NODE* current = (*Head);

		while ((current != NULL) && (current->next != remove)) { // 넘어왔을때 NULL이 아니고, 다음 위치가 지울 node가 아니면
			// 만약 지울 노드가 List 상에 없어서 NULL을 먼저 만날 경우 while문을 나와야 error가 나지 않음.
			current = current->next; // 다음 노드로 이동.
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
	// input : (NODE** Head ; List의 첫번째 노드를 가리키고 있는 포인터 변수의 주소)
	//		   (NODE* current ; 삽입의 기준이 되는 node 위치)
	//		   (NODE* node ; 삽입할 node)
	
	node->next = current; // 삽입할 node의 next가 current 노드를 가리키도록 함.
	
	if ((*Head) == current) { // current가 Head와 같으면
		(*Head) = node; // Head가 node를 가리키도록 변경.
	}
	else { // current가 Head가 아니면
		NODE* curr = (*Head);

		while ((curr != NULL) && (curr->next != current)) { // 이동한 위치가 NULL이 아니고 next가 current가 아니라면
			curr = curr->next; // 다음 노드로 이동함.
		}

		if (curr != NULL) { // curr은 삽입 기준인 current의 직전 노드이므로
			curr->next = node; // curr의 next가 node를 가리키도록 한다.
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