#include<iostream>
#include"Tree.h"
using std::endl;
using std::cout;
using std::cin;
int main(void)
{
	Tree T=nullptr;
	int test = 1;
	int num;

	cout << "Please enter a character sequence: (-1 to quit)\n";
	while (1)
	{
		if (!(cin >> num))
		{
			cout << "Please enter legal characters!\n";
		}
		else
		{
			if (num == -1)
				break;
			else if (!Add(T, num))
				cout << "Storage failure!";
		}	
		cin.get();
	}

	cout << "Now,the preorder is :\n";
	Preorder(T);
	cout << endl<<endl;
	cout<<"And LevelOrder is :\n";
	LevelOrder(T);

	system("pause");
	return 0;
}