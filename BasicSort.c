#include <stdio.h>

void sort(int a[],int n);
void bsort(int a[], int n);
void isort(int a[], int n);

void SWAP(int *x,int *y);

int main(){
	int i;
	int a[5]={3,1,2,4,5};
	int b[5]={2,4,5,3,1};
	int c[5]={5,4,1,3,2};
	sort(a,5);
	bsort(b,5);
	isort(c,5);
	
	for(i=0; i<5; i++)
		printf("%d ",a[i]);
		
	printf("\n");
	
	for(i=0; i<5; i++)
		printf("%d ",b[i]);	
	
	printf("\n");
	
	for(i=0; i<5; i++)
		printf("%d ",c[i]);
	
	return 0;
}

//선택정렬 
void sort(int a[],int n){
	int last,i,max;
	for(last=n-1;last>0;last--){
		max=last;
		for(i=0;i<last;i++)
			if(a[max]<a[i])
				max=i;
				
		SWAP(&a[last],&a[max]);
	}
}

//버블정렬
void bsort(int a[], int n){
	int last,i;
	for(last=n-1; last>0; last--)
		for(i=0; i<last; i++)
			if(a[i]>a[i+1])
				SWAP(&a[i],&a[i+1]);
} 

//삽입정렬
void isort(int a[],int n){
	int i,loc,newItem;
	for(i=1; i<n; i++){
		loc=i-1;
		newItem=a[i];
		while(loc>=0 && newItem<a[loc]){
			a[loc+1] = a[loc];
			loc=loc-1;
		}
		a[loc+1]=newItem;
	}
}

void SWAP(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}
