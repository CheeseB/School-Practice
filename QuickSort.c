#include<stdio.h>

void quicksort(int a[], int p, int r);
int partition(int a[], int p, int r);
void SWAP(int *x, int *y);

int main(){
	
	int i;
	int a[100];
	
	for(i=0; i<100; i++)
		if(i%2) a[i]=(100-i)*3+1;
		else a[i] = i*2+1;
	
	quicksort(a,0,99);
	
	for(i=0;i<100;i++)
		printf("%d\n",a[i]);
	
	return 0;
}

void quicksort(int a[], int p, int r){
	int q;
	if(p<r){
		q=partition(a,p,r);
		quicksort(a,p,q-1);
		quicksort(a,q+1,r);
	}
}

int partition(int a[],int p,int r){
	int x=a[r];
	int i=p-1;
	int j;
	
	for(j=p;j<r;j++)
		if(a[j]<=x) SWAP(&a[++i], &a[j]);
	
	SWAP(&a[++i],&a[r]);
	
	return i;
}

void SWAP(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}
