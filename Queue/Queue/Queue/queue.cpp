#include"Queue.h"
#include<iostream>
bool IsEmpty(Queue* q)	//ͨ���ж�rear��front�Ƿ�������жϿ�
{
	return q->rear == q->front;
}

bool IsFull(Queue* q)	//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���
{
	return (q->rear + 1) % MAXSIZE == q->front;
}

bool Push(Queue* q,int num)	//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
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