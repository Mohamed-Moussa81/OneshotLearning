#include<stdlib.h>
#include<stdio.h>
void swap(int* inputArr,int i,int j,int n,int* temp){
	*temp = inputArr[i];
	inputArr[i] = inputArr[j];
	inputArr[j] = *temp;
}



int* insertionSort(int oddCount, int* inputArr,int n,int odd){
	int i;
	int j;
	//temporary value holder for array to be used until the values of the array have been printed
	int* temp = (int*)malloc(sizeof(int));
	if (odd){
		for(i =1;i<oddCount;i++){
			for(j=i;j>0;j--){
				if(inputArr[j-1] > inputArr[j]){
					//memory error occuring, if can't be fixed just use a local pointer
					swap(inputArr,j-1,j, n,temp);
				}
				else {			
					break;
				}
			}
		}
	}
	else{
		for(i =oddCount;i<n;i++){
			for(j=i;j>=oddCount;j--){
				if(inputArr[j-1] < inputArr[j]){
					swap(inputArr,j-1,j, n,temp);
				}
				else {			
					break;
				}
			}
		}

	}
	return temp;
}



 void Sort(int oddCount,int n, int* inputArr){
	//make sure indices in bound
	int *odd_Index = (int*)malloc(sizeof(int) * oddCount);
	int index =0;
	//determine indices of odd elements
	for(int i=0;i<n;i++){
		if(inputArr[i] %2 !=0){
			odd_Index[index] = i;
			index++;
		}
	}

	//rearrange even and odd elements
	for(int i = 0;i<oddCount;i++){
		int temp = inputArr[i];
		inputArr[i]  = inputArr[odd_Index[i]];
		inputArr[odd_Index[i]] = temp;
	}
	printf("\n");
	//insertion sort
	int* tempLeft = insertionSort(oddCount,inputArr,n,1);
	int* tempRight =insertionSort(oddCount,inputArr,n,0);
	for(int i=0;i<n;i++){
		printf("%d\t",inputArr[i]);
	}
	printf("\n");
	free(inputArr);
	free(tempLeft);
	free(tempRight);
	inputArr = NULL;
	free(odd_Index);
	odd_Index = NULL;
	
}
void scanFile(FILE* inputFile){
	int n;
	int val;
	int* inputArr;
	int oddCount=0;
	int evenCount=0;
	fscanf(inputFile,"%d\n",&n);
	//first line is successfully read
	inputArr = (int*)malloc(sizeof(int) * n);
	//array scanned
	for(int i=0;i<n;i++){
		fscanf(inputFile,"%d",&val);
		if (val %2 ==0){
			evenCount++;
		}
		else {
			oddCount++;
		}
		inputArr[i] = val;
	}
	Sort(oddCount,n,inputArr);
}




int main(int argc,char *argv[]){
	//can't say remainder is 1 since negative numbers might have a remainder of -1
	/*int n;
	int val;
	int* inputArr;
	int oddCount=0;
	int evenCount=0;
	FILE* inputFile;
	inputFile = fopen(argv[1],"r");
	if (inputFile ==NULL){
		return -1;
	}
	fscanf(inputFile,"%d\n",&n);
	//first line is successfully read
	inputArr = (int*)malloc(sizeof(int) * n);
	//array scanned
	for(int i=0;i<n;i++){
		fscanf(inputFile,"%d",&val);
		if (val %2 ==0){
			evenCount++;
		}
		else {
			oddCount++;
		}
		inputArr[i] = val;
	}
	//elements unsorted
	//elements sorted
	Sort(oddCount,n,inputArr);
	//close file and free inputFile;
	*/
	FILE* inputFile;
	inputFile = fopen(argv[1],"r");
	/*if (inputFile ==NULL){
		printf("Erorr opening file");
		return -1;
	}*/
	scanFile(inputFile);
	fclose(inputFile);
	


	
	return 0;
}


