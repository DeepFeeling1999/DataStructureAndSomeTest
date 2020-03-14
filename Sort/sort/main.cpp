#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cctype>
#include<ctime>
#include<valarray>
#include<windows.h>
#include<iomanip>
#include<cmath>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define LeftChild(i) (2*(i)+1)		//��������Ѱ������ӽڵ�
#define cutoff (3)
using std::endl;
using std::cout;
using std::cin;
using std::valarray;
using namespace std;
void initialize(int ar[], int amount);
void show(int ar[], int amount, string fun_name, double running_time);
void swap(int* temp1, int *temp2);

void InsertionSort(int ar[], int amount);	

void PercDown(int ar[], int i, int N);
void HeapSort(int ar[], int N);

void MergeSort(int Ar[], int N);
void Msort(int Ar[], int TempAr[], int left, int right);
void Merge(int Ar[], int TempAr[], int Lpos, int Rpos, int RightEnd);

void ShellSort(int ar[], int N);

void QuickSort(int ar[], int amount);
void Qsort(int ar[], int left, int right);
void Quick_InsertionSort(int ar[], int amount);
int Median3(int ar[], int left, int right);
int main()
{
	
	int amount = 10000000;
	//int ar[10] = { 1,5,8,4,9,3,2,0,7,6 };
	int *ar=(int *)malloc(amount*sizeof(int));
	//InsertionSort(ar, amount);

	//InsertionSort(ar, amount);	//��������


	initialize(ar, amount);		//ע����Ȼ��γ�ʼ����������������ʱ��϶̣����������ͬ
	HeapSort(ar, amount);			//�ʿɽ��ƿ�Ϊ��ʼ״̬��ͬ���������������������ʼ״̬δ����ͬ

	initialize(ar, amount);
	MergeSort(ar, amount);

	initialize(ar, amount);
	ShellSort(ar, amount);

	initialize(ar, amount);
	QuickSort(ar, amount);
	system("pause");
}

//��ʼ��
void initialize(int ar[], int amount)
{
	srand((unsigned int)time(0));

	for (int i = 0; i < amount; i++)
		ar[i] = ((rand() % 68587+rand()%6946-9)*(rand()%33654+3*i))%100000;
	//���д�ĳ�ʼ�����㹫ʽ���������һ��....
}

//չʾ
void show(int ar[], int amount,string fun_name, double running_time)
{
	int i, j, step;

	step = amount / 20;		//չʾ������

	cout << endl << endl;
	cout << left;			//���Ʒ��������
	for (i = 0, j = 1; i < amount; i += step,j++)
	{
		cout.width(6);
		cout << ar[i] << "  ";
		if (j % 10 == 0)
			cout << endl;
	}
	cout << "\nThe running time for use "<<fun_name << " is "<<running_time << " seconds." ;
	cout<< endl;
}

//����
void swap(int* num1, int* num2)
{
	int temp;

	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

//��������
//������κʹ�����Σ����ϵĽ���λ������β��뵽�������
void InsertionSort(int ar[], int amount)
{
	int j, i,temp;

	for (i= 1; i < amount; i++)
	{
		temp = ar[i];		//��¼ֵ����ʽ����

		for (j = i; j > 0 && ar[j - 1] > temp; j--)		//��������ֵС������εĻ���ֱ������
			ar[j] = ar[j - 1];							//����ݼ���������λ

		ar[j] = temp;		//ͨ��temp����
	}
}

//������----����
void PercDown(int ar[], int i, int amount)	//amount������Ԫ�ص�������������Ҫ������Ӱ��
{
	int child;
	int temp;	//���ڽ���

	for (temp = ar[i]; LeftChild(i) < amount; i = child) //��temp��¼�ڵ��ֵ�����ڽ���������ڵ�������ӽڵ�Ļ�
	{
		child = LeftChild(i);		//����ӽڵ�
		if (child != amount - 1 && ar[child + 1] > ar[child])	//����ڵ㲻�ǵ���Ҷ��������Ҷ��������Ҷ�Ļ�
			child++;				//�������������Ҷ���ϴ�ģ�

		if (temp < ar[child])		//����ڵ�С������Ҷ�Ļ�����ʽ������
									//������ͨ��forѭ��������i��Ȼ����for��ʹ��temp����
			ar[i] = ar[child];		//���һ������һ��ѭ���������ж��µĽڵ������Ҷ��ϵ
		else						
			break;				//����������Ҷ������ϴ�����ʣ����øı䣬ֱ������	
	}
	ar[i] = temp;				//ע��forѭ���и�����i��ʵ�����൱�ڽ����ڵ����ֵ��С�Ķ��ӽڵ�
}
//������----����
void HeapSort(int ar[], int amount)
{
	double running_time;
	clock_t start, finish;
	start = clock();

	int i;

	for (i = amount / 2; i >= 0; i--)	//������ʼmax��
		PercDown(ar, i, amount);

	for (i = amount - 1; i > 0; i--)
	{
		swap(&ar[i], &ar[0]);			//����ͷβ�������ֵ�ŵ����ұߣ�
										//��������ʱ���������ұߣ���ʡ�ռ䣬ͬʱҲ���������Ĺؼ�
		PercDown(ar, 0, i);		//����һ�ζѹ���
	}

	finish = clock();					//��ʱ��
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount, "HeapSort",running_time);
}

//�鲢����
void MergeSort(int ar[], int amount)
{
	double running_time;
	clock_t start, finish;
	start = clock();

	int* TempAr;
	TempAr = (int *)malloc(amount * sizeof(int));
	if (TempAr)
	{
		Msort(ar, TempAr, 0, amount - 1);
		free(TempAr);			//�ǵ��ͷ���ʱ����
	}
	else
		cerr << "No space for temp array!";

	finish = clock();					//��ʱ��
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount,"MergeSort", running_time);
}
void Msort(int Ar[], int TempAr[], int left, int right)		//����
{
	int center;

	if (left < right)						//�õݹ���ã����ϵķָ����飬ֱ���������ʱ���кϲ�
	{
		center = (left + right) / 2;
		Msort(Ar, TempAr, left, center);
		Msort(Ar, TempAr, center+1, right);
		Merge(Ar, TempAr, left, center + 1, right);	//�ϲ�
	}
}
void Merge(int Ar[], int TempAr[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, Num, TempPos;

	LeftEnd = Rpos - 1;
	TempPos = Lpos;	
	Num = RightEnd - Lpos + 1;		//����

	while (Lpos <= LeftEnd && Rpos <= RightEnd)		//���С����ֽ磬���Ҷ�С���ҷֽ磬��ϲ����̵Ĳ���
	{												//������ͬʱ��������/�Ҷ˵ģ����Ժ�����Ҫ��⣬����ʣ�ಿ��
		if (Ar[Lpos] <= Ar[Rpos])		//�����Сֵ
			TempAr[TempPos++] = Ar[Lpos++];	
		else
			TempAr[TempPos++] = Ar[Rpos++];
	}

	while (Lpos <= LeftEnd)				//����벿��ʣ�࣬�򿽱���벿��ʣ�ಿ��
		TempAr[TempPos++] = Ar[Lpos++];
	while (Rpos <= RightEnd)			//���Ұ벿��ʣ�࣬�򿽱��Ұ벿��ʣ�ಿ��
		TempAr[TempPos++] = Ar[Rpos++];

	for (i = 0; i < Num; i++, RightEnd--)	//�������TempAr�п�����ԭ������
		Ar[RightEnd] = TempAr[RightEnd];
}

//ϣ������--��С��������
void ShellSort(int ar[], int amount)
{	
	double running_time;
	clock_t start, finish;

	start = clock();

	int i, j, increment, temp;

	for (increment = amount / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < amount; i++)
		{
			temp = ar[i];			//��¼ar[i]��ֵ��������ʽ����
			for (j = i; j >= increment; j -= increment)	//ע��for�ĸ�����䣬������j��ֵ
			{
				if (temp < ar[j - increment])		//���С���������г�ʼλ�õ�ֵ�Ļ�
					ar[j] = ar[j - increment];		//������ar[j]ֵ��������ʽ����
				else
					break;			//ֱ����������������
			}
			ar[j] = temp;		//������ʵ���ϱ�֤��һ����������������
		}
	}

	/*
	for (increment = amount / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < amount; i++)
		{
			temp = ar[i];
			j = i - increment;
			while (j >= 0 && temp < ar[j])
			{
				ar[j + increment] = ar[j];
				j -= increment;
			}
			ar[j + increment] = temp;
		}
	}
	*/

	finish = clock();					//��ʱ��
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount,"ShellSort", running_time);
}

//��������
void QuickSort(int ar[], int amount)
{
	double running_time;
	clock_t start, finish;
	start = clock();

	Qsort(ar, 0, amount - 1);

	finish = clock();					//��ʱ��
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount,"QuickSort", running_time);
}
void Qsort(int ar[], int left, int right)
{
	int i, j, pivot;

	if (left + cutoff <= right)
	{
		pivot = Median3(ar, left, right);
		i = left;
		j = right - 1;
		for (;;)
		{
			while (ar[++i] < pivot) {}
			while (ar[--j] > pivot) {}
			if (i < j)
				swap(&ar[i], &ar[j]);
			else
				break;
		}

		swap(&ar[i], &ar[right - 1]);

		Qsort(ar, left, i - 1);
		Qsort(ar, i + 1, right);
	}
	else
		Quick_InsertionSort(ar+left,right-left+1);	//���ò�������
}
int Median3(int ar[], int left, int right)
{
	int center = (left + right) / 2;
	int temp = 0;

	if (ar[left] > ar[center])
		swap(&ar[left], &ar[center]);
	if (ar[left] > ar[right])
		swap(&ar[left], &ar[right]);
	if (ar[center] > ar[right])
		swap(&ar[center], &ar[right]);

	swap(&ar[center], &ar[right - 1]);

	return ar[right - 1];
}
void Quick_InsertionSort(int ar[], int amount)	//���������е��õĲ�������
{
	int j, p, temp;

	for (p = 1; p < amount; p++)
	{
		temp = ar[p];		//��¼ֵ����ʽ����

		for (j = p; j > 0 && ar[j - 1] > temp; j--)//��������ֵС������εĻ���ֱ������
			ar[j] = ar[j - 1];					   //����ݼ���������λ

		ar[j] = temp;		//ͨ��temp����
	}
}