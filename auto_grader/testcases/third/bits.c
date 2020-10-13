#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int compare(char* str1, char* str2 ){
	int i =0;
	while(str1[i] == str2[i]){
			if(str1[i] =='\0' || str2[i] == '\0'){
				break;
			}
			i++;
	}
	if(str1[i] =='\0' && str2[i] =='\0'){
		return 1;
	}
	else {
		return 0;
	}
}
unsigned int get(unsigned int* val, int n,int setMethod){
	unsigned temp = (*val &(1<<n)) >>n;
	if(setMethod){
		return temp;
	}
	printf("%d\n",temp);
	return temp;



}
void set(unsigned int* val, int n,int newval){
	//try newval as a integer, then as a pointer later
	if(newval == 0){
		//check to see what value is at that index;
		if(get(val,n,1) ==0){
			printf("%d\n",*val);
			return;
		}
		*val = (*val) ^ (1<<n);
	}
	else if(newval ==1){
	*val = (*val) | (newval<<n);
}
printf("%d\n",*val);

}

void complement(unsigned int* val, int n){
	*val = *val ^(1<<n);
	printf("%d\n",*val);
}
void scan(FILE* input_file){

	if(input_file ==NULL){
		//unable to open file
		printf("Error reading file");
		return -1;
	}
	char* method =(char*)malloc(sizeof(char) * 5);
	unsigned int* val = (unsigned int*)malloc(sizeof(int));
	input_file = fopen(argv[1],"r");
	int n;
	int newval;
	int requestedBit;
	if(fscanf(input_file,"%d\n",val) == EOF){
		printf("EOF");
		return -1;
	}
	//printf("value of x is %d\n",*val);
	while(fscanf(input_file,"%s\n",method) != EOF){
		if(compare(method,"set")){
			fscanf(input_file,"%d\t%d",&n,&newval);
			set(val,n,newval);
		}
		else if(compare(method,"get")){
			fscanf(input_file,"%d\n",&n);
			get(val,n,0);


		}
		else if(compare(method,"comp")){
			//complement method
			fscanf(input_file,"%d\n",&n);
			complement(val,n);
		}
	}
	free(val);
	free(method);
}





int main(int charc,char *argv[]){
	unsigned int a = 5;
	//to get a bit at an index we start off with 1(0001) and shift k indices then use the and operator to add bits that match up then shift it all the way to index 0, and output will either be 0 or 1
	//get returns value of nth bit of x
	//comp switchs the value of the bit to its complement
	//sets bit to either 0 or 1

	//char* equality is checked with compare function

	fclose(input_file);
	//get bit at index 0, shifts by k to return only 1 bit
	//unsigned int val = a &(1<<0) >>0;
	//printf("%d\n",val);
	//complement
	//val = a ^(1<<0);
	//printf("%d\n",val);
	//set
	//val = a | (1<<1);
	//printf("%d\n",val);

}
	