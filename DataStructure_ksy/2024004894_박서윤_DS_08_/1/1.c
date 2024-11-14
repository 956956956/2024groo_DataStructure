#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(first)(! (first))

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

// 함수 선언
void insert(listPointer* first, listPointer x, int data);
void delete(listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);

int main()
{
	FILE* f;
	listPointer search;
	int data[12];

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "cannot open the file\n");
		exit(EXIT_FAILURE);
	}

	fscanf_s(f, "%d %d %d %d %d %d\n", data, data + 1, data + 2, data + 3, data + 4, data + 5);
	fscanf_s(f, "%d %d %d %d %d %d\n", data + 6, data + 7, data + 8, data + 9, data + 10, data + 11);

	fclose(f);

	// 첫 번째 노드를 동적 할당하고 초기화
	first = malloc(sizeof(*first));
	first->data = data[0];
	first->link = NULL;

	search = first;  // 리스트 탐색을 위해 search 포인터를 초기화

	// 나머지 데이터를 리스트에 삽입
	for (int i = 1; i < 12; i++) {

		if (first->data > data[i]) {
			insert(&first, NULL, data[i]);  // 첫 번째 노드보다 작은 경우 앞에 삽입
		}
		else {
			while (1) {
				if (search->link == NULL || search->link->data > data[i]) {
					insert(&first, search, data[i]);  // 올바른 위치에 삽입
					break;
				}
				search = search->link;  // 다음 노드로 이동
			}
			search = first;  // 탐색 포인터를 다시 첫 번째 노드로 초기화
		}
	}

	printList(first);


	while (1) {
		search = first;
		if (search->data % 2)
			delete(&first, NULL, search);
		else {
			while (search->link != NULL) {
				if (search->link->data % 2)  // 다음 노드가 홀수인 경우
					delete(&first, search, search->link);  // 해당 노드를 삭제
				else
					search = search->link;  // 다음 노드로 이동
			}
		}
		if (search->link == NULL)
			break;
	}

	printf("\nAfter deleting nodes with odd value\n");

	printList(first);

	return 0;
}


void insert(listPointer* first, listPointer x, int data)
{
	listPointer temp;
	temp = malloc(sizeof(*temp));  // 새로운 노드를 동적 할당
	temp->data = data;
	if (*first == NULL) {  // 리스트가 비어있는 경우
		temp->link = NULL;
		*first = temp;  // 첫 번째 노드로 설정
	}
	else {
		if (x == NULL)  // 첫 번째 노드 앞에 삽입하는 경우
		{
			temp->link = *first;
			*first = temp;  // 새로운 노드를 첫 번째 노드로 설정
		}
		else {  // 중간이나 끝에 삽입하는 경우
			temp->link = x->link;
			x->link = temp;
		}
	}
}


void delete(listPointer* first, listPointer trail, listPointer x)
{
	if (trail)  // 중간 또는 끝에서 삭제하는 경우
		trail->link = x->link;  // 이전 노드가 삭제된 노드의 다음 노드를 가리킴
	else  // 첫 번째 노드를 삭제하는 경우
		*first = (*first)->link;  // 첫 번째 노드를 삭제
	free(x);  // 메모리 해제
}

void printList(listPointer first)
{
	printf("The ordered list contains:\n");
	for (; first; first = first->link)  // 리스트를 순회하며 각 노드 출력
		printf("(%p, %4d, %2p)\n", first, first->data, first->link);  // 노드의 주소, 데이터, 다음 노드의 주소 출력
	printf("\n");
}
