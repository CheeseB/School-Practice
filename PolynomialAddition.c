#include <stdio.h>
#define COMPARE(x,y) ((x)<(y)? -1:((x)==(y))?0:1)
#define MAX 100

typedef struct Polynomial2{
	float coef;
	int exp;
} Polynomial2;
Polynomial2 term[MAX]={{3,6},{6,5},{6,4},{6,3},{7,2},{3,1},{10,0},{1,20},{2,6},{8,4},{1,3},{6,2},{7,1}};
int avail;

void padd(int sa, int fa, int sb, int fb, int *sd, int *fd);
void attach(float coef, int exp);

int main(){
	int i;
	int startA,finishA;
	int startB,finishB;
	int startD,finishD;
	
	startA=0, finishA=6;
	startB=7, finishB=12;
	avail=13;
	
	padd(startA,finishA,startB,finishB,&startD,&finishD);
	
	printf("D(x) = ");
	for(i=startD;i<finishD;i++)
		printf("%.fx^%d + ",term[i].coef,term[i].exp);
	printf("%.fx",term[finishD].coef);
	
	return 0;
}

void padd(int sa, int fa, int sb, int fb, int *sd, int *fd){
	*sd = avail;
	float coef;
	
	while(sa<=fa && sb<=fb)
		switch(COMPARE(term[sa].exp, term[sb].exp)){
			case -1:
				attach(term[sb].coef,term[sb].exp);
				sb++;
				break;
				
			case 0:
				coef=term[sa].coef + term[sb].coef;
				if(coef)
					attach(coef,term[sa].exp);
				sa++, sb++;
				break;
			
			case 1:
				attach(term[sa].coef,term[sa].exp);
				sa++;
		}
		
	for(;sa<=fa;sa++)
		attach(term[sa].coef,term[sa].exp);
		
	for(;sb<=fb;sb++)
		attach(term[sb].coef,term[sb].exp);
		
	*fd = avail-1;
}

void attach(float coef, int exp){
	term[avail].coef=coef;
	term[avail++].exp=exp;
}
