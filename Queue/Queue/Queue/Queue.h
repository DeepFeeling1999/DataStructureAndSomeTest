#pragma once
//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
#define MAXSIZE 6
typedef struct queue {
	int data[MAXSIZE];
	int front=0, rear=0;
}Queue;
		
bool IsEmpty(Queue *q);		//ͨ���ж�rear��front�Ƿ�������жϿ�

bool IsFull(Queue* q);		//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���

bool Push(Queue* q, int num);//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
bool Pop(Queue* q,int *x);