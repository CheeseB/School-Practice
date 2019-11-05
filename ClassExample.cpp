#include <iostream>
#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

using namespace std;

class Fraction{
	public:
		void get_num();
		int print_num1();
		int print_num2();
		double mutator();
		void yack();
	private:
		int num1, num2;
};

int main(){
	
	Fraction f;
	
	f.get_num();
	f.yack();
	
	cout<<f.print_num1()<<"/"<<f.print_num2()<<"="<<f.mutator()<<endl;
	
	return 0;
}

void Fraction::get_num(){
	cout << "두개의 정수를 입력하세요.(두 정수 중 큰 값이 분모가 됩니다.):";
	cin >>num1>>num2;
}

int Fraction::print_num1(){
	return num1;
}

int Fraction::print_num2(){
	return num2;
}

double Fraction::mutator(){
	int temp;
	if(num1>num2)
		SWAP(num1,num2,temp);
		
	return static_cast<double>(num1)/num2;
}

void Fraction::yack(){
	int i, yack;
	for(i=1;i<=num1;i++)
		if(num1%i==0 && num2%i==0)
			yack=i;
	num1/=yack;
	num2/=yack;
}

