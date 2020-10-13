#include<stdlib.h>
#include<stdio.h>


double** transpose(double** matrix,int row,int col){
	//works
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
	//finds factor to multiply when subtracting rows
	if((x -y) ==0){
		return -1;
	}
		//both positive or negative, need to
		return -x/y;
	

}
double factorIdent(double x){
	//factor to result in 1
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

double **invert(double** matrix,int row, int col){
	//works!
	//invert method inverts bottom half then upper half
	//same amount of rows for augmented matrix, just more coloumns
	int i;
	int j;
	double val;
	//int r = 2 * row;
	int  c = 2 * col;
	double** aug = (double**)malloc(sizeof(double*) * (row));
	//double** invert = (double**)malloc(sizeof(double*) * row);
	//setting up inverted matrix to copy augmented results
	/*for(i=0;i<row;i++){
		invert[i] = (double*)malloc(sizeof(double) * col);
	}*/
	//set up memory for matrix with malloc
	//2*col-1, since last one not used maybe
	for(i =0;i<row;i++){
		aug[i] = (double*)malloc(sizeof(double) * (2*col));
}
//copy data
for( i =0;i<row;i++){
	for(j=0;j<col;j++){
		aug[i][j] = matrix[i][j];
	}
}
//copy identity matrix
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

//begin inverting, bottom half
for(i =0;i<row;i++){
	for(j=0;j<=i;j++){
		if(i==j){
			if(aug[i][j] ==1){
				continue;
			}
			val = factorIdent(aug[i][j]);
			//operate on the entire row;
			rowMultiply(aug,i,c,val);
		}
		else{
			//we subtract row j from row i Ri - Rj, but need to find factor
			//nede to set invert[i][j] to 0
			if(aug[i][j] ==0){
				continue;
			}
			val =factor(aug[i][j],aug[j][j]);
			add(aug,i,j,c,val);
		}
	}
}

//upper half
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
	
	//copy inverse matrix into invert and return
	/*for(i =row;i<r;i++){
		for(j=col;j<c;j++){
			invert[i-row][j-col] =  aug[i][j];
		}
	}*/


//returns augmented matrix;
return aug;
}




double** multiply(double** m1, double** m2, int m1Row, int m2Row,int m1Col, int m2Col){
	//works!
	int i;
	int j;
	int k;
	double sum;
	//matrix multiplication m1row X m1col and m2Row x M2col results in m1row * m2col; m1col and m1row need to match up
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
	// result matrix type: m1row X m2col
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
	//col is regular matrix not aug need to multiply by 2
	double** inverse = (double**)(malloc(sizeof(double*)*row));
	for(i=0;i<row;i++){
		inverse[i] = (double*)(malloc(sizeof(double) * col));
	}
	for( i=0;i<row;i++){
		for(j=col;j<(2*col);j++){
			inverse[i][j-col] = aug[i][j]; 
		}
	}
	freeArray(aug,row);
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



int main(int argc, char* argv[]){
	//double test =  (double)((double)221900 * (double)221900 + (double)538000 * (double)538000 * (double)180000 * (double)180000 + (double)604000 * (double)604000 + (double)510000 * (double)510000 + (double)1230000 * (double)1230000 + (double)257500 *  (double)257500 + (double)219850 * (double)291850 + (double)229500 * (double)229500 + (double)323000 * (double)323000);
	//printf("%lf",test);
FILE* training = fopen(argv[1],"r");
if(training ==NULL){
	printf("Unable to open training file");
	return -1;
}
//initilizing arrays
int k;
int n;
int m;
int i;
int j;
double** Y;
double** W;
double** X;
double** Xtranspose;
//checking to see if file is empty
if(fscanf(training,"%d\n",&k) ==EOF){
	printf("EOF error");
	return -1;
}
if(fscanf(training,"%d\n",&n) ==EOF){
	printf("EOF error");
	return -1;
}
Y = (double**)malloc(sizeof(double*) * n);
X = (double**)malloc(sizeof(double*) * n);

for( i =0;i<n;i++){
	X[i] = (double*)malloc(sizeof(double) * (k+1));
	Y[i] = (double*)malloc(sizeof(double));
}

i = 0;
j =0;
//reads values into X and Y matrix
while(fscanf(training,"%lf",&Y[i][0]) !=EOF){
	X[j][0] = 1;
	for(int c = 1; c<k+1;c++){
		fscanf(training,",%lf",&X[j][c]);
	}
	i++;
	j++;
}
//transpose is (k+1 X N), X is (N X K +1)
Xtranspose = transpose(X,n,k+1);
double** productXs = multiply(Xtranspose,X,k+1,n,n,k+1);

//result is m1col X m2col; k+1 X k+1

double** inverted = invert(productXs,(k+1),(k+1));
//freeArray(productXs,k+1);
//move inverted part form augmented matrix and free augmented
double** inverse = copyInverse(inverted,k+1,k+1);
//freeArray(inverted,k+1);
double** product_inverse_XT= multiply(inverse,Xtranspose,(k+1),(k+1),(k+1),n);
W = multiply(product_inverse_XT,Y,k+1,n,n,1);
//freeArray(product_inverse_XT,k+1);
//freeArray(inverse,k+1);
//freeArray(Xtranspose,k+1);

//read m from second file
FILE* test = fopen(argv[2],"r");
if(test ==NULL){
	return -1;
}
if(fscanf(test,"%d\n",&m) == EOF){
	return -1;
}
double** attributes = (double**)malloc(sizeof(double*)*m);
for(i=0;i<m;i++){
	attributes[i] = (double*)malloc(sizeof(double)*k+1);
	attributes[i][0] = 1;
	for(j=1;j<(k+1);j++){
		fscanf(test,"%lf,",&attributes[i][j]);
	}
}
double** answer = multiply(attributes,W,m,k+1,k+1,1);
//output m *1
for(i=0;i<m;i++){
	printf("%0.0lf\n",answer[i][0]);
}
//freeArray(answer,m);
//freeArray(W,n);
//freeArray(X,n);
//freeArray(Y,n);


//close both files
return 0;
}
