#include "Treap.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Node* InitTreap(char* key, unsigned int IP)
{
	return CreateNode(key, IP);
	srand(time(NULL));
}

struct Node* CreateNode(char* key, unsigned int IP)
{
	struct Node* node = malloc(sizeof(struct Node));
	node->key = key;
	node->IP = IP;
	node->priority = rand();
	node->L = 0;
	node->R = 0;
	return node;
}

struct Node* Merge(struct Node* A, struct Node* B)// all keys of A should be less then all keys of B
{
	if (!A || !B)
	{
		return A ? A : B;
	}

	if (A->priority > B->priority)
	{
		A->R = Merge(A->R, B);
		return A;
	}
	else
	{
		B->L = Merge(A, B->L);
		return B;
	}
}

void Split(struct Node* TreapRoot, char* key, struct Node** A, struct Node** B)
{
	if (!TreapRoot)
	{
		*A = *B = 0;
		return;
	}

	if (strcmp(TreapRoot->key, key) < 0)
	{
		Split(TreapRoot->R, key, &(TreapRoot->R), B);
		*A = TreapRoot;
	}
	else
	{
		Split(TreapRoot->L, key, A, &(TreapRoot->L));
		*B = TreapRoot;
	}
}

void Insert(struct Node** TreapRoot, char* key, unsigned int IP)
{
	struct Node* Less, * Greater;
	Split(*TreapRoot, key, &Less, &Greater);
	Less = Merge(Less, CreateNode(key, IP));
	*TreapRoot = Merge(Less, Greater);
}

unsigned int Find(struct Node* TreapRoot, char* key)
{
	struct Node* currentNode = TreapRoot;
	while (strcmp(currentNode->key, key) != 0)
	{
		if (strcmp(currentNode->key, key) > 0)
		{
			if (currentNode->L)
				currentNode = currentNode->L;
			else
			{
				return 0;
			}
		}
		else
		{
			if (currentNode->R)
				currentNode = currentNode->R;
			else
			{
				return 0;
			}
		}
	}
	return currentNode->IP;
}

void Erase(struct Node* TreapRoot)
{
	if (!TreapRoot) return;
	Erase(TreapRoot->L);
	Erase(TreapRoot->R);
	free(TreapRoot->key);
	free(TreapRoot);
}


