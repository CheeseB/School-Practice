#include <iostream>

using namespace std;
void deleteVowels(char p[], int &loc);

int main(){
	
	char p[10];
	p[0]='R';
	p[1]='o';
	p[2]='b';
	p[3]='o';
	p[4]='t';
	
	int size = 5;
	
	cout << "���� ���ڿ�:";
	for(int i=0; i<size; i++)
		cout<<p[i];
	cout<<"\nũ��:"<<size<<endl;
	
	deleteVowels(p,size);
	
	cout << "���� ���� �� ���ڿ�: ";
	for(int i=0; i<size; i++)
		cout<<p[i];
	cout<<"\nũ��:"<<size<<endl;

	return 0;
}

void deleteVowels(char p[], int &loc){
	for(int i=0; i<loc; i++)
		switch(p[i]){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				for(int j=0; j<loc-i; j++)
					p[i+j]=p[i+j+1];
	}
	for(int k=0; k<5; k++)
		if(p[k]!='\0')
			loc=k+1;
}

