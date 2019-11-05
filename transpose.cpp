#include <stdio.h>
#define MAX 100

typedef struct Term{
	int row;
	int col;
	int val;
} Term;

Term a[MAX]={{3,4,6},{0,1,3},{0,2,8},{1,0,7},{1,1,2},{1,3,5},{2,0,4}};
Term b[MAX];

void transpose(Term a[], Term b[]);

int main(){
	int i;
	
	transpose(a,b);
	
	for(i=0;i<=b[0].val;i++)
		printf("%d %d %d\n",b[i].row,b[i].col,b[i].val);
	
	return 0;
}

void transpose(Term a[], Term b[]){
	int i,j,n;
	int cb=1;
	n=a[0].val;
	
	b[0].col=a[0].row;
	b[0].row=a[0].col;
	b[0].val=n;
	
	for(i=0;i<b[0].row;i++)
		for(j=1;j<=n;j++)
			if(a[j].col==i){
				b[cb].row= a[j].col;
				b[cb].col= a[j].row;
				b[cb].val= a[j].val;
				
				cb++;
			}
}
