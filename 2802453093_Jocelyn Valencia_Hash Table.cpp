#include<stdio.h>
#include<stdlib.h>

#define size_table 10
#define EMPTY -1
#define DELETE -2

typedef struct node{
	int key;
	int value;
	struct node* next;
}node;

typedef struct hash_table{
	int keys[size_table];
	int values[size_table];
	node* chain[size_table];
}hash_table;

//mid square mengambil digit tengah di angka kuadrat
int mid_square(int key){
	int square = key * key;
	return (square/10) % size_table;
}

// divion hashing mengambil data dari sisa pembagian
int division(int key){
	return key % size_table;
}

// folding hashing -> membagi data menjadi beberapa bagian, 
// lalu dijumlahkan untuk mendapatkan nilai hash
int folding(int key){
	int sum = 0;
	while(key > 0){
		sum += key % 100; // ini utk mengambil 2 digit yang di belakang
		key/= 100;
	}
	return sum % size_table;
}

// digit extraction hash adalah proses memilih beberapa digit dari kunci data
int digit_extraction(int key){
	return (key / 10) % size_table;
}

// rotation hash adalah metode dimana digit terakhir diletak di depan
int rotation(int key){
	int last = key%10;
	key/=10;
	key = last *1000 + key;
	return key%size_table;
}

//hash function
int hash(int key)
{
	return key%size_table;
}

int(*fungsi_hash)(int) = mid_square;

//hash function utk rehashing
int hash2(int key){
	return(7-(key%7)); 
}

//hash table initialization
void initialization(hash_table* ht)
{
	for(int i = 0; i< size_table; i++)
	{
		ht->keys[i] = EMPTY;
		ht->values[i] = 0;
		ht->chain[i] = NULL;
	}
}

//insert a key-value pair
void insert_linear(hash_table* ht, int key, int value)
{
	int index = hash(key);
	
	//linear probing to find an empty slot
	while(ht->keys[index] != EMPTY && ht->keys[index] != DELETE && ht->keys[index] != key){
		index = (index+1)%size_table;
	}
	//insert the key-value pair
	ht->keys[index] = key;
	ht->values[index] = value;
}

void insert_chain(hash_table* ht, int key, int value){
	int index = hash(key);
	node* new_node = (node*)malloc(sizeof(node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = ht->chain[index];
	ht->chain[index] = new_node;
}

void insert_rehashing(hash_table* ht, int key, int value){
	int index = hash(key);
	int step = hash2(key);
	int i = 0;
	
	while(ht->keys[(index+i*step) %size_table] != EMPTY &&
		 ht->keys[(index+i*step) %size_table] != DELETE &&
		 ht->keys[(index+i*step) %size_table] !=key ){
		 	i++;
		 	if(i >= size_table){
		 		printf("!!! PENUH !!!\n");
			 }
	}
	
	index = (index+i*step) % size_table;
	ht->keys[index] = key;
	ht->values[index] = value;
}

//search for a key in hash table
int search(hash_table* ht, int key, int collision_handling)
{
	int index = hash(key);
	int oriIndex = index;
	
	//linear probing to find the key
	
	if(collision_handling == 1){
		while(ht->keys[index]!=EMPTY){
			if(ht->keys[index] == key){
				return ht->values[index];
			}
			index = (index+1)%size_table;
			if(index == oriIndex)
			{
				break;//avoid infinite loop
			}
		}
	}
	//chaining to find the key
	else if(collision_handling == 2){
		node* curr = ht->chain[index];
		while(curr){
			if(curr->key == key){
			return curr->value;
			}
		}
		curr = curr->next;
	}
	else{
		int step = hash2(key);
		int i = 0;
		while(ht->keys[(index + i * step) % size_table] != EMPTY){
			if(ht->keys[(index+i*step) % size_table] == key){
				return ht->values[(index+i*step) % size_table];
			}
			i++;
			if(i >= size_table){
				break;
			}
		}
	}
	
	return -1; //key not found
}

//display ht
void display(hash_table* ht)
{
	for(int i = 0; i<size_table; i++){
			if(ht->keys[i]!=EMPTY && ht->keys[i]!=DELETE){
				printf("Slot %d: (%d, %d)\n",i, ht->keys[i], ht->values[i]);
			}
			else{
				printf("Slot %d: Empty\n", i);
			}
	}
}


int main(){
	hash_table ht;
	initialization(&ht);
	
	int menu_hash, collision_handling;
	
	printf("Silahkan pilih fungsi\n");
	printf("1. Mid square hashing\n2. Division hashing\n3. Folding hashing\n4. Digit extraction hashing\n5. Rotation hashing\n");
	printf("Pilihan anda adalah ");
	scanf("%d", &menu_hash);
	
	switch(menu_hash){
		case 1: fungsi_hash = mid_square;break;
		case 2: fungsi_hash = division;break;
		case 3: fungsi_hash = folding;break;
		case 4: fungsi_hash = digit_extraction;break;
		case 5: fungsi_hash = rotation;break;
		default:printf("Pilihan tidak adam otomatis ke nomor satu\n");
	}
	
	printf("\nSilahkan pilih collision handling:\n");
    printf("1. Linear probing\n2. Chaining\n3. Rehashing\n");
    printf("Pilihan anda adalah ");
    scanf("%d", &collision_handling);
    
    if (collision_handling == 1) {
        insert_linear(&ht, 1, 10);
        insert_linear(&ht, 2, 20);
        insert_linear(&ht, 11, 110);
        insert_linear(&ht, 12, 120);
    } else if (collision_handling == 2) {
        insert_chain(&ht, 1, 10);
        insert_chain(&ht, 2, 20);
        insert_chain(&ht, 11, 110);
        insert_chain(&ht, 12, 120);
    } else {
        insert_rehashing(&ht, 1, 10);
        insert_rehashing(&ht, 2, 20);
        insert_rehashing(&ht, 11, 110);
        insert_rehashing(&ht, 12, 120);
    }
    
    display(&ht);
    
    int search_key;
    printf("Key yang ingin anda cari? Silahkan ketik\n");
    scanf("%d", &search_key);
    
    int result = search(&ht, search_key, collision_handling);
    if (result != -1) {
        printf("Key %d ditemukan dengan nilai %d\n", search_key, result);
    } else {
        printf("Key %d TIDAK DITEMUKAN\n", search_key);
    }
    
    return 0;
}
