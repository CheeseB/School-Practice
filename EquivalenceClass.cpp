#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

/*연결 리스트를 위한 노드 구조 정의*/ 
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
	
	/*배열의 크기 설정*/
	printf("크기를 입력하세요. (<= %d) ", MAX_SIZE);
    scanf("%d", &n);  
	
	/*out 배열을 true로, seq배열을 null로 초기화*/
	for(i=0;i<n;i++){
		out[i]=TRUE; 
		seq[i]=NULL;
	}
	 
	printf("동치 쌍을 입력하세요.(-1,-1 입력 시 종료):");
	scanf("%d%d",&i,&j); 
	
	while(i>=0){ //i가 음수가 되면 실행을 그만한다. 
		x=(node*)malloc(sizeof(*x)); 
		x->data=j;
		x->link=seq[i]; 
		seq[i]=x;
		//x노드에 공간을 임시로 할당해 j값을 넣고 seq[i]가 노드를 가리키게 한다. 
		
		x=(node*)malloc(sizeof(*x));
		x->data=i; 
		x->link=seq[j];
		seq[j]=x;
		//x노드에 공간을 임시로 할당해 i값을 넣고 seq[j]가 노드를 가리키게 한다. 
		
		printf("동치 쌍을 입력하세요.(-1,-1입력 시 종료):");
		scanf("%d%d",&i,&j);
	}
	
	/*동치 부류를 출력한다.*/
		for(i=0;i<n;i++)
			if(out[i]){ //out[i]의 값이 null이라면 실행하지 않는다. 
				printf("\n동치 부류 = %5d",i);
				out[i]=FALSE;//i를 출력한 후 out 값을 FALSE로 만든다. 
				x=seq[i]; top=NULL; 
				for(;;){ //i와 동치 부류인 것을 모두 출력하는 반복문 
					while(x){
						j=x->data; 
						if(out[j]){
							printf("%5d",j);
							out[j]=FALSE;//i와 동치 부류인 것들을 출력한 후 out 값을 FALSE로 만든다. 
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
