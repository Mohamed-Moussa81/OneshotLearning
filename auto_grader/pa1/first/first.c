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
	int i;
	//determine indices of odd elements
	for( i=0;i<n;i++){
		if(inputArr[i] %2 !=0){
			odd_Index[index] = i;
			index++;
		}
	}

	//rearrange even and odd elements
	for( i = 0;i<oddCount;i++){
		int temp = inputArr[i];
		inputArr[i]  = inputArr[odd_Index[i]];
		inputArr[odd_Index[i]] = temp;
	}
	//printf("\n");
	//insertion sort
	int* tempLeft = insertionSort(oddCount,inputArr,n,1);
	int* tempRight =insertionSort(oddCount,inputArr,n,0);
	for( i=0;i<n;i++){
		printf("%d\t",inputArr[i]);
	}
	//printf("\n");
	free(inputArr);
	free(tempLeft);
	free(tempRight);
	inputArr = NULL;
	free(odd_Index);
	odd_Index = NULL;
	
}
void scanFile(FILE* inputFile){
	int n;
	int i;
	int val;
	int* inputArr;
	int oddCount=0;
	int evenCount=0;
	fscanf(inputFile,"%d\n",&n);
	//first line is successfully read
	inputArr = (int*)malloc(sizeof(int) * n);
	//array scanned
	for( i=0;i<n;i++){
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
	FILE* inputFile;
	inputFile = fopen(argv[1],"r");
	if (inputFile ==NULL){
		printf("Erorr opening file");
		return -1;
	}
	scanFile(inputFile);
	fclose(inputFile);
	
	return 0;
}



