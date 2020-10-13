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
	//either negative need to return positive factor
	if(x<0 && y>0){
		return -x/y;
	}
	else if(x>0 && y<0){
		return -x/y;
	}
	else{
		//both positive or negative, need to
		return -x/y;
	}

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
	printf("Invert! METHOD");
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
			aug[i][j] = 1.0;
		}
		else{
			aug[i][j] = 0.0;
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


//free aug;
return aug;
}




double** multiply(double** m1, double** m2, int m1Row, int m2Row,int m1Col, int m2Col){
	//works!
	int i;
	int j;
	int k;
	int sum;
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



int main(int argc, char* argv[]){
FILE* training = fopen(argv[1],"r");
if(training ==NULL){
	printf("Unable to open training file");
	return -1;
}
//initilizing arrays
int k;
int n;
int i;
int j;
double* Y;
double* W;
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
Y = (double*)malloc(sizeof(double) * n);
W = (double*)malloc(sizeof(double) * (k+1));
X = (double**)malloc(sizeof(double*) * n);

for( i =0;i<n;i++){
	X[i] = (double*)malloc(sizeof(double) * (k+1));
}
i = 0;
j =0;
//reads values into X and Y matrix
while(fscanf(training,"%lf",&Y[i]) !=EOF){
	X[j][0] = Y[i];
	for(int c = 1; c<k+1;c++){
		fscanf(training,",%lf",&X[j][c]);
	}
	i++;
	j++;
}

/* prints matrices
printf("Y matrix: \n");
printf("[");
for(i =0;i<n;i++){
	printf(" %lf ,",Y[i]);
}
//printing X matrix
	printf("]\n\n");*/
for(i =0;i<n;i++){
	printf("[");
	for(j=0;j<k+1;j++){
		printf("%lf,",X[i][j]);
		//printf("%lf,",Xtranspose[i][j]);
	}
	printf("]\n");
}
printf("\n\n\n");
//Prints Transpose
Xtranspose = transpose(X,n,k+1);
/*for(i =0;i<k+1;i++){
	printf("[");
	for(j=0;j<n;j++){
		printf("%lf,",Xtranspose[i][j]);
		//printf("%lf,",Xtranspose[i][j]);
	}
	printf("transpose DONE]\n\n");
}*/
//product of xtranspose * x
//m1,m2,m1row,m2row,m1col,m2col
double** productXTranspose = multiply(Xtranspose,X,k+1,n,n,k+1);
printf("product done");
//row, col
double** inverted = invert(X,(k+1),(k+1));
//move identity part into a new matrix
double** inverseXTranspose = multiply(inverted,Xtranspose,(k+1),(k+1),(k+1),N);
//find out correct row and col
W = multiply(inverseXTranspose,Y,row,col);
//then read following file and //for each data point multiply the corresponding attributes with weights and add together and print each price
//row and col are k+1, but need to access col from k+1 to 2(k+1) since identity
printf(" invert done");
//printf("%lf",inverted[i][j]);
//equation W=(Xtranspose * X)(-1 inverse)* Xtranspose * Y
//inverted is the entire augmented matrix need to work with identity part
for(i=0;i<(k+1);i++){
		printf("[");
	for(j=(k+1);j<2*(k+1);j++){
		printf("%lf,",inverted[i][j]);
	}
		printf("]\n\n");
}
//equation for W is W= (xtranpose*X)^-1* XTranspoeY
//row becomes k+1, column becomes n for transpose


return 0;
}