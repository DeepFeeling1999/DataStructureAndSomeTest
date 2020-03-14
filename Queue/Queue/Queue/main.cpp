#include<iostream>
#include"Queue.h"
#include<stdlib.h>
#include<string>
using namespace std;
int main(void)
{
	int num;
	Queue q;

	while (cin >> num)
	{
		fflush(stdin);
		Push(&q, num);
	}
	cout << IsEmpty(&q)<<endl;
	cout << IsFull(&q) << endl;

	system("pause");
	return 0;
}