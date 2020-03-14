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
#define LeftChild(i) (2*(i)+1)		//堆排序中寻找左儿子节点
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

	//InsertionSort(ar, amount);	//不做测试


	initialize(ar, amount);		//注：虽然多次初始化，但是由于运行时间较短，随机种子相同
	HeapSort(ar, amount);			//故可近似看为初始状态相同，若数据量继续增大则初始状态未必相同

	initialize(ar, amount);
	MergeSort(ar, amount);

	initialize(ar, amount);
	ShellSort(ar, amount);

	initialize(ar, amount);
	QuickSort(ar, amount);
	system("pause");
}

//初始化
void initialize(int ar[], int amount)
{
	srand((unsigned int)time(0));

	for (int i = 0; i < amount; i++)
		ar[i] = ((rand() % 68587+rand()%6946-9)*(rand()%33654+3*i))%100000;
	//随便写的初始化计算公式，尽量随机一点....
}

//展示
void show(int ar[], int amount,string fun_name, double running_time)
{
	int i, j, step;

	step = amount / 20;		//展示的数量

	cout << endl << endl;
	cout << left;			//控制符，左对齐
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

//交换
void swap(int* num1, int* num2)
{
	int temp;

	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

//插入排序
//分有序段和待排序段，不断的将首位待排序段插入到有序段中
void InsertionSort(int ar[], int amount)
{
	int j, i,temp;

	for (i= 1; i < amount; i++)
	{
		temp = ar[i];		//记录值，隐式交换

		for (j = i; j > 0 && ar[j - 1] > temp; j--)		//有序段最大值小于无序段的话，直接跳出
			ar[j] = ar[j - 1];							//否则递减，交换邻位

		ar[j] = temp;		//通过temp交换
	}
}

//堆排序----构建
void PercDown(int ar[], int i, int amount)	//amount是数组元素的总数，后面需要考虑其影响
{
	int child;
	int temp;	//用于交换

	for (temp = ar[i]; LeftChild(i) < amount; i = child) //用temp记录节点的值，用于交换；如果节点有左儿子节点的话
	{
		child = LeftChild(i);		//左儿子节点
		if (child != amount - 1 && ar[child + 1] > ar[child])	//如果节点不是单子叶，且右子叶大于左子叶的话
			child++;				//自增，变成右子叶（较大的）

		if (temp < ar[child])		//如果节点小于其子叶的话，隐式交换，
									//即继续通过for循环，更改i，然后在for外使用temp交换
			ar[i] = ar[child];		//而且会进入新一轮循环，继续判断新的节点和其子叶关系
		else						
			break;				//大于其左子叶，则符合大堆性质，不用改变，直接跳出	
	}
	ar[i] = temp;				//注意for循环中更改了i，实际上相当于交换节点和其值更小的儿子节点
}
//堆排序----排序
void HeapSort(int ar[], int amount)
{
	double running_time;
	clock_t start, finish;
	start = clock();

	int i;

	for (i = amount / 2; i >= 0; i--)	//构建初始max堆
		PercDown(ar, i, amount);

	for (i = amount - 1; i > 0; i--)
	{
		swap(&ar[i], &ar[0]);			//交换头尾，即最大值放到最右边，
										//策略是暂时储存在最右边，节省空间，同时也是完成排序的关键
		PercDown(ar, 0, i);		//进行一次堆构建
	}

	finish = clock();					//计时块
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount, "HeapSort",running_time);
}

//归并排序
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
		free(TempAr);			//记得释放临时数组
	}
	else
		cerr << "No space for temp array!";

	finish = clock();					//计时块
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount,"MergeSort", running_time);
}
void Msort(int Ar[], int TempAr[], int left, int right)		//排序
{
	int center;

	if (left < right)						//用递归调用，不断的分隔两块，直到区间最短时进行合并
	{
		center = (left + right) / 2;
		Msort(Ar, TempAr, left, center);
		Msort(Ar, TempAr, center+1, right);
		Merge(Ar, TempAr, left, center + 1, right);	//合并
	}
}
void Merge(int Ar[], int TempAr[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, Num, TempPos;

	LeftEnd = Rpos - 1;
	TempPos = Lpos;	
	Num = RightEnd - Lpos + 1;		//总数

	while (Lpos <= LeftEnd && Rpos <= RightEnd)		//左端小于左分界，且右端小于右分界，因合并过程的差异
	{												//并不是同时到达最左/右端的，所以后面需要检测，链接剩余部分
		if (Ar[Lpos] <= Ar[Rpos])		//保存较小值
			TempAr[TempPos++] = Ar[Lpos++];	
		else
			TempAr[TempPos++] = Ar[Rpos++];
	}

	while (Lpos <= LeftEnd)				//若左半部分剩余，则拷贝左半部分剩余部分
		TempAr[TempPos++] = Ar[Lpos++];
	while (Rpos <= RightEnd)			//若右半部分剩余，则拷贝右半部分剩余部分
		TempAr[TempPos++] = Ar[Rpos++];

	for (i = 0; i < Num; i++, RightEnd--)	//将结果从TempAr中拷贝到原数组中
		Ar[RightEnd] = TempAr[RightEnd];
}

//希尔排序--缩小增量排序
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
			temp = ar[i];			//记录ar[i]的值，用于隐式交换
			for (j = i; j >= increment; j -= increment)	//注意for的更新语句，更新了j的值
			{
				if (temp < ar[j - increment])		//如果小于增量序列初始位置的值的话
					ar[j] = ar[j - increment];		//更改了ar[j]值，用于隐式交换
				else
					break;			//直接跳出，不做更新
			}
			ar[j] = temp;		//交换，实际上保证了一个增量序列内有序
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

	finish = clock();					//计时块
	running_time = ((double)finish - (double)start) / CLOCKS_PER_SEC;
	show(ar, amount,"ShellSort", running_time);
}

//快速排序
void QuickSort(int ar[], int amount)
{
	double running_time;
	clock_t start, finish;
	start = clock();

	Qsort(ar, 0, amount - 1);

	finish = clock();					//计时块
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
		Quick_InsertionSort(ar+left,right-left+1);	//调用插入排序
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
void Quick_InsertionSort(int ar[], int amount)	//快速排序中调用的插入排序
{
	int j, p, temp;

	for (p = 1; p < amount; p++)
	{
		temp = ar[p];		//记录值，隐式交换

		for (j = p; j > 0 && ar[j - 1] > temp; j--)//有序段最大值小于无序段的话，直接跳出
			ar[j] = ar[j - 1];					   //否则递减，交换邻位

		ar[j] = temp;		//通过temp交换
	}
}