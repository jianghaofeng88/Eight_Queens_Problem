// Eight Queens Problem 
#include<stdio.h>
#include<stdlib.h> 

void initialize(int board[8][8], int row){
	for (int i=row;i<8;i++){
		for (int j=0;j<8;j++){
			board[i][j] = 0;
		}
	}
}

void print(int board[8][8]){
	for (int i=0;i<8;i++){
		for (int j=0;j<8;j++){
			printf(" %d", board[i][j]);
		}
		printf("\n");
	}
}

int check_rowcol(int board[8][8], int i, int j){
    int n;
    for (n=0;n<8;n++){
   		if (board[i][n] == 1 && n!=j){
   			return 0;
		}
		if (board[n][j] == 1 && n!=i){
   			return 0;
		}	
    }
    return 1;  
}

int check_diagonal(int board[8][8], int i, int j){
	int n;
	for (n=-7;n<8;n++){
		if (0<=i+n && i+n<=7 && 0<=j+n && j+n<=7 && board[i+n][j+n] == 1 && n!=0){
			return 0;
		}
		if (0<=i+n && i+n<=7 && 0<=j-n && j-n<=7 && board[i+n][j-n] == 1 && n!=0){
			return 0;
		}
	}
	return 1;
}

int check_entry(int board[8][8], int i, int j){
	int a = check_rowcol(board,i,j);
	int b = check_diagonal(board,i,j);
	return a*b;
}

int solved(int board[8][8]){
	int i,j,acc;
	acc = 0;
	for (i=0;i<8;i++){
		for (j=0;j<8;j++){
			if (board[i][j] == 1){
				if (check_entry(board, i, j) == 0){
					return 0;
				}
				acc++;
			}
		}
	}
	if (acc != 8){
		return 0;
	}
	return 1;
}

//***********************************
// Solve the problem recursively
//***********************************
int find_next_entry(int board[8][8], int startrow, int startcol, int *col){
	int i, j;
 	
 	if (startcol == 7){
 		return 0;
	}
	
 	for (j=startcol+1;j<8;j++){
 		if (check_entry(board, startrow, j)){
 			*col = j;
 			return 1;
		}
	}

	return 0;
}

void fill_recursively(int board[8][8], int i, int j[8], int acc){
	int tem_col,inspector,new_col;
 	inspector = 0;
	if (i <= 7){
		for(tem_col=0;tem_col<8;tem_col++){
			if(check_entry(board,i,tem_col)){
				board[i][tem_col] = 1;
				inspector = 1;
				j[i] = tem_col;
				break;
			}
		}

		if (inspector == 1){
			fill_recursively(board,i+1,j,acc);

		}else{
			
			while(i>=1){
				initialize(board,i-1);
				if(find_next_entry(board,i-1,j[i-1],&new_col)){	
					j[i-1] = new_col;
					board[i-1][new_col] = 1;
					fill_recursively(board,i,j,acc);
				}
				if (solved(board)){
					printf(" Solution #%d:\n",++acc);
					print(board);
					printf("\n\n");
					i=8;
				}
				i--;
			}			
			
		}
	}
	
}

void recursive_EightQueensProblem(){
	int board[8][8];
	initialize(board,0);
	int j[8];
	for(int i=0;i<8;i++){
		j[i] = 0;
	}
	fill_recursively(board,0,j,0);
	printf("*****<Eight Queens Problem Ends Recursively>*****\n");
}



//***********************************
// Solve the problem non-recursively
//***********************************

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[],int from, int to) {
    while(from < to) {
        int tmp = arr[from];
        arr[from]= arr[to];
        arr[to] = tmp;
        from++;
        to--;
    }
}

int next_array(int A[]) {
    int i,j,m;
    for(i=6;i>=0;i--) {
        if(A[i+1] > A[i]){
        	break;
		}  
    }
    
    if(i < 0){
    	return 0;
	}    
    m = i;
    i++;
    for(j=7;j>i;j--) {
        if(A[j] >= A[m]){
        	 break;
		}     
    }
    swap(&A[j],&A[m]);
    reverse(A,m+1,7);
    return 1;
}


void fill_non_recursively(int board[8][8], int x[8], int y[8]){
	int i;
	for(i=0;i<8;i++){
		board[y[i]][x[i]] = 1;
	}
}


void non_recursive_EightQueensProblem(){
	int board[8][8];
	initialize(board,0);
	int acc = 0;
	int x[8] = {0,1,2,3,4,5,6,7};
	int y[8] = {0,1,2,3,4,5,6,7};
	
	while (next_array(x)){
		fill_non_recursively(board,x,y);
		if (solved(board)){
			printf(" Solution #%d:\n",++acc);
			print(board);
			printf("\n\n");
		}
		initialize(board,0);
	}
	printf("*****<Eight Queens Problem Ends Non-Recursively>*****\n");
}




int main(){
	recursive_EightQueensProblem();
	//non_recursive_EightQueensProblem();
	return 0;
}
