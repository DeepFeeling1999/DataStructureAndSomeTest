#pragma once
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}Node,* Tree;

bool Add(Tree &T,int num);
Node* Delete(Tree &T,int num);
Node* Seek(Tree T, int num);
Node* FindMin(Tree T);
Node* FindMax(Tree T);
bool Destroy(Tree T);
void Preorder(Tree T);
void LevelOrder(Tree T);



//���ж���
//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
#define MAXSIZE 33
typedef struct queue {
	Tree data[MAXSIZE];
	int front = 0, rear = 0;
}Queue;

bool IsEmpty(Queue q);		//ͨ���ж�rear��front�Ƿ�������жϿ�

bool IsFull(Queue q);		//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���

bool Push(Queue* q, Tree num);//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1

bool Pop(Queue* q, Tree* x);