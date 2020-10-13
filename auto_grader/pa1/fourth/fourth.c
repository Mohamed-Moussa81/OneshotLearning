#include<stdlib.h>
#include<stdio.h>
#include "fourth.h"

int main(int argc, char* argv[]){
	if (argc<3){
		printf("error\n");
		exit(0);
	}
FILE* training = fopen(argv[1],"r");
if(training ==NULL){
	printf("0\n");
	exit(0);
}

int k,n,m,i,j;
double** Y;
double** W;
double** X;
double** Xtranspose;
fscanf(training,"%d\n",&k); 
fscanf(training,"%d\n",&n); 

Y = (double**)malloc(sizeof(double*) * n);
X = (double**)malloc(sizeof(double*) * n);

for( i =0;i<n;i++){
	X[i] = (double*)malloc(sizeof(double) * (k+1));
	Y[i] = (double*)malloc(sizeof(double));
}

i = 0;
j =0;

while(fscanf(training,"%lf",&Y[i][0]) !=EOF){
	X[j][0] = 1;
	for(int c = 1; c<k+1;c++){
		fscanf(training,",%lf",&X[j][c]);
	}
	i++;
	j++;
	if(i>=n && j>=n){
		break;
	}
}
Xtranspose = transpose(X,n,k+1);
//printf("X Transpose is: \n");
//printmatrix(Xtranspose,k+1,n);

double** productXs = multiply(Xtranspose,X,k+1,n,n,k+1);

double** inverted = invert(productXs,(k+1),(k+1));

double** inverse = copyInverse(inverted,k+1,k+1);
double** product_inverse_XT= multiply(inverse,Xtranspose,(k+1),(k+1),(k+1),n);
W = multiply(product_inverse_XT,Y,k+1,n,n,1);
//printf("Weight Matrix is:\n");
//printmatrix(W,k+1,1);

FILE* test = fopen(argv[2],"r");
if(test ==NULL){
	exit(0);
}
fscanf(test,"%d\n",&m);
double** attributes = (double**)malloc(sizeof(double*)*m);
for(i=0;i<m;i++){
	attributes[i] = (double*)malloc(sizeof(double)*(k+1));
	attributes[i][0] = 1;
	for(j=1;j<(k+1);j++){
		fscanf(test,"%lf,",&attributes[i][j]);
	}
}

double** answer = multiply(attributes,W,m,k+1,k+1,1);
//printf("Predicted House prices are:\n");
for(i=0;i<m;i++){
	printf("%0.0lf\n",answer[i][0]);
}
freeArray(answer,m);
freeArray(W,k+1);
freeArray(X,n);
freeArray(Y,n);
freeArray(product_inverse_XT,k+1);
freeArray(inverse,k+1);
freeArray(Xtranspose,k+1);
freeArray(inverted,k+1);
freeArray(productXs,k+1);

fclose(training);
fclose(test);

return 0;
}

double** transpose(double** matrix,int row,int col){

	int i;
	int j;
	double** temp = (double**)malloc(sizeof(double*) * col);
	for(j =0;j<col;j++){
	temp[j] = (double*)malloc(sizeof(double) * row);
	}
	for(i =0;i<row;i++){
		for(j=0;j<col;j++){
			temp[j][i] = matrix[i][j];
		}
	}
	
	return temp;

}
void add(double** matrix,int r1, int r2, int col,double factor){
	int j;
	double val;
	for(j=0;j<col;j++){
		if(matrix[r2][j] ==0){
			continue;
		}
		val = matrix[r2][j] * factor;
		matrix[r1][j] = matrix[r1][j] + val;
	}


}
double factor(double x, double y){
	//finds factor to multiply when subtracting rows to result in Identity Matrix
	if((x -y) ==0){
		return -1;
	}
		return -x/y;
	

}
double factorIdent(double x){
	//Identiy Matrix,helper Method
	if( x ==1){
		return 1;
	}
	return (1/x);
	
}

void rowMultiply(double** matrix,int row,int col,double val){
	int j;
	for(j =0;j<col;j++){
		if(matrix[row][j] ==0){
			continue;
		}
		matrix[row][j] = matrix[row][j] * val;
	}
}

double** invert(double** matrix,int row, int col){
	int i;
	int j;
	double val;

	int  c = 2 * col;
	double** aug = (double**)malloc(sizeof(double*) * (row));

	for(i =0;i<row;i++){
		aug[i] = (double*)malloc(sizeof(double) * (2*col));
}
for( i =0;i<row;i++){
	for(j=0;j<col;j++){
		aug[i][j] = matrix[i][j];
	}
}

for( i=0;i<row;i++){

	for(j=col;j<c;j++){
		if(j==(row+i)){
			aug[i][j] = 1;
		}
		else{
			aug[i][j] = 0;
		}
	}
}

for(i =0;i<row;i++){
	for(j=0;j<=i;j++){
		if(i==j){
			if(aug[i][j] ==1){
				continue;
			}
			val = factorIdent(aug[i][j]);

			rowMultiply(aug,i,c,val);
		}
		else{

			if(aug[i][j] ==0){
				continue;
			}
			val =factor(aug[i][j],aug[j][j]);
			add(aug,i,j,c,val);
		}
	}
}

	for(j=col-1;j>0;j--){
		for(i = row-2;i>=0;i--){
			if(i==j){
				if(aug[i][j] ==1){
					continue;
				}
				val = factorIdent(aug[i][j]);
				rowMultiply(aug,i,c,val);
			}
			else {
				if(aug[i][j] ==0){
					continue;
				}
				val =factor(aug[i][j],aug[j][j]);
			add(aug,i,j, c,val);
			}
	}
}

return aug;

}

double** multiply(double** m1, double** m2, int m1Row, int m2Row,int m1Col, int m2Col){

	int i;
	int j;
	int k;
	double sum;

	double** res = (double**)malloc(sizeof(double*) * m1Row);
	for(i=0;i<m1Row;i++){
		res[i] = (double*)malloc(sizeof(double) * m2Col);
	}
	for(i =0;i<m1Row;i++){
		for(j=0;j<m2Col;j++){
			sum =0;
			for(k=0;k<m1Col;k++){
				sum += m1[i][k]*m2[k][j];
				}
				res[i][j] = sum;
			}
			
		
	}
	return res;

}
void freeArray(double** matrix,int row){
	int i;
	for(i=0;i<row;i++){
		free(matrix[i]);
	}
	free(matrix);
	matrix = NULL;
}
double** copyInverse(double** aug,int col, int row){
	int i;
	int j;

	double** inverse = (double**)(malloc(sizeof(double*)*row));
	for(i=0;i<row;i++){
		inverse[i] = (double*)(malloc(sizeof(double) * col));
	}
	for( i=0;i<row;i++){
		for(j=col;j<(2*col);j++){
			inverse[i][j-col] = aug[i][j]; 
		}
	}
	return inverse;
}
void printmatrix(double** matrix, int row, int col){
	int i;
	int j;
	for( i=0;i<row;i++){
		printf("[ ");
		for(j=0;j<col;j++){
			printf("%lf,",matrix[i][j]);
		}
		printf("\n");
	}
	printf("]\n\n");
}

