#include <iostream>
#include <vector>

using namespace std;

int main(){
	
	int n,loc=0;
	cout<< "��ȥ���� ���� �Է��ϼ���.:";
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
	
	cout << endl<< v[0] <<"��° ��ġ�� �� �־�� �մϴ�."<<endl;
	
    return 0;
}

