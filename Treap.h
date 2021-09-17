#pragma once

struct Node
{
	char* key;
	unsigned int IP;
	int priority;
	struct Node* L;
	struct Node* R;


};

struct Node* InitTreap(char* key, unsigned int IP);
struct Node* CreateNode(char* key, unsigned int IP);
struct Node* Merge(struct Node* A, struct Node* B);
void Split(struct Node* TreapRoot, char* key, struct Node** A, struct Node** B);
void Insert(struct Node** TreapRoot, char* key, unsigned int IP);
unsigned int Find(struct Node* TreapRoot, char* key);
void Erase(struct Node* TreapRoot);
