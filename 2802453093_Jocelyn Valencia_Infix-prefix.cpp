#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxx 100

typedef struct{
	char infix[maxx];
	int front;
}stack;

void fungsiStack(stack *x){
	x->front = -1;
}

int kosong(stack *x){
	return x->front == -1;
}

int penuh(stack *x){
	return x->front == maxx - 1;
}

void push(stack *x, char infix){
	if(!penuh(x)){
		x->front = x->front +1;
		x->infix[x->front] = infix;
	}
}

char pop(stack *x){
	if(kosong(x)){
		return '\0';
	}
	char infix = x->infix[x->front];
	x->front = x->front-1;
	return infix;
}

char elemenTeratas(stack *x){
	if(!kosong(x)){
		return x->infix[x->front];
	}
	return '\0';
}

char prioritas(char oper){
	switch(oper){
		case '^' : return 3;
		case '*' : case '/' : return 2;
		case '+' : case '-' : return 1;
		default: return 0;
	}
}

char angka(char angka){
	return (angka >= '0' && angka <='9')||(angka >= 'A' && angka <='Z')||(angka >= 'a' && angka <= 'z');
}

void konversPrefix(char infix[], char prefix[]){
	stack x;
	fungsiStack(&x);
	int len = strlen(infix);
	int j = 0;
	char temp[maxx];
	
	//string disini direverse
	for(int i = 0; i < len; i++){
		temp[i] = infix[len-1-i];
	}
	temp[len] = '\0';
	
	//untuk tanda kurung
	for(int i = 0; i < len; i++){
		if(temp[i] == '('){
			temp[i] = ')';
		}
		else if(temp[i] == ')'){
			temp[i] = '(';
		}
	}
	
	for(int i = 0; i<len; i++){
		char c = temp[i];
		if(angka(c)){
			prefix[j++] = c;
		}
		else if(c == '('){
			push(&x, c);
		}
		else if(c == ')'){
			while(!kosong(&x) && elemenTeratas(&x) != '('){
				prefix[j++] = pop(&x);
			}
			pop(&x);
		}
		else{
            while (!kosong(&x) && prioritas(elemenTeratas(&x)) >= prioritas(c)) {
                prefix[j++] = pop(&x);
            }
            push(&x, c);
        }
	}
	
	while(!kosong(&x)){
		prefix[j++] = pop(&x);
	}
	prefix[j] = '\0';
	
	len = strlen(prefix);
	for(int i = 0; i < len/2; i++){
		char tempCha = prefix[i];
		prefix[i] = prefix[len-i-1];
		prefix[len-i-1] = tempCha;
	}
}

int main(){
	char infix[maxx], prefix[maxx];
	printf("Beri soal Infix!\n");
	scanf("%s",infix);
	getchar();
	
	konversPrefix(infix, prefix);
	printf("Hasil ke prefix adalah %s\n", prefix);
	return 0;
}
