#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode{
	int x;
	char nama[21];
	struct tnode *next;
	struct tnode *prev;
}tnode;

tnode *head = NULL;
tnode *tail = NULL;

tnode *node(int value, const char *name){
	tnode *save = (tnode*) malloc(sizeof(tnode));
	save->x = value;
	strcpy(save->nama, name);
	save->next = NULL;
	save->prev = NULL;
	return save;
}

void push_front(int value, const char *name){
	if(head == NULL){
		head = tail = node(value, name);
	} else {
		tnode *curr = node(value, name);
		curr->next = head;
		head->prev = curr;
		head = curr;
	}
}

void push_back(int value, const char *name){
	if(head == NULL){
		head = tail = node(value, name);
	} else {
		tnode *curr = node(value, name);
		curr->prev = tail;
		tail->next = curr;
		tail = curr;
	}
}

void push_mid(int value, const char *name){
	if(head == NULL){
		head = tail = node(value, name);
		return;
	}

	if(head->x > value){
		push_front(value, name);
		return;
	}

	if(tail->x <= value){
		push_back(value, name);
		return;
	}

	tnode *curr = node(value, name);
	tnode *start = head;

	while(start->next != NULL && start->next->x < value){
		start = start->next;
	}

	curr->next = start->next;
	curr->prev = start;

	if(start->next != NULL){
		start->next->prev = curr;
	}

	start->next = curr;
}

void delete_front(){
	if(head == NULL){
		printf("There is no data\n");
	} else {
		if(head == tail){
			free(head);
			head = tail = NULL;
		} 
		else {
			tnode *curr = head->next;
			curr->prev = NULL;
			free(head);
			head = curr;
		}
	}
}

void delete_back(){
	if(head == NULL){
		printf("There is no data\n");
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		tnode *curr = tail->prev;
		curr->next = NULL;
		free(tail);
		tail = curr;
	}
}

void delete_mid(int value){
	if(head == NULL){
		printf("There is no data\n");
	} 
	else if(head->x == value){
		delete_front();
	}
	else if(tail->x == value){
		delete_back();
	}
	else{
		tnode *start = head;
		while(start != NULL && start->x != value){
			start = start->next;
		}
		if(start == NULL){
			printf("There is no data\n");
		}
		
		tnode *a = start->prev;
		tnode *b = start->next;
		free(start);
		a->next = b;
		b->prev = a;
	}
}


void printList(){
	if(head == NULL){
		printf("List kosong\n");
		return;
	}

	tnode *curr = head;
	while(curr != NULL){
		printf("%d %s\n", curr->x, curr->nama);
		curr = curr->next;
	}
}

int main(){
	printf("Linked list\n");
	printf("____________________________________________\n");
	push_front(2, "Alice");
	push_front(1, "Budi");
	push_back(3, "Chacha");
	push_mid(6, "Diva");
	delete_front();
	printList();
}

