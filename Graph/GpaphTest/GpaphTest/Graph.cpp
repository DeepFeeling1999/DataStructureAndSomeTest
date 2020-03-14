#include"Graph.h"
#include<iostream>
using std::cout;
using std::endl;
void GreatGraph(Graph* g, int ar[5][5])
{
	int i, j;
	Node* p;

	for (i = 0; i < g->amount; i++)
	{
		g->list[i].data = i + 1;		//ͷ���
		g->list[i].next = NULL;			//ָ���򸳳�ֵ
	}

	for (i = 0; i < g->amount; i++)
		for (j = g->amount - 1; j >= 0; j--)
			if (ar[i][j] != 0)				
			{
				p = (Node*)malloc(sizeof(Node));

				if (p)							//����ͷ�巨
				{
					p->data = j + 1;
					p->next = g->list[i].next;
					p->weight = ar[i][j];		//�ߵ�Ȩ��

					g->list[i].next = p;
				}
			}
}

void DFS(Graph* G, int visit[], int d_node)
{
	int d;
	Node* p;

	cout << d_node << "    ";
	visit[d_node - 1] = 1;			//���Ϊ�ѷ���

	p = G->list[d_node - 1].next;	//ת����һ���ڽӵ�

	while (p)				//��p��NULL��˵���ڵ���Χû���ڽӱ�		
	{								
		d = p->data;
		if (!visit[d-1])		//δ����ʱ
			DFS(G, visit, d);
		p = p->next;
	}
}

void BFS(Graph* G, int visit[], int d_node)
{
	int d;
	Node* p;
	Queue Q;

	cout << d_node << "    ";
	visit[d_node-1] = 1;		//����Ϊ���ʹ�

	Push(&Q, d_node);		//���
	while (!IsEmpty(&Q))	//�Ӳ�Ϊ��
	{
		Del(&Q, &d);
		p = G->list[d - 1].next;
		
		while (p)
		{
			if (!visit[p->data-1])	//���δ������
			{
				cout << p->data << "    ";
				visit[p->data-1] = 1;	//���Ϊ���ʹ�
				Push(&Q, p->data);
			}
			p = p->next;
		}
	}
}

void DestroyGraph(Graph* G)
{
	int i;
	Node* pre,*p;

	for (i = 0; i < G->amount; i++)
	{
		p = G->list[i].next;
		while (p)
		{
			pre = p->next;
			free(p);
			p = pre;
		}
	}
	//��G�Ƕ�̬����ģ�����Ҫ  free(G);
}






//���ζ��еķ�������
bool IsEmpty(Queue* q)	//ͨ���ж�rear��front�Ƿ�������жϿ�
{
	return q->rear == q->front;
}

bool IsFull(Queue* q)	//ͨ���ж϶�βָ��ѭ������1ʱ���ڶ������ж���
{
	return (q->rear + 1) % MAXSIZE == q->front;
}

bool Push(Queue* q, int num)	//����һ����λ�ô�Ŷ�ͷָ��,��ʱ�������Ŀ��MAXSIZE-1
{
	if (!IsFull(q))
	{
		q->rear = (q->rear + 1) % MAXSIZE;
		q->data[q->rear] = num;

		return true;
	}
	return false;
}

bool Del(Queue* q, int* x)
{
	if (!IsEmpty(q))
	{
		q->front = (q->front + 1) % MAXSIZE;
		*x = q->data[q->front];
		return true;
	}

	return false;
}