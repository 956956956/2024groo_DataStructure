#include <stdio.h>
#include <stdlib.h>
#include <string.h>;

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;
nodePointer header = NULL;

void dinsert(nodePointer node, nodePointer newnode);
void ddelete(nodePointer node, nodePointer deleted);
void dprintforward();
void dprintbackward();

int main()
{
	FILE* f;
	char* tok;
	char item[50];
	char* next_item;
	char* delimiter = " \n";
	nodePointer new, search, next;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "cannot open the file\n");
		exit(EXIT_FAILURE);
	}

	header = malloc(sizeof(*header));
	header->llink = header;
	header->rlink = header;
	header->data = NULL;

	while (!feof(f)) {
		fgets(item, 50, f);
		new = malloc(sizeof(*new));
		tok = strtok_s(item, delimiter, &next_item);

		while (tok != NULL) {
			new->data = atoi(tok);
			dinsert(header->llink, new);
			new = malloc(sizeof(*new));
			tok = strtok_s(NULL, delimiter, &next_item);
		}
	}

	printf("After creating a doubly linked circular list with a head node :\n");
	printf("forward\n");
	dprintforward();
	printf("backward\n");
	dprintbackward();

	search = header->rlink;
	while (search != header) {
		search = search->rlink;
		if (search->llink->data <= 50) ddelete(header, search->llink);
	}

	printf("After deleting numbers less than and equal to 50 :\n");
	printf("forward\n");
	dprintforward();
	printf("backward\n");
	dprintbackward();

	return 0;
}

void dinsert(nodePointer node, nodePointer newnode)
{
	newnode->llink = node;
	newnode->rlink = node->rlink;
	node->rlink->llink = newnode;
	node->rlink = newnode;
}

void ddelete(nodePointer node, nodePointer deleted)
{
	if (node == deleted)
		printf("Deletion of header node not permitted.\n");
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}

void dprintforward()
{
	nodePointer search = header->rlink;
	int i = 1;

	for (; search != header; search = search->rlink) {
		printf("(%p %4d %p)", search->llink, search->data, search->rlink);
		if (!(i % 4)) puts(""); else printf("    ");
		i++;
	}
	puts(""); puts("");
}

void dprintbackward()
{
	nodePointer search = header->llink;
	int i = 1;

	for (; search != header; search = search->llink) {
		printf("(%p %4d %p)", search->llink, search->data, search->rlink);
		if (!(i % 4)) puts(""); else printf("    ");
		i++;
	}
	puts(""); puts("");
}