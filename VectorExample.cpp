#include <iostream>
#include <vector>

using namespace std;

int main(){
	
	int n,loc=0;
	cout<< "구혼자의 수를 입력하세요.:";
	cin >>n;
	
	vector <int>v(n);
	
	for (int i=0;i<n;i++)
		v[i]=i+1;
	for (int i=0;i<n;i++)
		cout<<v[i];
		
	while(v.size()>1){
		loc+=2;
		if(loc<v.size())
			v.erase(v.begin()+loc);
		else{
			loc%=v.size();
			v.erase(v.begin()+loc);
		}
		cout<<endl;
		
		for (int i=0;i<v.size();i++)
			cout<<v[i];
	}
	
	cout << endl<< v[0] <<"번째 위치에 서 있어야 합니다."<<endl;
	
    return 0;
}

