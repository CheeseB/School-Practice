
#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int n;
	cout << "트리의 층을 선택하세요 : ";
	cin >> n;
	
	int nk = n * 2 + 1;


	for (int i = 0; i < 3; i++)
	{
		if (i != 2) {
			for (int j = 1; j < n + 1; j++)
			{
				for (int k = 0; k < nk; k++)
				{
					if (k == n)
						cout << "*";
					else if (k <= n - j || k >= n + j)
						cout << " ";
					else
						cout << "*";
				}
				cout << endl;
			}
		}
		else {
			for (int j = 1; j < n + 1; j++)
			{
				for (int k = 0; k < nk; k++)
				{
					if (n < 10)
					{
						if (k == n)
							cout << "*";
						else
							cout << " ";
					}

					else if (n > 10 && n < 30)
					{
						if (k >= n - 1 && k <= n + 1)
							cout << "*";
						else
							cout << " ";
					}
					else
					{
						if (k >= n - 2 && k <= n + 2)
							cout << "*";
						else
							cout << " ";
					}
					
				}
				cout << endl;
			}
		
		}
		
	}
	return 0;
}
