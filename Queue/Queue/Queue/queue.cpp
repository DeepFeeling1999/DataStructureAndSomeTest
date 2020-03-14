#include"Queue.h"
#include<iostream>
bool IsEmpty(Queue* q)	//通过判断rear和front是否相等来判断空
{
	return q->rear == q->front;
}

bool IsFull(Queue* q)	//通过判断队尾指针循环递增1时等于队首来判读满
{
	return (q->rear + 1) % MAXSIZE == q->front;
}

bool Push(Queue* q,int num)	//保留一个空位置存放队头指针,此时最大存放数目是MAXSIZE-1
{
	if (!IsFull(q))
	{
		q->rear = (q->rear + 1) % MAXSIZE;
		q->data[q->rear] = num;

		return true;
	}
	return false;
}

bool Pop(Queue* q, int* x)
{
	if (!IsEmpty(q))
	{
		q->front = (q->front + 1) % MAXSIZE;
		*x = q->data[q->front];
		return true;
	}
	
	return false;
}