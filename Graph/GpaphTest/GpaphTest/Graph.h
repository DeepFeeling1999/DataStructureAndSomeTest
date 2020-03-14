#pragma once
typedef struct node {	
	int data;				//�ߵ��ڽӵ���
	int weight;				//�ߵ�Ȩ��
	struct node* next;		//ָ����һ�ڵ�	
}Node;
typedef struct {
	Node list[5] = { 0 };
	int amount = 5;			//�ڵ�����
}Graph;

void GreatGraph(Graph* g, int ar[5][5]);
void DFS(Graph* g, int visit[], int d_node);
void BFS(Graph* G, int visit[], int d_node);
void DestroyGraph(Graph* g);

//���ζ�������
//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
#define MAXSIZE 6
typedef struct queue {
	int data[MAXSIZE] = { 0 };
	int front = 0, rear = 0;
}Queue;

//ͨ���ж�rear��front�Ƿ�������жϿ�
bool IsEmpty(Queue* q);		

//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���
bool IsFull(Queue* q);		

//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
bool Push(Queue* q, int num);

bool Del(Queue* q, int* x);