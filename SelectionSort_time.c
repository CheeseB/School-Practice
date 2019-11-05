#include <stdio.h>
#include <time.h>
#define MAX 1001
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void sort(int list[],int n);

int main(){
	
	int i,n,step,a[MAX];
	clock_t start;
	clock_t stop;
	float duration;
	
	step=10;
	for(n=0; n<MAX; n+=step){
		for(i=0; i<n; i++)
			a[i] = n-i;
			
		start = clock();
		sort(a,n);
		stop = clock();
		
		duration = (float)(stop-start)/CLOCKS_PER_SEC;
		printf("%6d %f\n",n,duration);
		
		if(n==100) step=100;
	}
	
}

void sort(int list[],int n){
	int i,j,min,temp;
	
	for(i=0; i<n-1; i++){
		min = i;
		for(j=i+1; j<n; j++)
			if(list[min]>list[j]) min=j;
		SWAP(list[i],list[min],temp);
	}
}
