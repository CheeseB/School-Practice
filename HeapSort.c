#include <stdio.h>

void heapsort(int a[], int n);
void buildheap(int a[],int n);
void heapify(int a[], int k, int n);

void SWAP(int *x, int *y);

int main(){
	int i;
	int a[100];
	
	for (i=0; i<100; i++)
		if(i%2) a[i] =(100-i)*3+1;
		else a[i]=i*2+1;
		
	heapsort(a,99);
	
	for(i=0; i<100; i++)
		printf("%d ",a[i]);
	
	return 0;
}

void heapsort(int a[], int n){
	int i;
	buildheap(a,n);
	for(i=n;i>=2;i--){
		SWAP(&a[1],&a[i]);
		heapify(a,1,i-1);
	}
}

void buildheap(int a[],int n){
	int i;
	for(i=n/2; i>=1; i--)
		heapify(a,i,n);
}

void heapify(int a[], int k, int n){
	int left = 2*k;
	int right = 2*k+1;
	int big;
	
	if(right <=n)
		if(a[left]>a[right]) big = left;
		else big = right;
	else if(left<=n)
		big = left;
	else
		return;
		
	if(a[big]>a[k]){
		SWAP(&a[big],&a[k]);
		heapify(a,big,n);
	}
}

void SWAP(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}
