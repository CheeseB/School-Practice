#include <stdio.h>

void mergesort(int a[], int p, int q);
void merge(int a[],int p, int q, int r);

int main(){
	int i;
	int a[4]={45,25,35,30};
	
	mergesort(a,0,3);
	
	for(i=0;i<4;i++)
		printf("%d ",a[i]);
	
	return 0;
}

void mergesort(int a[], int p, int r){
	int q;
	if(p<r){
		q=(p+r)/2;
		mergesort(a,p,q);
		mergesort(a,q+1,r);
		merge(a,p,q,r);
	}
}

void merge(int a[], int p, int q, int r){
	int i=p;
	int j=q+1;
	int t=0;
	int temp[r-p+1];
	
	while(i<=q && j<=r)
		if(a[i]<=a[j]) temp[t++]=a[i++];
		else temp[t++]=a[j++];
		
	while(i<=q)
		temp[t++]=a[i++];
		
	while(j<=r)
		temp[t++]=a[j++];
		
	for(i=p,t=0;i<=r;i++)
		a[i]=temp[t++];
}
