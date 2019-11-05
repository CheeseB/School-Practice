#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

/*���� ����Ʈ�� ���� ��� ���� ����*/ 
typedef struct node *nodePointer;
typedef struct node{
	int data;
	nodePointer link;
}; 

int main(){
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x,y,top;
	int i,j,n;
	
	/*�迭�� ũ�� ����*/
	printf("ũ�⸦ �Է��ϼ���. (<= %d) ", MAX_SIZE);
    scanf("%d", &n);  
	
	/*out �迭�� true��, seq�迭�� null�� �ʱ�ȭ*/
	for(i=0;i<n;i++){
		out[i]=TRUE; 
		seq[i]=NULL;
	}
	 
	printf("��ġ ���� �Է��ϼ���.(-1,-1 �Է� �� ����):");
	scanf("%d%d",&i,&j); 
	
	while(i>=0){ //i�� ������ �Ǹ� ������ �׸��Ѵ�. 
		x=(node*)malloc(sizeof(*x)); 
		x->data=j;
		x->link=seq[i]; 
		seq[i]=x;
		//x��忡 ������ �ӽ÷� �Ҵ��� j���� �ְ� seq[i]�� ��带 ����Ű�� �Ѵ�. 
		
		x=(node*)malloc(sizeof(*x));
		x->data=i; 
		x->link=seq[j];
		seq[j]=x;
		//x��忡 ������ �ӽ÷� �Ҵ��� i���� �ְ� seq[j]�� ��带 ����Ű�� �Ѵ�. 
		
		printf("��ġ ���� �Է��ϼ���.(-1,-1�Է� �� ����):");
		scanf("%d%d",&i,&j);
	}
	
	/*��ġ �η��� ����Ѵ�.*/
		for(i=0;i<n;i++)
			if(out[i]){ //out[i]�� ���� null�̶�� �������� �ʴ´�. 
				printf("\n��ġ �η� = %5d",i);
				out[i]=FALSE;//i�� ����� �� out ���� FALSE�� �����. 
				x=seq[i]; top=NULL; 
				for(;;){ //i�� ��ġ �η��� ���� ��� ����ϴ� �ݺ��� 
					while(x){
						j=x->data; 
						if(out[j]){
							printf("%5d",j);
							out[j]=FALSE;//i�� ��ġ �η��� �͵��� ����� �� out ���� FALSE�� �����. 
							y=x->link;
							x->link=top;
							top=x;
							x=y;
						}
						else x=x->link;
					}
					if(!top) break;
					x=seq[top->data]; top=top->link;
				}
			}
	return 0;
} 
