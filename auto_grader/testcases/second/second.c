#include<stdlib.h>
#include<stdio.h>
struct List{
	int data;
	int empty;
	struct List* next;
};

int search(struct List* table, int key,int callMethod){
	//callMethod =1 searching from main, callMethod = 0, searching from insert before adding
	int index = key % 10000;
	if(!table[index].empty && callMethod){
		printf("absent\n");
		return 0;
	}
	if(!table[index].empty){
		return 0;
	}
	else {
		struct List* ptr = &table[index];
		while(ptr != NULL){
			if(ptr->data == key){
				if (callMethod ==0){
					return 1;
				}
				printf("present\n");
				return 1;
			}
			ptr = ptr->next;
		}
	}
	if (callMethod ==1){
		printf("absent\n");
	}
	return 0;
}


void insert(struct List* table,int key){
	//search for value first to see if added
	if(search(table,key,0)){
		printf("duplicate\n");
		return;
	}
	//then insert
	 int index = key % 10000;
	if(!table[index].empty){
		table[index].data  = key;
		table[index].empty = 1;
		table[index].next = NULL;
		printf("inserted\n");
	}
	else{
		struct List* ptr = (struct List*)malloc(sizeof(struct List));
		ptr->data = key;
		ptr->next = table[index].next;
		ptr->empty = 1;
		table[index].next = ptr;
		printf("inserted\n");
		//free(ptr);
		//causes an error look into this
		//ask about what happens here to the value of table[index] after ptr is freed
		//allowed since we are not changing table[index] itself, it still refers to same memory if we wanted to do that we would need to send a pointer to table
	}


}


int main(int argc,char *argv[]){
	//hashTable, pointer for 10000 Linked Lists(array of Linked Lists)
	//empty is boolean to see if the Linked List is empty
	struct List* hashTable = (struct List*)malloc(sizeof(struct List) * 10000);
	char operator;
	int key;
	FILE* inputFile = fopen(argv[1],"r");
	
	while (fscanf(inputFile,"%c",&operator) != EOF){
		if (operator=='i'){
			//printf("insert\n");
		fscanf(inputFile,"\t%d\n",&key);

		insert(hashTable,key);

	}
	else if (operator=='s'){
		//printf("search\n");
		fscanf(inputFile,"\t%d\n",&key);
		search(hashTable,key,1);
	}
	

	}


	for(int i=0;i<10000;i++){
		if(hashTable[i].empty){
			struct List* ptr = (hashTable[i].next);
			struct List* ptrNext;
				while(ptr !=NULL && ptr->empty){
					ptrNext = ptr->next;
					free(ptr);
					ptr = ptrNext;
		}
	}
	}
	free(hashTable);

	//free(hashTable); //this only frees the head ptr of the list need to traverse list one by one and free

	fclose(inputFile);

}