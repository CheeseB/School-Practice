#include <stdio.h>

void sort(int list[],int n);
void SWAP(int *x, int *y);

int main() {
	
	int i,num;
	int a[10];
	
	printf("10���� ���ڸ� �Է��� �ּ���.: ");
	for(i=0; i<10; i++)
		scanf("%d",&a[i]);
	
	printf("���� �� : ");
	for(i=0; i<10; i++)
		printf("%d ",a[i]);
	
	sort(a,10);
	
	printf("\n���� �� : ");
	for(i=0; i<10; i++)
		printf("%d ",a[i]);
	return 0;
}

void sort(int list[],int n){
	int i,j,min,temp;
	
	for(i=0; i<n-1; i++){
		min = i;
		for(j=i+1; j<n; j++)
			if(list[min]>list[j]) min=j;
		SWAP(&list[i],&list[min]);
	}
	
}

void SWAP(int *x, int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}

